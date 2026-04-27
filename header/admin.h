#pragma once
#include "types.h"
#include <vector>
using namespace std;
void adminMenu(const string username, vector<User> &user,
               vector<Flight> &flights, vector<Ticket> ticket);
void banUserAccount(vector<User> &user);
void removeUserAccount(vector<User> &user);
void viewListAccount(const vector<User> &user);
void addNewAccount(vector<User> &user);
