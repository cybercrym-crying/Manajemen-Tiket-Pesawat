#pragma once
#include "types.h"
#include <string>
#include <vector>
#include <optional>

std::optional<User> loginAccount(vector<User> &user);
void registerAccount(vector<User> &user);
