#include <iostream>
#include "foodFunctions.h"
#include <string>
#include <map>
#include <iomanip>
#include <cmath>


std::string foodInput(std::map<std::string, double> gasEmissions, 
Queue& userInputObjects)
{
  //prompt for if user eats meat
	std::cout << "\n\n\n Are you a meat-eater?" << std::endl;
	std::cout << " 1) yes \n 2) no \n ";

  //store yes/no option
  std::string doesEat;

  while (true) {
    std::string input;
	  std::cin >> input;

    //if user eats meat doesEat==yes other wise no
    if(input == "1")
    {
		  doesEat = "yes";
      break;
    }
    if(input == "2")
    {
		  doesEat = "no";
      break;
    }
    //if input is not 1 or 2 output error message
       std::cout << "\nInvalid food type." 
      << " Please enter 1 if you are a meat-eater, and 2 if you are not: "
      << std::endl;
	}	

  
  //if user eats meat, prompt for which types of common meat user eats
	if(doesEat == "yes")
	{
    std::cout<< "Which types of meat do you eat? Enter done when finished: " 
		<< std::endl;
		std::cout << " 1) beef \n 2) chicken \n 3) pork \n 4) fish \n";
     while (true) {
   
    //user chooses from beef, chicken, pork, and fish
		std::string input;
		std::cin >> input;
  //beef is 1, chicken is 2, etc..
    //push meat selected to queue
    if(input == "1")
		  userInputObjects.push("beef");
    else if(input == "2")
      userInputObjects.push("chicken");
    else if(input == "3")
      userInputObjects.push("pork");
    else if(input == "4")
      userInputObjects.push("fish");
    // Exit the loop if the user types 'done'
    else if(input == "done")
      break;
      // Check if user input 1 2 3 or 4, if not then print error message
    else
    {
       std::cout << "\nInvalid food type." 
      << " Please enter 1 for beef, 2 for chicken, 3 for pork, and 4 for fish: "
      << std::endl;
    }
  }
	//return option yes/no for eating meat
}
  
  return doesEat; 
}



double inputOuncesAndOutput(std::map<std::string, double> gasEmissions, 
Queue userInputObjects, HashTable& ht)
{
  //stores total emissions from meat from suer
	double totalEmissions = 0;
  //stores recommendation from user
	std::string recommendation = "";
	//iterate through queue which has meats user eats
	 while(!userInputObjects.empty())
	 {
    //stores current meat accessed from queue. front of the queue
		std::string currObject = userInputObjects.getFront(); 
    //days per week the user eats meat
		double days;
    //ounces per day user eats the type of meat
		double ounces;

     //prompt for days user eats type of meat they entered
		std::cout << "How many days per week do you eat " << userInputObjects.getFront()
		 << "?" << std::endl;
		std::cin >> days;

     //User enters ounces of meat eaten on the days they eat that type
		std::cout << "\nOn the days you eat " << userInputObjects.getFront()
		<< ", how many ounces per day do you eat " << userInputObjects.getFront()
		 << "?" << std::endl;
     //provides ounces for common types of meals which contain that type of meat 
     
     //foods which contain beef and ounces of beef in each meal
     if(userInputObjects.getFront()== "beef")
     {
       std::cout << "For your reference: \nSteak: 8oz   Burger: 4oz   Stir-fry: 4oz " << std::endl;
     }
    //4-6oz per serving of chicken and fish
     else if(userInputObjects.getFront()== "chicken" || userInputObjects.getFront()== "fish")
     {
       std::cout << "For your reference: \nMost servings contain 4-6oz of " << userInputObjects.getFront() << std::endl;
     }
    ////foods which contain pork and ounces of pork
     else if(userInputObjects.getFront()== "pork")
     {
       std::cout << "For your reference: \nPork chops: 6-8oz   Pork ribs: 2-3oz/rib  Other meals: 4-6oz " << std::endl;
     }
		std::cin >> ounces;

    /*calculates total weekly emissions from each type of meat. days per week eating meat times the ounces per day the person eats meat times co2/ounce for the type of meat.
    */
		totalEmissions += ounces*(gasEmissions[currObject])*days;
		
	  //if beef is in queue add beef rec to rec var
		if(currObject == "beef") 
		{
			recommendation += (ht.recommend("beef"));
	  }
    //if other types of meat, add the general meat rec from hashtable to rec var
	  else if(currObject == "pork" || 
		currObject == "chicken" || currObject == "fish")
		{
      /*if the general meat rec is not already present, add the general meat rec to the rec var.
      prevents the same recommendation from being printed multiple times
      */
      if(recommendation.find("leaner") == std::string::npos)
      {
        recommendation += (ht.recommend("meat"));
      }
	  }
     //pop each item from the queue until queue is empty
  	userInputObjects.pop();
	}

  //print total weekly emissions
	std::cout << "\nTotal emissions: " << totalEmissions << 
	   " gCO2/week" << std::endl;
	   
	   //print out recs
	   std::cout << "\nRecommendations to reduce emissions: " << std::endl;
	   std::cout << recommendation << std::endl;

  //return total weekly emissions
	return totalEmissions;
}
	


void compareToAverageFood(double total)
{

  //stores yearly total of user, which is their calculated weekly emissions times the 52 weeks of the year
	double yearlyTotal = total*52;
  
	//average yearly emissions from an individual for food consumption 
		double average = 3300000;
    //if users total is greater than average print percent diff and we recommend to decrease
		if(yearlyTotal > average) 
		{
			percent_diff(yearlyTotal, average);
			std::cout << " We recommend to decrease your emissions."
			<<std::endl;
		}
    //if less than congratulate user and print percent diff
		else
		{
			std::cout << "\nCongratulations! "<<std::endl;
			percent_diff(yearlyTotal,average);
		}
} 

void food(std::map<std::string, double> gasEmissions, HashTable& recommendations)
{
  //initialize queue for storing user input. types of meat they eat.
	Queue userInputObjects;
	//input type is yes to eating meat or no
	std::string inputType = foodInput(gasEmissions, userInputObjects);

  //if they input yes, print total emissions, recs, and compare to average
  if(inputType == "yes")
  {
    double totalEmissions = inputOuncesAndOutput(gasEmissions, userInputObjects, recommendations);
	  compareToAverageFood(totalEmissions);
  }
  /*
    if user does not eat meat, emissions due to food choices are already very low. General information and recs are provided instead of theie emissions since emissions due to food are already very low.
  */
  else
  {
    std::cout << "\n\nBy not eating meat your emissions due to your food choices are already significantly low.\n To further reduce your emissions you can choose organic and sustainably produced foods, and use energy-efficient cooking methods. This can significantly reduce the carbon footprint of a vegetarian diet, while also promoting sustainable farming practices and saving energy." << std::endl;
  }
	
}