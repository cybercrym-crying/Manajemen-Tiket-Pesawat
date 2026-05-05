#pragma once
#include "types.h"
#include <string>
#include <vector>
using namespace std;

void customerMenu(const string username, vector<User> &user,
                  vector<Flight> &flights, vector<Ticket> &ticket);
void bookingTicket(vector<Flight> &flights, vector<Ticket> &ticket,
                   const string username, Role role);
void payTicket(vector<Ticket> &ticket, const string username);
void cancelTicket(vector<Flight> &flights, vector<Ticket> &ticket,
                  const string username);
