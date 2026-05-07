#include "../header/airline.h"
#include "../header/fileHandler.h"
#include "../header/flight.h"
#include "../header/types.h"
#include "../header/utils.h"
#include <algorithm>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

void airlineMenu(const string username, vector<User> &user,
                 vector<Flight> &flights, vector<Ticket> &ticket) {
  string inputUser;
  while (true) {
    cout << "1. View Transaction" << endl;
    cout << "2. Add New Flight Schedule" << endl;
    cout << "3. Remove Flight" << endl;
    cout << "4. View Flight" << endl;
    cout << "Input User : ";
    cin >> inputUser;
    if (inputUser == "1") {
      viewTotalTransaction(flights, ticket, username);
    } else if (inputUser == "2") {
      addFlightData(flights, username);
    } else if (inputUser == "3") {
      deleteFlightData(flights, username, AIRLINE);
    } else if (inputUser == "4") {
      viewFlight(flights, username, AIRLINE);
    } else if (inputUser == "5") {
      return;
    }
  }
}

void viewTotalTransaction(vector<Flight> &flights, vector<Ticket> &ticket,
                          const string username) {
  int sum = 0;

  sort(flights.begin(), flights.end(), [](const Flight &a, const Flight &b) {
    return a.airlineName < b.airlineName;
  });

  sort(ticket.begin(), ticket.end(), [](const Ticket &a, const Ticket &b) {
    return a.flightID < b.flightID;
  });

  // Pakai lower_bound + upper_bound sebagai pengganti equal_range
  auto startF = lower_bound(flights.begin(), flights.end(), username,
                            [](const Flight &f, const string &uname) {
                              return f.airlineName < uname;
                            });
  auto endF = upper_bound(flights.begin(), flights.end(), username,
                          [](const string &uname, const Flight &f) {
                            return uname < f.airlineName;
                          });

  for (auto itF = startF; itF != endF; ++itF) {

    auto startT = lower_bound(
        ticket.begin(), ticket.end(), itF->flightID,
        [](const Ticket &t, const string &fId) { return t.flightID < fId; });
    auto endT = upper_bound(
        ticket.begin(), ticket.end(), itF->flightID,
        [](const string &fId, const Ticket &t) { return fId < t.flightID; });

    for (auto itT = startT; itT != endT; ++itT) {
      sum += itF->price;
    }
  }

  cout << "Total Transaction : " << sum << endl;
}
void addFlightData(vector<Flight> &flights, const string &username) {
  string id = generateId(flights);
  string origin, dest, date_time;
  int price, capacity;
  auto timeNow = chrono::system_clock::now();
  time_t t = chrono::system_clock::to_time_t(timeNow);
  ostringstream oss;
  oss << put_time(localtime(&t), "%Y-%m-%d %H:%M");
  string timeZoned = oss.str();
  cin.ignore(1000, '\n');
  cout << "Input Origin : ";
  getline(cin, origin);
  cout << "Input Destination : ";
  getline(cin, dest);
  cout << "Input Date Time (YYYY-MM-DD H:M): ";
  getline(cin, date_time);
  if (!(isValidDateTime(date_time))) {
    cout << "Failed, Wrong Date Time Format, Example (2026-03-10 23:59)\n";
    return;
  }
  cout << "Input Price : ";
  cin >> price;
  if (cin.fail()) {
    cout << "Failed, Price Must Integer\n";
    cin.clear();
    return;
  }
  cout << "Input Capacity : ";
  cin >> capacity;
  if (cin.fail()) {
    cout << "Failed, Capacity Must Integer\n";
    cin.clear();
    return;
  }
  flights.emplace_back(id, username, origin, dest, date_time, price, capacity);
  saveFlightFile(flights);
}

void deleteFlightData(vector<Flight> &flights, const string &username,
                      const Role &role) {

  string inputId;
  char inputUser;
  if (role == AIRLINE) {
    viewFlight(flights, username, role);
    cout << "Input Flight Id : ";
    cin >> inputId;
    auto pos = lower_bound(
        flights.begin(), flights.end(), inputId,
        [](const Flight &id, string inputId) { return id.flightID < inputId; });
    if (pos != flights.end() && pos->flightID == inputId &&
        pos->airlineName == username) {
      cout << "Flight Found : " << pos->flightID << " | " << pos->airlineName
           << endl;
      cout << "Delete (y/n): ";
      cin >> inputUser;
      if (inputUser == 'y' || inputUser == 'Y') {
        flights.erase(pos);
        saveFlightFile(flights);
      } else {
        cout << "Delete Flight Canceled\n";
      }
    } else
      cout << "Flight Id Not Found\n";
  }
}

void editFlightData(vector<Flight> &flights, const string &username,
                    Role &role) {
  string inputId;
  string ori, dest, price, capacity;
  char inputUser;
  viewFlight(flights, username, role);
  cout << "Input Flight Id : ";
  cin >> inputId;
  auto pos = lower_bound(
      flights.begin(), flights.end(), inputId,
      [](const Flight &id, string inputId) { return id.flightID < inputId; });
  if (pos != flights.end() && pos->flightID == inputId &&
      pos->airlineName == username) {
    cout << "Flight Found : " << pos->flightID << " | " << pos->airlineName
         << endl;
    cout << "Edit? (y/n): ";
    cin >> inputUser;
    if (inputUser == 'y' || inputUser == 'Y') {
      cin.ignore(1000, '\n');
      cout << "Enter if you don't want to change!!";
      cout << "Input Origin : ";
      getline(cin, ori);
      cout << "Input Destination : ";
      getline(cin, dest);
      cout << "Input Price : ";
      getline(cin, price);
      cout << "Input Capacity";
      getline(cin, capacity);
      if (!(ori.empty()) && checkIsDigit(ori) == false) {
        pos->origin = ori;
      }
      if (!(dest.empty()) && checkIsDigit(dest) == false) {
        pos->destination = dest;
      }
      if (!(price.empty())) {
        try {
          if (stoi(price) < 0) {
            throw runtime_error("Mines Price Not Possible\n");
          }
          pos->price = stoi(price);
        } catch (const invalid_argument &e) {
          cerr << "Price Must Be Integet Not Alfabet\n";
        } catch (const out_of_range &e) {
          cerr << "Input To Large\n";
        } catch (const runtime_error &e) {
          cerr << e.what() << endl;
        }
      }

      if (!(capacity.empty())) {
        try {
          if (stoi(capacity) < 0) {
            throw runtime_error("Mines Seat Capacity Not Possible\n");
          }
          pos->capacity = stoi(capacity);
        } catch (const invalid_argument &e) {
          cerr << "Capacity Must Be Integer Not Alfabet\n";
        } catch (const out_of_range &e) {
          cerr << "Input To Large\n";
        } catch (const runtime_error &e) {
          cerr << e.what() << endl;
        }
      }

      saveFlightFile(flights);
    } else {
      cout << "Edit Flight Canceled\n";
    }
  } else
    cout << "Flight Id Not Found \n";
}
