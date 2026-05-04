#pragma once
#include "constants.h"
#include "types.h"
#include <string>
#include <vector>
using namespace std;
void clearScreen();
string generateId(vector<Flight> &flights);
bool isValidDateTime(const string &dateTime);
string toStringRole(Role &role);
bool haveSymbol(string username);
bool checkIsDigit(string &x);
