#pragma once
#include <string>
#include <vector>
using namespace std;

enum Role { ADMIN = 1, AIRLINE = 2, CUSTOMER = 3 };

struct User {
  string username;
  string password;
  bool isActive;
  Role role;

  // User() {}
  User(string u, string p, bool i, Role r)
      : username(u), password(p), isActive(i), role(r) {}
};

struct Flight {
  string flightID;
  string airlineName;
  string destination;
  string time;
  int price;
  int capacity;

  // Flight() {} // saran ku tambahin aja, biar file csv bisa ngisi
  Flight(string f, string a, string d, string t, int p, int c)
      : flightID(f), airlineName(a), destination(d), time(t), price(p),
        capacity(c) {}
};

struct Ticket {
  string ticketID;
  string flightID;
  string customerName;
  string bookingStatus;
  string seatNumber;
  string date;

  Ticket() {} // -> default constructor
  Ticket(string t, string f, string c, string b, string s, string d)
      : ticketID(t), flightID(f), customerName(c), bookingStatus(b),
        seatNumber(s), date(d) {}
};

/*Aku tambahin default constructor, jadi datanya kosong dulu untuk sementara
  nanti pas file .csv kita panggil baru nilai di isi sama file*/

/*Ketimbang kita tampung di variabel biasa*/