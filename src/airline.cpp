#include "../header/airline.h"
#include "../header/fileHandler.h"
#include "../header/flight.h"
#include "../header/types.h"
#include "../header/utils.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <limits>
#include <string>
#include <thread>
#include <vector>
using namespace std;
using namespace chrono;
void airlineMenu(const User &userlogged, vector<User> &user,
                 vector<Flight> &flights, vector<Ticket> &ticket) {
  string inputUser;
  while (true) {
    this_thread::sleep_for(seconds(2));
    clearScreen();
    cout << "1. View Transaction" << endl;
    cout << "2. Add New Flight Schedule" << endl;
    cout << "3. Remove Flight" << endl;
    cout << "4. Edit Flight" << endl;
    cout << "5. View Flight" << endl;
    cout << "6. Exit" << endl;
    cout << "Input User : ";
    cin >> inputUser;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    sort(flights.begin(), flights.end(), [](const Flight &a, const Flight &b) {
      auto getNum = [](const string &s) {
        size_t pos = s.find_first_of("0123456789");
        return (pos != string::npos) ? stoi(s.substr(pos)) : 0;
      };
      return getNum(a.flightID) < getNum(b.flightID);
    });
    sort(ticket.begin(), ticket.end(), [](const Ticket &a, const Ticket &b) {
      auto getNum = [](const string &s) {
        size_t pos = s.find_first_of("0123456789");
        return (pos != string::npos) ? stoi(s.substr(pos)) : 0;
      };
      return getNum(a.ticketID) < getNum(b.ticketID);
    });

    refreshPendingTicket(ticket, flights);
    if (inputUser == "1") {
      viewTotalTransaction(flights, ticket, userlogged);
      cout << "Press Enter To Continue...";
      cin.get();
    } else if (inputUser == "2") {
      addFlightData(flights, userlogged);
    } else if (inputUser == "3") {
      deleteFlightData(flights, user, ticket, userlogged);
    } else if (inputUser == "4") {
      editFlightData(flights, user, userlogged);
    } else if (inputUser == "5") {
      viewFlight(flights, userlogged, user);
      cout << "Press Enter To Continue...";
      cin.get();
    } else if (inputUser == "6") {
      return;
    }
  }
}

void viewTotalTransaction(vector<Flight> &flights, vector<Ticket> &ticket,
                          const User &userlogged) {
  clearScreen();
  int sum = 0;

  sort(flights.begin(), flights.end(), [](const Flight &a, const Flight &b) {
    auto getNum = [](const string &s) {
      size_t pos = s.find_first_of("0123456789");
      return (pos != string::npos) ? stoi(s.substr(pos)) : 0;
    };
    return getNum(a.airlineUserID) < getNum(b.airlineUserID);
  });
  sort(ticket.begin(), ticket.end(), [](const Ticket &a, const Ticket &b) {
    auto getNum = [](const string &s) {
      size_t pos = s.find_first_of("0123456789");
      return (pos != string::npos) ? stoi(s.substr(pos)) : 0;
    };
    return getNum(a.flightID) < getNum(b.flightID);
  });

  auto startF = lower_bound(
      flights.begin(), flights.end(), userlogged.userId,
      [](const Flight &f, const string &id) { return f.airlineUserID < id; });
  auto endF = upper_bound(
      flights.begin(), flights.end(), userlogged.userId,
      [](const string &id, const Flight &f) { return id < f.airlineUserID; });

  for (auto itF = startF; itF != endF; ++itF) {
    auto startT = lower_bound(
        ticket.begin(), ticket.end(), itF->flightID,
        [](const Ticket &t, const string &fId) { return t.flightID < fId; });
    auto endT = upper_bound(
        ticket.begin(), ticket.end(), itF->flightID,
        [](const string &fId, const Ticket &t) { return fId < t.flightID; });

    int count = 0;
    for (auto itT = startT; itT != endT; ++itT) {
      if (itT->bookingStatus == "Paid") {
        sum += itF->price;
        count++;
      }
    }
    cout << "Flight " << itF->flightID << " | " << itF->origin << " -> "
         << itF->destination << " | Tickets Sold: " << count
         << " | Revenue: " << (count * itF->price) << "\n";
  }

  cout << "Total Revenue : " << sum << endl;
}

void addFlightData(vector<Flight> &flights, const User &userlogged) {
  clearScreen();
  string origin, dest, date_time;
  char inputUser;
  int price, capacity;
  cout << "Input Origin : ";
  getline(cin, origin);
  if (haveSymbol(origin) || checkIsDigit(origin)) {
    cout << "Origin Cannot Containt Symbol or Digit\n";
    return;
  }
  cout << "Input Destination : ";
  getline(cin, dest);
  if (haveSymbol(dest) || checkIsDigit(dest)) {
    cout << "Destination Cannot Containt Symbol or Digit\n";
    return;
  }
  cout << "Input Date Time (YYYY-MM-DD H:M): ";
  getline(cin, date_time);
  if (!(isValidDateTime(date_time))) {
    cout << "Failed, Wrong Date Time Format Or Date Is In The Past, Example "
            "(2026-03-10 23:59)\n";
    return;
  }
  cout << "Input Price : ";
  cin >> price;
  if (cin.fail()) {
    cout << "Failed, Price Must Integer\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return;
  } else if (price < 1) {
    cout << "Failed, Price Cannot Empty Or Mines\n";
    return;
  }
  cout << "Input Capacity : ";
  cin >> capacity;
  if (cin.fail()) {
    cout << "Failed, Capacity Must Integer\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return;
  } else if (capacity < 1) {
    cout << "Failed, Capacity Cannot Empty Or Mines\n";
    return;
  }
  cout << "Added New Flight(y/n)? : ";
  cin >> inputUser;
  if (inputUser == 'Y' || inputUser == 'y') {

    string id = generateId(flights);
    flights.emplace_back(id, userlogged.userId, origin, dest, date_time, price,
                         capacity);
    cout << "Added Flight Succesfull\n";
    saveFlightFile(flights);
  } else {
    cout << "Added Flight Canceled\n";
  }
}

void deleteFlightData(vector<Flight> &flights, const vector<User> &user,
                      const vector<Ticket> &ticket, const User &userlogged) {
  clearScreen();
  string inputId;
  char inputUser;
  if (userlogged.role == AIRLINE) {
    viewFlight(flights, userlogged, user);
    cout << "Input Flight Id : ";
    cin >> inputId;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    auto pos = lower_bound(flights.begin(), flights.end(), inputId,
                           [](const Flight &id, const string &inputId) {
                             return id.flightID < inputId;
                           });
    if (pos != flights.end() && pos->flightID == inputId &&
        pos->airlineUserID == userlogged.userId) {
      cout << "Flight Found : " << pos->flightID << " | " << pos->airlineUserID
           << endl;
      auto it = lower_bound(
          ticket.begin(), ticket.end(), inputId,
          [](const Ticket &a, const string &b) { return a.flightID < b; });
      if (it != ticket.end() && it->flightID == pos->flightID &&
          it->bookingStatus == "Paid") {
        cout << "Sorry, there is already a customer who has paid for the "
                "ticket\n";
        return;
      }
      cout << "Delete (y/n): ";
      cin >> inputUser;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      if (inputUser == 'y' || inputUser == 'Y') {
        cout << "Delete Flight Succesfull\n";
        flights.erase(pos);
        saveFlightFile(flights);
      } else {
        cout << "Delete Flight Canceled\n";
      }
    } else {
      cout << "Flight Id Not Found\n";
    }
  }
}

void editFlightData(vector<Flight> &flights, const vector<User> &user,
                    const User &userlogged) {
  clearScreen();
  string inputId;
  int price, capacity;
  char inputUser;
  viewFlight(flights, userlogged, user);
  cout << "Input Flight Id : ";
  cin >> inputId;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  auto pos = lower_bound(flights.begin(), flights.end(), inputId,
                         [](const Flight &id, const string &inputId) {
                           return id.flightID < inputId;
                         });
  if (pos != flights.end() && pos->flightID == inputId &&
      pos->airlineUserID == userlogged.userId) {
    cout << "Flight Found : " << pos->flightID << " | " << pos->airlineUserID
         << endl;
    cout << "Edit? (y/n): ";
    cin >> inputUser;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (inputUser == 'y' || inputUser == 'Y') {
      cout << "Input Capacity : ";
      cin >> capacity;
      if (cin.fail()) {
        cout << "Failed, Capacity Must Integer\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
      } else if (pos->capacity < 1) {
        cout << "Failed, Capacity Cannot Empty Or Mines\n";
        return;
      }
      pos->capacity = capacity;
      cout << "Edit Flight Succescull\n";
      saveFlightFile(flights);
    } else {
      cout << "Edit Flight Canceled\n";
    }
  } else {
    cout << "Flight Id Not Found\n";
  }
}
