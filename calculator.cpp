#include "calculator.h"

void calculator()
{
  //brief description of calculator
  std::cout << "The calculator will calculate your individual CO2 emissions in 3 different categories: transportation, electronics, and food. You will also be provided with recommendations on how you can decrease your emissions.\n\n";
  
  //HashTable contains every recommendation used in the calculator
	HashTable recommendations;
  //Recs for cars
	recommendations.add("car", "\n-Using fuel-efficient vehicles(electric or hybrid), maintaining the car properly, and carpooling with others or using public transportation can significantly reduce carbon emissions from transportation while also saving money on fuel costs and reducing traffic congestion.");

  //recs for motorcycle
  recommendations.add("motorcycle", "\n-Choosing a fuel-efficient motorcycle and maintaining it properly can significantly reduce carbon emissions related to motorcycle transportation while also saving money on fuel costs and reducing the environmental impact of frequent maintenance.");

  //recs for electronics
	recommendations.add("phone", "\n\n-Use your phone efficiently by reducing screen brightness, disabling background apps, and using Wi-Fi instead of mobile data when possible.");
	recommendations.add("TV", "\n\n-Use energy-efficient TVs, such as LED or OLED models. Turn off the TV when not in use and consider using a smart power strip to reduce standby power consumption.");
	recommendations.add("PC", "\n\n-Use energy-efficient computers and monitors, and enable power-saving settings. Turn off the computer and peripherals when not in use");


  //recs for meat eaters 
  recommendations.add("beef", "\n\n-Beef has one of the highest carbon footprints amoung meats. Choosing plant-based alternatives or grass-fed beef can help reduce carbon emissions and support sustainable farming practices.");
	recommendations.add("meat", "\n\n-Choosing leaner meats and buying from local sources with sustainable farming methods can significantly reduce carbon emissions related to meat production.");
	
  

	/*map which stores all rates used for calculation
	  car and motorcycle uses kgCO2/mile
	  electronics use gCO2/hour of screen time
	  food uses gCO2/ounces

	*/
	std::map<std::string, double> gasEmissions = {

  //cars
	{"SUV",0.45},
	{"compact", 0.225},
	{"sedan", 0.25}, 
	{"sports",0.45},
	{"hybrid", 0.175}, 
	{"electric",0.1},

  //motorcycles
  {"small", 0.133},
	{"medium", 0.162},
	{"large", 0.213},

  //electronics
  {"phone", 1.6},
	{"TV",36},
	{"PC", 60},

  //meat
  {"beef", 751},
	{"pork",181},
	{"chicken", 162},
	{"fish", 145},
};
  
  std::string input;
  //allows the user to calculate there emissions from trans, elect, or food until they input exit
  while (input != "exit")
  {
    //prompts for category
    std::cout << "\n\n\nChoose a category: \n 1) transportation\n 2) electronics \n 3) food\n Enter \"exit\" to exit the calculator\n";
    std::cin >> input;

    //prompts questions for category chosen 
    if (input == "transportation" || input == "1" ) {
     transport(gasEmissions, recommendations);
    }
    else if (input == "electronics" || input == "2") {
     electronics(gasEmissions, recommendations);
    }
    else if (input == "food" || input == "3") {
      food(gasEmissions, recommendations);
    }
    else if (input != "exit") {
      // Handle invalid input
      std::cout << "Invalid input. Please try again.\n";
    }
  }
}