#ifndef ELECTRONICFUNCTIONS_H
#define ELECTRONICFUNCTIONS_H
#include <iostream>
#include "transportFunctions.h"
#include <map>



/*user inputs the electronics they use. choose from phone, TV, PC
map is used to validate that the input type is correct and each type entered by user
is added to the queue.
*/
void electronicsInput(Queue& userInputObjects);

/*
user inputs average hourly screen time for each type of electronic they use
total weekly emissions is calculated using rates stored in map and ouput to user
recs ouput based on electronics user entered using hashtable
*/
double inputScreenTimeAndOutput(std::map<std::string, double> gasEmissions, Queue userInputObjects, HashTable& ht);

/*
compare weekly total emissions to average yearly emissions of an individuals electronic usage
print perent diff between both values. if above average we recommend to decrease your emissions
*/
void compareToAverageElectronic(double total);

/*
initializes queue which holds input of types of electronics
user inputs electronics and average hourly screen time of each electronic
prints total emissions, compares to average, and prints recs for user
*/
void electronics(std::map<std::string, double> gasEmissions, HashTable& recommendations);

#endif