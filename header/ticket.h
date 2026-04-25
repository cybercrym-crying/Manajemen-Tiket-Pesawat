#pragma once
#include "types.h"
#include <string>
#include <vector>
using namespace std;

void bookTicket(vector<Ticket> &ticket, const vector<Flight> &flights);
void cancelTicket(vector<Ticket> &ticket, string ticketID);
void displayAllTicket(vector<Ticket> &ticket);
