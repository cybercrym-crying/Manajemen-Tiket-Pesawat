#include "../header/constants.h"
#include "../header/types.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
void clearScreen() {
  // fungsi clearsecreen sesuaikan dengan  OS
}
string generateId(vector<Flight> &flights) {
  if (flights.empty())
    return "FL0";
  else
    return "FL" + to_string(stoi(flights.back().flightID.substr(2)) + 1);
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

bool isValidDateTime(const string &datetime) {
  tm t = {};
  istringstream ss(datetime);
  ss >> get_time(&t, "%Y-%m-%d %H:%M");
  if (ss.fail() || !ss.eof())
    return false;
  time_t now = time(0);
  tm *ltm = localtime(&now);
  int current_year = ltm->tm_year;

  if (t.tm_year > current_year) {
    return false;
  }

  int orig_hour = t.tm_hour;
  int orig_min = t.tm_min;
  int orig_mday = t.tm_mday;
  int orig_mon = t.tm_mon;
  int orig_year = t.tm_year;

  if (mktime(&t) == -1 || t.tm_hour != orig_hour || t.tm_min != orig_min ||
      t.tm_mday != orig_mday || t.tm_mon != orig_mon ||
      t.tm_year != orig_year) {
    return false;
  }

  return true;
}

bool haveSymbol(string username) {
  for (char c : username) {
    if (ispunct(c)) {
      return true;
    }
  }
  return false;
}

bool checkIsDigit(string &x) {
  for (char &c : x) {
    if (isdigit(c)) {
      return true;
    }
  }
  return false;
}
