#pragma once
#include "constants.h"
#include "types.h"
#include <string>
#include <vector>
using namespace std;
void clearScreen();
void refreshPendingTicket(vector<Ticket> &ticket, vector<Flight> &flights);
string generateId(vector<Flight> &flights);
string generateIdTicket(vector<Ticket> &ticket);
string toStringRole(Role &role);
bool haveSymbol(string username);
bool checkIsDigit(string &x);
bool isValidDateTime(const string &dateTime);
