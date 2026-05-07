#pragma once
#include "types.h"
#include <string>
#include <vector>
using namespace std;
void airlineMenu(const string username, vector<User> &user,
                 vector<Flight> &flights, vector<Ticket> &ticket);
void viewTotalTransaction(vector<Flight> &flights, vector<Ticket> &ticket,
                          const string username);
void addFlightData(vector<Flight> &flights, const string &username);
void deleteFlightData(vector<Flight> &flights, const string &username,
                      const Role &role);
void editFlightData(vector<Flight> &flights, const string &username,
                    Role &role);
