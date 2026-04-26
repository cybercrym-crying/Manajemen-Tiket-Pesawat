#pragma once
#include "types.h"
#include <string>
#include <vector>
using namespace std;

void viewFlight(const vector<Flight> &flights, string username, Role role);
void searchFlight(const vector<Flight> &flights, string destination);
bool addFlightData(vector<Flight> &flights, Flight &dataFlights);
bool deleteFlightData(vector<Flight> &flights, string &idFlights);
bool editFlightData(vector<Flight> &flights, Flight &dataFlights);
