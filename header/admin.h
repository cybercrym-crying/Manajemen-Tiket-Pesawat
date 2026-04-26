#pragma once
#include "types.h"
#include <vector>
using namespace std;
void banUserAccount(vector<User> &user);
void eraseUserAccount(vector<User> &user);
void viewListAccount(const vector<User> &user);
void addNewAccount(vector<User> &user);
void viewHistory(const vector<Ticket> &history);
