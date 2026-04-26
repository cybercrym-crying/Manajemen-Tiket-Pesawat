#pragma once
#include "types.h"
#include <string>
#include <vector>
using namespace std;

void bookTicket(string username, int amountTicket, vector<Ticket> &ticket,
                vector<Flight> &flights);
bool cancelTicket(vector<Ticket> &ticket, vector<Flight> &flights,
                  string ticketID);
void paymentTicket(string ticketID, vector<Ticket> &ticket);

void viewHistoryTicket(vector<Ticket> &ticket, string username, Role role);
