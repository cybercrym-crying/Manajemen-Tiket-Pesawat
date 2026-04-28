#include "../header/fileHandler.h"
#include "../header/types.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;
int loadFile(vector<User> &user, vector<Ticket> &ticket,
             vector<Flight> &flights) {
  ifstream accountFile("data/account.csv");
  ifstream flightFile("data/flight.csv");
  ifstream ticketFile("data/ticket.csv");
  string line, word, header;
  stringstream ss;
  bool isActive;
  Role role;
  vector<string> temp;
  if (!(accountFile.is_open() && flightFile.is_open() &&
        ticketFile.is_open())) {
    return -1;
  } else {
    if (getline(accountFile, header)) {
    }
    while (getline(accountFile, line)) {
      stringstream ss(line);
      while (getline(ss, word, ',')) {
        temp.emplace_back(word);
      }
      if (temp[2] == "true") {
        isActive = true;
      } else {
        isActive = false;
      }
      if (temp[3] == "ADMIN") {
        role = ADMIN;
      } else if (temp[3] == "AIRLINE") {
        role = AIRLINE;
      } else {
        role = CUSTOMER;
      }
      user.emplace_back(temp[0], temp[1], isActive, role);
      temp.clear();
    }

    if (getline(flightFile, header)) {
    }
    while (getline(flightFile, line)) {
      stringstream ss(line);
      string word;
      while (getline(ss, word, ',')) {
        temp.emplace_back(word);
      }
      flights.emplace_back(temp[0], temp[1], temp[2], temp[3], stoi(temp[4]),
                           stoi(temp[5]));
      temp.clear();
    }

    if (getline(ticketFile, header)) {
    }
    while (getline(ticketFile, line)) {
      stringstream ss(line);
      string word;
      while (getline(ss, word, ',')) {
        temp.emplace_back(word);
      }
      ticket.emplace_back(temp[0], temp[1], temp[2], temp[3], temp[4], temp[5]);
      temp.clear();
    }
    accountFile.close();
    flightFile.close();
    ticketFile.close();
    return 0;
  }
}

void saveUserFile(vector<User> &user) {
  ofstream userFile("data/account.csv");
  string role;
  if (!(userFile.is_open()))
    return;

  else {
    userFile << "username" << ',' << "password" << ',' << "isActive" << ','
             << "role\n";
    for (const auto &dataUser : user) {
      if (dataUser.role == ADMIN) {
        role = "ADMIN";
      } else if (dataUser.role == AIRLINE) {
        role = "AIRLINE";
      } else {
        role = "CUSTOMER";
      }
      userFile << dataUser.username << ',' << dataUser.password << ','
               << (dataUser.isActive ? "true" : "false") << ',' << (role)
               << '\n';
    }
    userFile.close();
  }
}
void saveFlightFile(vector<Flight> &flight) {
  ofstream flightFile("data/flight.csv");
  if (!(flightFile.is_open()))
    return;

  else {
    for (const auto &dataFlight : flight) {
      flightFile << dataFlight.flightID << ',' << dataFlight.airlineName << ','
                 << dataFlight.destination << ',' << dataFlight.time << ','
                 << dataFlight.price << ',' << dataFlight.capacity << '\n';
    }
    flightFile.close();
  }
}
void saveTicketFile(vector<Ticket> &ticket) {
  ofstream ticketFile("data/ticket.csv");
  if (!(ticketFile.is_open()))
    return;

  else {
    for (const auto &dataTicket : ticket) {
      ticketFile << dataTicket.ticketID << ',' << dataTicket.flightID << ','
                 << dataTicket.customerName << ',' << dataTicket.bookingStatus
                 << ',' << dataTicket.seatNumber << ',' << dataTicket.date
                 << '\n';
    }
    ticketFile.close();
  }
}
