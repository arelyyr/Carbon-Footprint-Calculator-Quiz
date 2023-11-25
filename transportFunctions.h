
#ifndef TRANSPORTFUNCTIONS_H
#define TRANSPORTFUNCTIONS_H
#include <iostream>
#include <vector>
#include "hashtable.h"
#include <map>

/*
User selects either car, motorcycle, or public transport
User inputs valid types of either the car or motorcycle they use. These types are added to queue
return transport type: car. motorcycle, or public
*/
std::string transportInput(Queue& userInputObjects);

/*
input days per week user drives each type of car/motorcycle and miles on each of those days
outputs recs and total emissions per week from forms of transportation chosen.
uses map which holds the rates and hashtable which holds rec for each type of transport
returns total emissions per week
*/
double inputMilesAndOutput(std::map<std::string, double> gasEmissions, 
Queue userInputObjects, HashTable& ht);

/*
compares total yearly emissions from user to the average yearly emissions 
outputs percent above or below the average

function is used by transportation, food, and electronics 
*/
void percent_diff(double total, double average);

/*
compares the users yearly emissions to the average yearly emissions of an individual
prints percent diff and recommends to decrease emissions if above average yearly emissions
*/
void compareToAverageTransport(std::string inputType, double total);

/*
initializes queue which holds user input
if transport type is car or motorcyles, print total emissions, recs, and compare to average
if type is public, print general information and recs for public transport users.
*/
void transport(std::map<std::string, double> gasEmissions, HashTable& recommendations);




#endif

