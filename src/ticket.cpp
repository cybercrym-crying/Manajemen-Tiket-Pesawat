#include "../header/ticket.h"
#include "../header/tabulate.hpp"
#include "../header/utils.h"
#include <iostream>
#include <vector>
using namespace std;
using namespace tabulate;

void viewHistoryTicket(vector<Ticket> &ticket, const string username,
                       Role role) {
  clearScreen();
  Table tableTicket;
  int i = 1;
  string inputUser;

  tableTicket.add_row({"No", "Ticket Id", "Flight Id", "Username",
                       "Ticket Status", "Seat Number", "Pending Limit"});

  if (role == CUSTOMER) {
    for (auto &data : ticket) {
      if (data.customerName == username) {
        tableTicket.add_row({to_string(i), data.ticketID, data.flightID,
                             data.customerName, data.bookingStatus,
                             data.seatNumber, data.date});
        i++;
      }
    }
  }

  else if (role == ADMIN) {
    for (auto &data : ticket) {
      tableTicket.add_row({to_string(i), data.ticketID, data.flightID,
                           data.customerName, data.bookingStatus,
                           data.seatNumber, data.date});
      i++;
    }
  }

  else if (role == AIRLINE) {
    for (auto &data : ticket) {
      if (data.customerName == username) {
        tableTicket.add_row({to_string(i), data.ticketID, data.flightID,
                             data.customerName, data.bookingStatus,
                             data.seatNumber, data.date});
        i++;
      }
    }
  } else if (i == 1)
    cout << "No Ticket History\n";

  cout << tableTicket << endl;
}
