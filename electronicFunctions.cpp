#include <iostream>
#include <string>
#include "electronicFunctions.h"
#include <map>
#include <iomanip>
#include <cmath>



void electronicsInput( 
Queue& userInputObjects)
{
    //prompts for types of electronics user uses: phone, TV, PC
		std::cout<< "\n\n\nWhich types of electronics do you use? Enter done when finished: " 
		<< std::endl;
		std::cout << " 1) phone \n 2) TV \n 3) PC/laptop \n";
	  
    while (true) {
    std::string input;
    std::cin >> input;
    
    //push electronic selected to queue
    if(input == "1")
		  userInputObjects.push("phone");
    else if(input == "2")
      userInputObjects.push("TV");
    else if(input == "3")
      userInputObjects.push("PC");
    // Exit the loop if the user types 'done'
    else if(input == "done")
      break;
      // Check if user input 1 2 or 3, if not then print error message
    else
    {
       std::cout << "\nInvalid electronic." 
      << " Please enter 1 for phone, 2 for TV, and 3 for PC: "
      << std::endl;
    }
	}	 
}



double inputScreenTimeAndOutput(std::map<std::string, double> gasEmissions, 
Queue userInputObjects, HashTable& ht)
{
  //stores total emissions by user from electronic usage
	double totalEmissions = 0;
  //stores recommendations given to user
	std::string recommendation = "";
	 
	
	//iterate through each object stored in queue
	 while(!userInputObjects.empty())
	 {
     //stores current object of the queue, front of queue 
		std::string currObject = userInputObjects.getFront(); 
    //hours of screen time for each type of object from queue 
		int hours;
		std::cout << "What is your average daily screen time for the " << userInputObjects.getFront()
		 << " in hours?" << std::endl;
		std::cin >> hours;
		 
		/*multiply daily average hours times the co2/(hour of screen time) rate from the map for each type of
     electronic(phone, TV,PC). multiply by 7 for weekly emissions
    */
		totalEmissions += hours*gasEmissions[currObject]*7;

    //add appropriate recs to the rec variable. 

     //if phone add phone rec
		if(currObject == "phone") 
		{
			recommendation += (ht.recommend("phone"));
	  }
    //if TV in queue add tv rec
	  else if(currObject == "TV")
		{
			recommendation += (ht.recommend("TV"));
	  }
    //if PC in queue add PC rec
	  else if(currObject == "PC")
    {
        recommendation += (ht.recommend("PC"));
    }
        
	    //pop from front of queue 
	    userInputObjects.pop();
	}
  //display total emissions
	std::cout << "\nTotal emissions: " << totalEmissions << 
	   " gCO2/week" << std::endl;
	   
	  
	   //print out recs
	   std::cout << "\nRecommendations to reduce emissions: " << std::endl;
	   std::cout << recommendation << std::endl;

  //return total weekly emissions
	return totalEmissions;
}
	
	

void compareToAverageElectronic(double total)
{
  //stores yearly total from calculated weekly total
	double yearlyTotal = total*52;
  //average yearly emissions by someone who uses electronics
	double average = 142496;
  //if greater than average, print percent diff and we recommend to decrease emissions
	 if(yearlyTotal > average) 
		{
			percent_diff(yearlyTotal, average);
			std::cout << " We recommend to decrease your emissions."
			<<std::endl;
		}
     //if less than average congratulate user and print percent diff
		else
		{
			std::cout << "\nCongratulations! "<<std::endl;
			percent_diff(yearlyTotal,average);
		}
} 



void electronics(std::map<std::string, double> gasEmissions, HashTable& recommendations)
{
  //queue which holds electronic types from user input
	Queue userInputObjects;
	
	//user inputs electronics
  electronicsInput(userInputObjects);
  //user inputs screen time for each electronic and total emissions calculated, print recs and total
	int totalEmissions = inputScreenTimeAndOutput(gasEmissions, userInputObjects, recommendations);
  //print comparision to average 
	compareToAverageElectronic(totalEmissions);
}