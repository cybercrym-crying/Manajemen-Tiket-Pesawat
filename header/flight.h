#pragma once
#include "types.h"
#include <string>
#include <vector>
using namespace std;

void viewFlight(const vector<Flight> &flights, const User &userlogged,
                const vector<User> &user);
