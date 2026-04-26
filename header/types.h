#pragma once
#include <string>
using namespace std;

enum Role { ADMIN = 1, AIRLINE = 2, CUSTOMER = 3 };

struct User {
  string username;
  string password;
  bool isActive;
  Role role;
  User(string u, string p)
      : username(u), password(p), isActive(true), role(CUSTOMER) {}
};

struct Flight {
  string flightID;
  string airlineName;
  string destination;
  string time;
  int price;
  int capacity;
  Flight(string f, string a, string d, string t, int p, int c)
      : flightID(f), airlineName(a), destination(d), time(t), capacity(c) {}
};

struct Ticket {
  string ticketID;
  string flightID;
  string customerName;
  string bookingStatus;
  string seatNumber;
  string date;
  Ticket(string t, string f, string c, string b, string s, string d)
      : ticketID(t), flightID(f), customerName(c), bookingStatus(b),
        seatNumber(s), date(d) {}
};
