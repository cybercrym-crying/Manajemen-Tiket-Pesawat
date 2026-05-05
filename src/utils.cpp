#include "../header/fileHandler.h"
#include "../header/types.h"
#include <algorithm>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
using namespace chrono;
void clearScreen() {
  // fungsi clearsecreen sesuaikan dengan  OS
}

void refreshPendingTicket(vector<Ticket> &ticket, vector<Flight> &flights) {
  string statusP = "Pending";
  auto timeNow = chrono::system_clock::now();
  time_t t = chrono::system_clock::to_time_t(timeNow);
  ostringstream oss;
  oss << put_time(localtime(&t), "%Y-%m-%d %H:%M");
  string timeZone = oss.str();
  sort(ticket.begin(), ticket.end(), [](const Ticket &a, const Ticket &b) {
    return a.bookingStatus < b.bookingStatus;
  });
  auto pos = lower_bound(ticket.begin(), ticket.end(), statusP,
                         [](const Ticket &status, const string &statusP) {
                           return status.bookingStatus < statusP;
                         });
  while (pos != ticket.end() && pos->bookingStatus == statusP) {
    if (pos->date < timeZone) {
      auto posF = lower_bound(flights.begin(), flights.end(), pos->flightID,
                              [](const Flight &id, const string &flightId) {
                                return id.flightID < flightId;
                              });
      if (posF != flights.end() && pos->flightID == posF->flightID) {
        (posF->capacity)++;
        pos->bookingStatus = "Canceled";
      }
    }
    pos++;
  }
  sort(ticket.begin(), ticket.end(), [](const Ticket &a, const Ticket &b) {
    return a.ticketID < b.ticketID;
  });
  saveFlightFile(flights);
  saveTicketFile(ticket);
}

string generateId(vector<Flight> &flights) {
  if (flights.empty())
    return "FL1";
  else
    return "FL" + to_string(stoi(flights.back().flightID.substr(2)) + 1);
}

string generateIdTicket(vector<Ticket> &ticket) {
  if (ticket.empty())
    return "TIX1";
  else
    return "TIX" + to_string(stoi(ticket.back().ticketID.substr(3)) + 1);
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
