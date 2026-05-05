#include "../header/customer.h"
#include "../header/fileHandler.h"
#include "../header/flight.h"
#include "../header/tabulate.hpp"
#include "../header/ticket.h"
#include "../header/types.h"
#include "../header/utils.h"
#include <algorithm>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
using namespace std;
using namespace tabulate;
using namespace chrono_literals;
using namespace chrono;

void customerMenu(const string username, vector<User> &user,
                  vector<Flight> &flights, vector<Ticket> &ticket) {
  string inputUser;

  while (true) {
    refreshPendingTicket(ticket, flights);
    cout << "Selamat Datang " << username << endl;
    cout << "1. Booking Ticket\n";
    cout << "2. Paying Ticket\n";
    cout << "3. Cancel Ticket\n";
    cout << "4. View Ticket History\n";
    cout << "5. Exit\n";
    cout << "Input User : ";
    cin >> inputUser;

    if (inputUser == "1") {
      viewFlight(flights, username, CUSTOMER);
      bookingTicket(flights, ticket, username, CUSTOMER);
    } else if (inputUser == "2") {
      payTicket(ticket, username);
    } else if (inputUser == "3") {
      cancelTicket(flights, ticket, username);
    } else if (inputUser == "4") {
      viewHistoryTicket(ticket, username, CUSTOMER);
    } else if (inputUser == "5") {
      return;
    }
  }
}

void bookingTicket(vector<Flight> &flights, vector<Ticket> &ticket,
                   const string username, Role role) {
  string inputUser;
  auto timeNow = chrono::system_clock::now();
  time_t t = chrono::system_clock::to_time_t(timeNow + hours(1));
  ostringstream oss;
  oss << put_time(localtime(&t), "%Y-%m-%d %H:%M");
  string timeZoned = oss.str();
  cout << "Input Flight Id\n";
  cin >> inputUser;
  auto pos = lower_bound(flights.begin(), flights.end(), inputUser,
                         [](const Flight &id, string inputUser) {
                           return id.flightID < inputUser;
                         });
  if (pos != flights.end() && pos->flightID == inputUser) {
    pos->displayInfo();
    if (pos->capacity >= 1) {
      inputUser.clear();
      cout << "Booking Ticket (y/n) : ";
      cin >> inputUser;
      if (inputUser == "Y" || inputUser == "y") {
        ticket.emplace_back(generateIdTicket(ticket), pos->flightID, username,
                            "Pending", "A" + to_string(pos->capacity),
                            timeZoned);
        (pos->capacity)--;
        saveTicketFile(ticket);
      } else
        cout << "Booking Canceled\n";
    } else
      cout << "Flight Id Not Found\n";
  }
  saveFlightFile(flights);
}

void payTicket(vector<Ticket> &ticket, const string username) {
  Table tableTicket;
  int i = 1;
  string inputUser;
  tableTicket.add_row({"No", "Ticket Id", "Flight Id", "Username",
                       "Ticket Status", "Seat Number", "Pending Limit"});
  for (auto &data : ticket) {
    if (data.customerName == username && data.bookingStatus == "Pending") {
      tableTicket.add_row({to_string(i), data.ticketID, data.flightID,
                           data.customerName, data.bookingStatus,
                           data.seatNumber, data.date});
      i++;
    }
  }

  if (i != 1) {
    cout << tableTicket << endl;
    cout << "Input Ticket Id : ";
    cin >> inputUser;
    auto pos = lower_bound(
        ticket.begin(), ticket.end(), inputUser,
        [](Ticket &id, string inputUser) { return id.ticketID < inputUser; });
    if (pos != ticket.end() && pos->ticketID == inputUser &&
        pos->bookingStatus == "Pending") {
      cout << "Pay Ticket ? (y/n) : ";
      cin >> inputUser;
      if (inputUser == "y" || inputUser == "Y") {
        cout << "Process....\n";
        this_thread::sleep_for(4s);
        cout << "Success\n";
        pos->bookingStatus = "Paid";
        saveTicketFile(ticket);
      } else
        cout << "Paying Canceled\n";
    }
  } else
    cout << "Ticket Id Not Found\n";
}

void cancelTicket(vector<Flight> &flights, vector<Ticket> &ticket,
                  const string username) {
  Table tableTicket;
  int i = 1;
  string inputUser;

  tableTicket.add_row({"No", "Ticket Id", "Flight Id", "Username",
                       "Ticket Status", "Seat Number", "Pending Limit"});
  for (auto &data : ticket) {
    if (data.customerName == username && data.bookingStatus == "Pending") {
      tableTicket.add_row({to_string(i), data.ticketID, data.flightID,
                           data.customerName, data.bookingStatus,
                           data.seatNumber, data.date});
      i++;
    }
  }
  if (i != 1) {
    cout << tableTicket << endl;
    cout << "Input Ticket Id : ";
    cin >> inputUser;
    auto posT = lower_bound(
        ticket.begin(), ticket.end(), inputUser,
        [](Ticket &id, string inputUser) { return id.ticketID < inputUser; });

    auto posF = lower_bound(flights.begin(), flights.end(), posT->flightID,
                            [](const Flight &id, string flightID) {
                              return id.flightID < flightID;
                            });

    if (posT != ticket.end() && posT->ticketID == inputUser &&
        posT->bookingStatus == "Pending" && posF != flights.end()) {

      cout << "Cancel Ticket ? (y/n) : ";
      cin >> inputUser;
      if (inputUser == "y" || inputUser == "Y") {
        cout << "Process....\n";
        this_thread::sleep_for(4s);
        cout << "Success\n";
        posT->bookingStatus = "Canceled";
        (posF->capacity)++;
        saveTicketFile(ticket);
        saveFlightFile(flights);
      } else
        cout << "Cancel Ticket Canceled\n";
    }
  } else
    cout << "Ticket Id Not Found \n";
}
