#pragma once
#include "types.h"
#include <string>
#include <vector>
using namespace std;

void customerMenu(User &userlogged, vector<User> &user, vector<Flight> &flights,
                  vector<Ticket> &ticket);
void bookingTicket(vector<Flight> &flights, vector<Ticket> &ticket,
                   const User &userlogged);
void payTicket(vector<Ticket> &ticket, const User &userlogged);
void cancelTicket(vector<Flight> &flights, vector<Ticket> &ticket,
                  const User &userlogged);
