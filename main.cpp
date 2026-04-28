#include "header/admin.h"
#include "header/airline.h"
#include "header/auth.h"
#include "header/constants.h"
#include "header/customer.h"
#include "header/fileHandler.h"
#include "header/types.h"
#include <iostream>
#include <vector>
using namespace std;

void mainMenu(vector<User> &user, vector<Flight> &flights,
              vector<Ticket> &ticket) {
  string input;
  while (true) {
    cout << "1. Login\n";
    cout << "2. Register\n";
    cout << "3. Exit\n";
    cout << "Input : ";
    cin >> input;
    if (input == "1") {
      User *userLogged = loginAccount(user);
      if (userLogged) {
        if (userLogged->role == ADMIN)
          adminMenu(userLogged->username, user, flights, ticket);
        if (userLogged->role == CUSTOMER)
          customerMenu(userLogged->username, user, flights, ticket);
        if (userLogged->role == AIRLINE)
          airlineMenu(userLogged->username, user, flights, ticket);
      }
    } else if (input == "2") {
      registerAccount(user);
    } else if (input == "3") {
      exit(0);
    }
  }
};

int main() {
  vector<User> user;
  vector<Flight> flights;
  vector<Ticket> ticket;
  int file = loadFile(user, ticket, flights);
  if (file == -1) {
    cout << "Failed To Load database\n";
    return -1;
  }
  mainMenu(user, flights, ticket);
  return 0;
}
