#pragma once
#include "types.h"
#include <string>
#include <vector>
using namespace std;

void bookingTicket(const string username);
void payTicket(const string username);
bool cancelTicket(const string username);
void updateAccount(vector<User> user);
