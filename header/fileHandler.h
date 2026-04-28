#pragma once
#include "types.h"
#include <string>
#include <vector>

int loadFile(vector<User> &user, vector<Ticket> &ticket,
             vector<Flight> &flights);

void saveUserFile(vector<User> &user);
void saveFlightFile(vector<Flight> &flight);
void saveTicketFile(vector<Ticket> &ticket);
