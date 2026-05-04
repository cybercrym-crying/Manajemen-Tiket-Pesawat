#pragma once
#include "types.h"
#include <string>
#include <vector>
using namespace std;

void viewFlight(const vector<Flight> &flights, string username, Role role);
void addFlightData(vector<Flight> &flights, const string username);
void deleteFlightData(vector<Flight> &flights, const string username);
void editFlightData(vector<Flight> &flights, const string username);
