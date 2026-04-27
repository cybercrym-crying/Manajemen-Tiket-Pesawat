#pragma once
#include "types.h"
#include <string>
#include <vector>
using namespace std;

void customerMenu(const string username, vector<User> &user,
                  vector<Flight> &flights, vector<Ticket> &ticket);
void bookingTicket(const string username);
void payTicket(const string username);
bool cancelTicket(const string username);
void updateAccount(vector<User> &user);
