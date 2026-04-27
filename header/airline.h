#pragma once
#include "types.h"
#include <string>
#include <vector>
using namespace std;
void airlineMenu(const string username, vector<User> &user,
                 vector<Flight> &flights, vector<Ticket> &ticket);
void viewTotalTransaction(const string username, const vector<Ticket> ticket);
void createFlight(const string username, vector<Flight> &flights);
void deleteFlight(const string username, vector<Flight> &flights);
