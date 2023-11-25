#include <iostream>
#include <string>
#include <utility>
#include <fstream>
#include <iomanip>
#include <limits>
#include "quiz.h"
#include "dag.h" // directed acyclic graph

const int NUM_QUESTIONS = 10;                       // max number of questions to ask
const int LEADERBOARD_POSITIONS = 10;               // number of positions in leaderboard
const std::string LEADERBOARD_FILENAME = "lb.txt";  // name of file for leaderboard

void quizGame()
{
    srand(time(0)); // seed rng

    // create and initialize graph that will be traversed and used to store quiz questions/answers/responses
    DAG quiz_graph;
    initializeQuizGraph(quiz_graph); 
    
    int score = 0;
    int count = 0;
    char user_answer = '\0';

    // starts at first vertex
    Vertex* currentVertex = quiz_graph.getFirstVertex();

    if (currentVertex == nullptr) // error check
    {
        std::cout << "No questions provided or no firstVertex assigned in graph.";
    }
  
    // introduction text output
    std::cout << "Welcome to the Climate Change Quiz!" << std::endl;
    std::cout << "This quiz contains various questions about climate change." << std::endl;
    std::cout << "You will be presented with multiple-choice questions and must answer with either 1 or 2." << std::endl;
    std::cout << "You may also quit at any time by entering Q. However, your score will not be saved." << std::endl;
    std::cout << "Good luck!" << std::endl;

    // while loop for asking and answering quiz questions by traversing quiz_graph
    while (currentVertex != nullptr) {
        // checks if less than question count (currently 10)
        if (count < NUM_QUESTIONS && (user_answer != 'q' && user_answer != 'Q')) 
        {
            
            // print questions and choices
            std::cout << "\nQuestion " << count+1 << ": " << std::endl;
            std::cout << currentVertex->question << std::endl;
            std::cout << currentVertex->choices << std::endl;
            // get answer input from user
            std::cout << "Answer: ";
            std::cin >> user_answer;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            // check if user answer is correct or quitting
            if (user_answer == 'q' || user_answer == 'Q') {
                // reprompt and warn user
                std::cout << "\nAre you sure you want to quit? Your score will not be submitted to the leaderboard.\n";
                std::cout << "Type Q again to confirm, or any other key to continue: \n";
                std::cin >> user_answer;
            }
            // only run if not quitting
            if (user_answer != 'q' && user_answer != 'Q')
            {
                count++; 
                if (tolower(user_answer) == tolower(currentVertex->correct_answer))
                {
                    // user answer is correct
                    std::cout << currentVertex->response_correct << std::endl;                  // print correct response
                    score++;                                                                    // increment score
                }
                else
                {
                    // user answer is wrong
                    std::cout << currentVertex->response_incorrect << std::endl;                // print wrong response
                }
                // update next vertex/question to use
                if (!(quiz_graph.getEdgesFrom(currentVertex)->empty()))
                {
                    if (tolower(user_answer) == tolower(currentVertex->correct_answer))
                    {
                        // if correct, use 1st edge as next question
                        currentVertex = quiz_graph.getEdgesFrom(currentVertex)->at(0)->toVertex;
                    }
                    else
                    {
                        if (quiz_graph.getEdgesFrom(currentVertex)->size() >= 2) 
                        {
                            // when wrong, if the current vertex has a 2nd edge, use that as the next question
                            currentVertex = quiz_graph.getEdgesFrom(currentVertex)->at(1)->toVertex;
                        }
                        else
                        {
                            // no alternate question, so just use 1st edge as next question
                            currentVertex = quiz_graph.getEdgesFrom(currentVertex)->at(0)->toVertex;
                        }
                    }
                }
                else { currentVertex = nullptr; } // at end of graph
            }
        } else { // count exceeds NUM_QUESTIONS
            currentVertex = nullptr;
        }
    }

    // display score
    std::cout << "\nYour score is " << score << " out of " << count << ".\n\n";

    // run leaderboard functions if user didn't quit early
    if (count == NUM_QUESTIONS)
    {
        // add user's score to leaderboard, display leaderboard, write to file, prompt user to clear leaderboard 
        leaderboard(score);
    }
    else
    {
        std::cout << "Your score will not be added to the leaderboard.\n";
        std::cout << "Returning to menu...\n";
    }
}

void leaderboard(int new_score)
{
    std::vector<std::pair<std::string, int>> leaderboard;   // leaderboard stored as pairs of name and score
    std::string name;                                       // name string read from leaderboard file
    int score;                                              // score int read from leaderboard file
    int max_name_length = 19;

    // load the leaderboard from the data file, or create a new one if it doesn't exist
    std::ifstream infile(LEADERBOARD_FILENAME);
    if (infile.is_open()) {

        while (infile >> name >> score) {
            leaderboard.push_back({name, score});
            // adjust leaderboard width if one of the names is too long
            if ((int)name.size() > max_name_length) { max_name_length = name.size();}
        }
        infile.close();
    }

    // prompt user for name to write to leaderboard
    std::string new_name = "defaultname";
    std::cout << "Please enter your name to submit to the leaderboard: ";
    getline(std::cin, new_name);
    // adjust leaderboard width if name is too long
    if ((int)new_name.size() > max_name_length) { max_name_length = new_name.size();}

    // add the new score to the leaderboard using binary search
    // use binary search to find the correct position to insert the new entry
    int index = binary_search(leaderboard, 0, leaderboard.size() - 1, new_score);

    // insert the new entry at the correct position
    leaderboard.insert(leaderboard.begin() + index, {new_name, new_score});

    // Keep only the top 10 scores
    if (leaderboard.size() > LEADERBOARD_POSITIONS) 
    {
        leaderboard.resize(LEADERBOARD_POSITIONS);
    }

    int name_width = max_name_length + 1;

    // display the leaderboard with proper formatting
    std::cout << std::left << std::setw(6) << "Rank" << std::setw(name_width) << "Name" << std::setw(10) << "Score" << std::endl;
    std::cout << std::setfill('-') << std::setw(36) << "" << std::setfill(' ') << std::endl;
    int count = 0;
    while (count < (int)leaderboard.size() && count < LEADERBOARD_POSITIONS)
    {
        std::cout << std::left << std::setw(6) << (count+1) << std::setw(name_width) << leaderboard[count].first << std::setw(10) << leaderboard[count].second << std::endl;
        count++;
    }
    
    // prompt user to clear the leaderboard
    char choice;
    std::cout << "Do you want to clear the leaderboard? (Y/N): ";
    std::cin >> choice;
    if (choice == 'Y' || choice == 'y') {
        // clear leaderboard vector
        leaderboard.clear();
        // clear leaderboard file
        std::ofstream outfile(LEADERBOARD_FILENAME, std::ios::out | std::ios::trunc);
        if (outfile.is_open()) {
            outfile.close();
            std::cout << "Leaderboard cleared." << std::endl;
        }
    }

    // write the updated leaderboard to the data file
    std::ofstream outfile(LEADERBOARD_FILENAME);
    if (outfile.is_open()) {
        for (auto& score : leaderboard) {
            outfile << score.first << " " << score.second << std::endl;
        }
        std::cout << "Updated leaderboard data file: " << LEADERBOARD_FILENAME << std::endl;
        outfile.close();
    } else {
        std::cerr << "Unable to open file for writing" << std::endl;
    }
}

int binary_search(std::vector<std::pair<std::string, int>>& leaderboard, int from, int to, int value)
{  
    if (from > to) 
    { 
        return from; // element not found
    }

    int mid = (from + to) / 2;
    if (leaderboard[mid].second == value)
    {
        // if the value already exists, insert after the last entry with that value
        while (mid < (int)leaderboard.size() && leaderboard[mid].second == value) {
            ++mid;
        }
        return mid;
    }
    else if (leaderboard[mid].second > value)
    {
        return binary_search(leaderboard, mid + 1, to, value);
    }
    else
    {
        return binary_search(leaderboard, from, mid - 1, value);
    }
}

void initializeQuizGraph(DAG& quiz_graph)
{
    // create random general knowledge vertices
    Vertex* vertex1 = quiz_graph.addVertex("What is the main cause of climate change?", "1. Human activity \n" "2. Natural fluctuations in the Earth’s climate \n", '1', "Correct! This is because Human activities, such as burning of fossil fuels and deforestation, are the primary cause of climate change due to the release of greenhouse gases. Although natural fluctuations can contribute to short-term climate variability, they are not the main cause of the observed long-term warming trend.", "Incorrect. The correct answer is “1. Human Activity”. The primary driver of climate change is human activity, specifically the release of greenhouse gases through burning of fossil fuels and deforestation. While natural fluctuations can contribute to short-term climate variability, they are not the main cause of the observed long-term warming trend.");
    Vertex* vertex2 = quiz_graph.addVertex("Which of the following is not a greenhouse gas?", "1.Carbon Dioxide\n" "2. Oxygen\n", '2', "Correct! This is because greenhouse gases trap heat in the Earth's atmosphere, contributing to the warming of the planet. Oxygen does not have this property and is not considered a greenhouse gas.", "Incorrect. The correct answer is “2.Oxygen”. This is because greenhouse gases are gases that absorb and emit radiation within the thermal infrared range. However, oxygen does not have this property and is not considered a greenhouse gas.");
    Vertex* vertex3 = quiz_graph.addVertex("Which sector contributes the most to greenhouse gas emissions globally?", "1. Transportation\n" "2. Industry\n", '1', "Correct! This is because the transportation sector is a major source of greenhouse gas emissions, responsible for approximately 24% of global emissions. This includes emissions from cars, trucks, airplanes, ships, and other forms of transportation that rely on fossil fuels.", "Incorrect. The correct answer is “1. Transportation”. While the Industry sectors also contribute to greenhouse gas emissions, they do not emit as much as the transportation sector, being 24% of global emissions. The industry sector, for example, is responsible for approximately 21% of global emissions, which is close.");
    Vertex* vertex4 = quiz_graph.addVertex("What is the Paris Agreement?", "1. An agreement between countries to reduce greenhouse gas emissions\n" "2. A treaty to protect endangered species\n", '1' , "Correct! The Paris Agreement is an international treaty adopted in December 2015 with the goal of limiting global warming to below 2 degrees Celsius above pre-industrial levels, and a target of 1.5 degrees Celsius." , "Incorrect. The correct answer is “1. An agreement between countries to reduce greenhouse gas emissions”. The Paris Agreement is an international treaty adopted in December 2015 with the goal of limiting global warming to below 2 degrees Celsius above pre-industrial levels, and a target of 1.5 degrees Celsius.");
  Vertex* vertex5 = quiz_graph.addVertex("Which of the following is a consequence of climate change?", "1. Increase Rainfall\n" "2. Rising Seal Levels\n" , '2' , "Correct! Climate change has caused global temperatures to rise, which in turn has caused glaciers and ice caps to melt. This melting ice contributes to rising sea levels, which is one of the most significant consequences of climate change.", "Incorrect. The correct answer is “2. Rising Sea Levels”. Climate change has caused global temperatures to rise, which in turn has caused glaciers and ice caps to melt. This melting ice contributes to rising sea levels, which is one of the most significant consequences of climate change. This can also result in changes to the precipitation patterns but doesn’t necessarily mean an increase in rain.");
  Vertex* vertex6 = quiz_graph.addVertex("What is the name of the process by which energy from the sun is trapped by the Earth's atmosphere?" , "1. Photosynthesis\n" "2. The Greenhouse Effect\n" , '2' , "Correct! The greenhouse effect is a natural process by which energy from the sun is absorbed by the Earth's surface and radiated back into the atmosphere as heat. This heat is then trapped by certain gases in the atmosphere, known as greenhouse gases, which act like a blanket to keep the planet warm. Without the greenhouse effect, the Earth's surface would be too cold to support life as we know it." , "Incorrect. The correct answer is “2. The greenhouse effect”. Photosynthesis is a biological process that occurs in living organisms and is not directly related to the greenhouse effect or climate change. The greenhouse effect is a natural process by which energy from the sun is absorbed by the Earth's surface and radiated back into the atmosphere as heat. This heat is then trapped by certain gases in the atmosphere, known as greenhouse gases, which act like a blanket to keep the planet warm.");
  Vertex* vertex7 = quiz_graph.addVertex("What is the term used to describe the gradual increase in the Earth's average surface temperature?" , "1. Global Warming\n" "2. Climate Change\n" , '1' , "Correct! Global warming refers to the long-term trend of rising average temperatures on the Earth's surface, primarily due to human activities such as the burning of fossil fuels and deforestation, which increase the concentration of greenhouse gases in the atmosphere." , "Incorrect. The correct answer is “1. Global Warming”. Climate change is a broader term that encompasses all the long-term changes in the Earth's climate system, including changes in temperature, precipitation, and weather patterns, as well as the impacts of these changes on the environment and human societies. Global warming refers to the long-term trend of rising average temperatures on the Earth's surface, primarily due to human activities such as the burning of fossil fuels and deforestation, which increase the concentration of greenhouse gases in the atmosphere.");
  Vertex* vertex8 = quiz_graph.addVertex("Which of the following energy sources is considered the most environmentally friendly?" , "1. Coal\n" "2. Solar\n" , '2' , "Correct! Solar energy is considered to be the most environmentally friendly because it is renewable, emits no greenhouse gases, and has a minimal environmental impact compared to coal." , " Incorrect. The correct answer is “2. Solar”. Coal is a fossil fuel that is responsible for a significant portion of global greenhouse gas emissions and other air pollutants. Solar energy is considered to be the most environmentally friendly because it is renewable, emits no greenhouse gases, and has a minimal environmental impact compared to coal.");
  Vertex* vertex9 = quiz_graph.addVertex("How much has the Earth's average temperature increased since the 19th century?" , "1. 0.5°C\n" "2. 1.5°C\n" , '2' , "Correct! The IPCC has reported that the global average temperature has increased by approximately 1.1°C to 1.5°C since the pre-industrial era (mid-to late-19th century), with a majority of the warming occurring in the last few decades." , "Incorrect. The correct answer is b. 1.5°C. The IPCC has reported that the global average temperature has increased by approximately 1.1°C to 1.5°C since the pre-industrial era (mid to late-19th century), with a majority of the warming occurring in the last few decades.");
  Vertex* vertex10 = quiz_graph.addVertex("What is the term used to describe the process by which trees absorb carbon dioxide?" , "1. Photosynthesis\n" "2. Carbon Sequestraion\n" , '2' , "Correct! Carbon sequestration is the process by which carbon is removed from the atmosphere and stored in carbon sinks, such as forests, oceans, and soils. Trees absorb carbon dioxide from the atmosphere through the process of photosynthesis, in which they convert carbon dioxide and water into oxygen and organic compounds." , "Incorrect. The correct answer is “2. Carbon Sequestration”. Photosynthesis is the process by which plants, including trees, use sunlight to convert carbon dioxide and water into oxygen and organic compounds, such as sugars and starches. Carbon sequestration is the process by which carbon is removed from the atmosphere and stored in carbon sinks, such as forests, oceans, and soils.");
  Vertex* vertex11 = quiz_graph.addVertex("What is the effect or outcome of climate change?" , "1. Increased Crop Yields\n" "2. More Frequent & Severe Heatwaves\n" , '2' , "Correct! More frequent and severe heat waves are a consequence of climate change. Rising global temperatures can lead to more frequent and intense heat waves, which can have negative impacts on human health, agriculture, and infrastructure." , "Incorrect. The correct answer is 2. More frequent and severe heatwaves. While some regions may experience increased crop yields due to longer growing seasons or increased rainfall, the overall negative impacts of climate change on agriculture, including decreased crop yields and increased pests and diseases, far outweigh any potential benefits.");
  Vertex* vertex12 = quiz_graph.addVertex("Which of the following is an example of a natural carbon sink?" , "1. Coal Mines\n" "2. Forests\n" , '2' , "Correct! Forests are an example of a natural carbon sink because trees absorb carbon dioxide from the atmosphere during photosynthesis and store it in their biomass and soil. This process is known as carbon sequestration. Forests can store large amounts of carbon over long periods of time, making them an important tool for mitigating climate change." , " Incorrect. The correct answer is 2. Forests. Coal mines are a source of carbon emissions rather than a sink. Forests are an example of a natural carbon sink because trees absorb carbon dioxide from the atmosphere during photosynthesis and store it in their biomass and soil.");
  Vertex* vertex13 = quiz_graph.addVertex("Which of the following is a consequence of melting permafrost?" , "1. Increased availability of agricultural land\n" "2. Release of methane, a potent greenhouse gas\n" , '2' , "Correct! Methane is a greenhouse gas that is more potent than carbon dioxide, meaning that it has a greater ability to trap heat in the Earth's atmosphere and contribute to global warming. The release of methane from melting permafrost is therefore a significant consequence of climate change, as it can lead to further warming and more permafrost melt." , " Incorrect. The correct answer is 2. Release of methane, a potent greenhouse gas. The melting of permafrost is unlikely to result in increased availability of agricultural land. The cold and harsh conditions in the Arctic and sub-Arctic regions make it difficult for crops to grow, even if the permafrost were to melt. Methane is a greenhouse gas that is more potent than carbon dioxide, meaning that it has a greater ability to trap heat in the Earth's atmosphere and contribute to global warming.");
  Vertex* vertex14 = quiz_graph.addVertex("Which of the following is a consequence of the increased frequency and intensity of extreme weather events?" , "1. Decreased property damage\n" "2. Increased human and economic costs\n" , '2' , "Correct! Increased frequency and intensity of extreme weather events can lead to increased human costs, such as injury, illness, and loss of life. Extreme heat waves, for example, can lead to heat stroke and dehydration, while floods and hurricanes can cause drowning and injury. In addition, extreme weather events can have social and economic impacts. Economic costs are also a significant consequence of extreme weather events. These events can cause damage to homes, businesses, and infrastructure, leading to loss of property and income." , " Incorrect. The correct answer is 2. Increased human and economic costs. It is unlikely that increased frequency and intensity of extreme weather events would lead to decreased property damage, as extreme weather events are likely to cause more damage, not less.");
  Vertex* vertex15 = quiz_graph.addVertex("How much time do we have left to prevent irreversible damage from climate change?" , "1. Until 2035\n" "2. Until 2050\n" , '1' , "Correct, unfortunately. Based on current predictions, maintaining the current rate of increase in global average temperature would result in irreversible damage by 2035. However, recent observations during the pandemic suggest that it is possible to reduce the Earth's temperature by adopting more environmentally sustainable behaviors. Achieving this would require widespread changes towards the environment." , " Incorrect, unfortunately. The correct answer is 1. Until 2035. Based on current predictions, maintaining the current rate of increase in global average temperature would result in irreversible damage by 2035. However, recent observations during the pandemic suggest that it is possible to reduce the Earth's temperature by adopting more environmentally sustainable behaviors. Achieving this would require widespread changes towards the environment.");

    // removes all edges in the graph and shuffles vertices, 
    // then updates adjacency list to make vertices into a randomized list
    quiz_graph.shuffleToList();

    // create follow-up vertices, which are given after user gives wrong answer
    Vertex* vertex1a = quiz_graph.addVertex("What are the effects of climate change on the planet and its inhabitants?", "1. Increased sea levels, biodiversity, and economic growth\n" "2.Rising temperatures, sea level rise, extreme weather events, ecosystem disruption, and human health impacts", '2', "Correct! Climate change has a range of negative impacts on the planet and its inhabitants, including rising temperatures, sea level rise, extreme weather events, ecosystem disruption, and human health impacts. While climate change can have some positive impacts, such as increased agricultural yields in some regions, the overall negative impacts far outweigh any positives.", "Incorrect. The correct answer is 2. Rising temperatures, sea level rise, extreme weather events, ecosystem disruption, and human health impacts. Climate change has a range of negative impacts on the planet and its inhabitants, including rising temperatures, sea level rise, extreme weather events, ecosystem disruption, and human health impacts. While climate change can have some positive impacts, such as increased agricultural yields in some regions, the overall negative impacts far outweigh any positives.");
    Vertex* vertex2a = quiz_graph.addVertex("Which of the following is not a greenhouse gas? " , "1. Methane\n" "2. Water Vapor\n" , '2', "Correct! Water Vapor is not considered a greenhouse gas in the context of climate change because it does not directly contribute to increases in atmospheric temperatures." , "Incorrect. The correct answer is 2. Water Vapor. Methane is a potent greenhouse gas that is emitted through natural processes like decomposition, as well as human activities such as livestock farming and natural gas production. It is a significant contributor to climate change, trapping about 28 times more heat than carbon dioxide over a 100-year timescale.");
    Vertex* vertex5a = quiz_graph.addVertex("Which of the following is NOT a consequence of climate change?" , "1. rising Sea Levels\n" "2. Decreasing Carbon Dioxide Emissions\n" , '2' , "Correct! This is true because rising sea levels are a consequence of climate change while decreasing carbon dioxide emissions is a measure to mitigate climate change.", "Incorrect. The correct answer is 2. Decreasing carbon dioxide emissions. This is true because rising sea levels are a consequence of climate change while decreasing carbon dioxide emissions is a measure to mitigate climate change.");
    Vertex* vertex8a = quiz_graph.addVertex("Which of the following is a renewable energy source?" , "1. Natural Gas\n" "2. Wind Power\n" , '2' , "Correct! Wind power is a form of renewable energy that harnesses the power of the wind to generate electricity. Wind turbines are used to capture the kinetic energy of the wind and convert it into electricity. Wind power is a sustainable and clean source of energy that can help reduce greenhouse gas emissions and lessen the impacts of climate change." , "Incorrect. The correct answer is 2. Wind Power. Natural gas is a non-renewable fossil fuel that is extracted from the ground and burned to generate electricity. In contrast, Wind power is a form of renewable energy that harnesses the power of the wind to generate electricity.");
    Vertex* vertex9a = quiz_graph.addVertex("What is the name of the international body responsible for assessing climate change science?" , "1. The Intergovernmental Panel on Climate Change (IPCC)\n" "2. The United Nations Development Programme (UNDP)\n" , '1' , "Correct! The IPCC is a scientific body established by the United Nations to provide regular assessments of the scientific basis of climate change, its impacts and future risks, and possible response options." , " Incorrect. The correct answer is “1. The Intergovernmental Panel on Climate Change (IPCC)”. The United Nations Development Programme is another agency of the United Nations, which works to reduce poverty, inequality, and promote sustainable development in countries around the world. The IPCC is a scientific body established by the United Nations to provide regular assessments of the scientific basis of climate change, its impacts and future risks, and possible response options.");

    // add edges to and from follow-up vertices (wrong answer vertices)
        // example: creates edges vertex1->vertex1a and vertex1a->(index 0 edge of vertex1)
    quiz_graph.addWrongAnsEdge(vertex1, vertex1a);
    quiz_graph.addWrongAnsEdge(vertex2, vertex2a);
    quiz_graph.addWrongAnsEdge(vertex5, vertex5a);
    quiz_graph.addWrongAnsEdge(vertex8, vertex8a);
    quiz_graph.addWrongAnsEdge(vertex9, vertex9a);

}
