#pragma once
#include "types.h"
#include <string>
#include <vector>

void loadFile(vector<User> &user, vector<Ticket> &ticket,
              vector<Flight> &flights);

void addUserFile(vector<User> &user);
void removeUserFile(vector<User> &user);
void updateUserFile(vector<User> &user);

void addFlightFile(vector<Flight> &flight);
void removeFlightFile(vector<Flight> &flight);
void updateFlightFile(vector<Flight> &flight);

void addTicketFile(vector<Ticket> &ticket);
void removeTicketFile(vector<Ticket> &ticket);
