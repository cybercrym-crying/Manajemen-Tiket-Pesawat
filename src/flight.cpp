#include "../header/flight.h"
#include "../header/fileHandler.h"
#include "../header/tabulate.hpp"
#include "../header/types.h"
#include "../header/utils.h"
#include <algorithm>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;
using namespace tabulate;

void viewFlight(const vector<Flight> &flights, string username, Role role) {
  Table tableData;
  int i = 1;
  string inputDest, inputOri, inputUser;
  auto timeNow = chrono::system_clock::now();
  time_t t = chrono::system_clock::to_time_t(timeNow);
  ostringstream oss;
  oss << put_time(localtime(&t), "%Y-%m-%d %H:%M");
  string timeZoned = oss.str();
  cout << "1. View All Flight\n";
  cout << "2. Search Flight\n";
  cout << "Input User : ";
  cin >> inputUser;
  tableData.add_row({"No", "Flight Id", "Airline Name", "Origin", "Destination",
                     "Date Time", "Price", "Capacity"});
  if (inputUser == "1") {
    if (role == ADMIN) {
      for (auto &data : flights) {
        tableData.add_row({to_string(i), data.flightID, data.airlineName,
                           data.origin, data.destination, data.time,
                           to_string(data.price), to_string(data.capacity)});
        i++;
      }

    } else if (role == AIRLINE) {
      for (auto &data : flights) {
        if (data.airlineName == username) {
          tableData.add_row({to_string(i), data.flightID, data.airlineName,
                             data.origin, data.destination, data.time,
                             to_string(data.price), to_string(data.capacity)});
          i++;
        }
      }
    } else {
      for (auto &data : flights) {
        if (data.time > timeZoned) {
          tableData.add_row({to_string(i), data.flightID, data.airlineName,
                             data.origin, data.destination, data.time,
                             to_string(data.price), to_string(data.capacity)});
          i++;
        }
      }
    }
  }

  else if (inputUser == "2") {
    cout << "Input Origin : \n";
    cin >> inputOri;
    cout << "Input Destination : \n";
    cin >> inputDest;

    if (role == ADMIN) {
      for (auto &data : flights) {
        if (inputDest == data.destination && data.origin == inputOri) {
          tableData.add_row({to_string(i), data.flightID, data.airlineName,
                             data.origin, data.destination, data.time,
                             to_string(data.price), to_string(data.capacity)});
          i++;
        }
      }
    }

    else if (role == AIRLINE) {
      for (auto &data : flights) {
        if (data.airlineName == username && data.origin == inputOri &&
            data.destination == inputDest) {
          tableData.add_row({to_string(i), data.flightID, data.airlineName,
                             data.origin, data.destination, data.time,
                             to_string(data.price), to_string(data.capacity)});
          i++;
        }
      }
    }

    else {

      for (auto &data : flights) {
        if (data.time > timeZoned && data.destination == inputDest &&
            data.origin == inputOri) {
          tableData.add_row({to_string(i), data.flightID, data.airlineName,
                             data.origin, data.destination, data.time,
                             to_string(data.price), to_string(data.capacity)});
          i++;
        }
      }
    }
  }

  if (i == 1) {
    cout << "Flight Not Found\n";
  } else {
    cout << tableData << endl;
  }
}
void addFlightData(vector<Flight> &flights, const string username) {
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
void deleteFlightData(vector<Flight> &flights, const string username,
                      Role role) {

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

void editFlightData(vector<Flight> &flights, const string username, Role role) {

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
          cerr << "Capacity Must Be Integet Not Alfabet\n";
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
