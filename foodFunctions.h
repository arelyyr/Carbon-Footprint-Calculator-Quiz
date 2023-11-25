
#ifndef FOODFUNCTIONS_H
#define FOODFUNCTIONS_H
#include <iostream>

#include "electronicFunctions.h"
#include <map>

/*
if user eats meat they input the types of meat they eat from list provided
returns yes/no to if they eat meat 
*/
std::string foodInput(std::map<std::string, double> gasEmissions, 
Queue& userInputObjects);

/*user inputs amount of days each meat from queue is eaten per week and ounces per each of those days
outputs total emissions from rates in the map and recs provided from hashtable
returns total weekly emissions
*/
double inputOuncesAndOutput(std::map<std::string, double> gasEmissions, 
Queue userInputObjects, HashTable& ht);

//prints the percentage comparision to the average yearly emissions
void compareToAverageFood(double total);

/*
initializes queue which stores meat types user enters
prints total emissions, recs, and comparison to average if user meats meat.
otherwise prints general info for lowering emissions related to food if user does not eat meat. 
*/
void food(std::map<std::string, double> gasEmissions, HashTable& recommendations);




#endif
