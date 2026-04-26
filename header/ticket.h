#pragma once
#include "types.h"
#include <string>
#include <vector>
using namespace std;

void bookTicket(string username, int amountTicket, vector<Ticket> &ticket,
                vector<Flight> &flights);
void cancelTicket(vector<Ticket> &ticket, vector<Flight> &flights,
                  string ticketID);
void viewAllTicket(vector<Ticket> &ticket);
