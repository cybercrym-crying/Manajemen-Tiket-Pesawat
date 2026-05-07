#include "../header/flight.h"
#include "../header/tabulate.hpp"
#include "../header/types.h"
#include "../header/utils.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
using namespace tabulate;

void viewFlight(const vector<Flight> &flights, const User &userlogged) {
  clearScreen();
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
    if (userlogged.role == ADMIN) {
      for (auto &data : flights) {
        tableData.add_row({to_string(i), data.flightID, data.airlineUserID,
                           data.origin, data.destination, data.departureTime,
                           to_string(data.price), to_string(data.capacity)});
        i++;
      }

    } else if (userlogged.role == AIRLINE) {
      for (auto &data : flights) {
        if (data.airlineUserID == userlogged.userId) {
          tableData.add_row({to_string(i), data.flightID, data.airlineUserID,
                             data.origin, data.destination, data.departureTime,
                             to_string(data.price), to_string(data.capacity)});
          i++;
        }
      }
    } else {
      for (auto &data : flights) {
        if (data.departureTime > timeZoned) {
          tableData.add_row({to_string(i), data.flightID, data.airlineUserID,
                             data.origin, data.destination, data.departureTime,
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

    if (userlogged.role == ADMIN) {
      for (auto &data : flights) {
        if (inputDest == data.destination && data.origin == inputOri) {
          tableData.add_row({to_string(i), data.flightID, data.airlineUserID,
                             data.origin, data.destination, data.departureTime,
                             to_string(data.price), to_string(data.capacity)});
          i++;
        }
      }
    }

    else if (userlogged.role == AIRLINE) {
      for (auto &data : flights) {
        if (data.airlineUserID == userlogged.userId &&
            data.origin == inputOri && data.destination == inputDest) {
          tableData.add_row({to_string(i), data.flightID, data.airlineUserID,
                             data.origin, data.destination, data.departureTime,
                             to_string(data.price), to_string(data.capacity)});
          i++;
        }
      }
    }

    else {

      for (auto &data : flights) {
        if (data.departureTime > timeZoned && data.destination == inputDest &&
            data.origin == inputOri) {
          tableData.add_row({to_string(i), data.flightID, data.airlineUserID,
                             data.origin, data.destination, data.departureTime,
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
