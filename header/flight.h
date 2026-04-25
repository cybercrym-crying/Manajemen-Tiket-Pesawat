#pragma once
#include "types.h"
#include <string>
#include <vector>
using namespace std;

void viewAllFlight(const vector<Flight> &flights);
void searchFlight(const vector<Flight> &flights, string destination);
void addFlight(vector<Flight> &flights);
void deleteFlight(vector<Flight> &flights);
void editFlight(vector<Flight> &flights);
