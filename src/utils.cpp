#include "../header/constants.h"
#include "../header/types.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
void clearScreen() {
  // fungsi clearsecreen sesuaikan dengan  OS
}
string generateId(vector<Flight> &flights) {
  // generate id flight berdasarkan flight id terakhir
  return "0";
}

string toStringRole(Role &role) {
  if (role == ADMIN) {
    return "ADMIN";
  } else if (role == AIRLINE) {
    return "AIRLINE";
  } else {
    return "CUSTOMER";
  }
}

bool haveSymbol(string username) {
  for (char c : username) {
    if (ispunct(c)) {
      return true;
    }
  }
  return false;
}
