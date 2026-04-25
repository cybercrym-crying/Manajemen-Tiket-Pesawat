#pragma once
#include <string>
using namespace std;

enum Role { ADMIN = 1, AIRLINE = 2, CUSTOMER = 3 };

struct User {
  string username;
  string password;
  bool isActive;
  Role role;
};

struct Flight {
  string flightID;
  string airlineName;
  string destination;
  string time;
  int price;
  int capacity;
};

struct Ticket {
  string ticketID;
  string flightID;
  string customerName;
  string bookingStatus;
  string seatNumber;
};
