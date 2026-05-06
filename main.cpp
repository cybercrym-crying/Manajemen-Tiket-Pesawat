#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NOUSER
#define NOMCX
#define NOIME
#define NOMINMAX
// Override byte sebelum windows.h masuk
#define byte win_byte
#include <windows.h>
#undef byte
#endif

#include "header/admin.h"
#include "header/airline.h"
#include "header/auth.h"
#include "header/customer.h"
#include "header/fileHandler.h"
#include "header/types.h"
#include <clocale>
#include <iostream>
#include <locale>
#include <vector>
using namespace std;
const string C = "LC_ALL=C";
void mainMenu(vector<User> &user, vector<Flight> &flights,
              vector<Ticket> &ticket) {
  putenv("LC_ALL=C");
  setlocale(LC_ALL, "C");

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
