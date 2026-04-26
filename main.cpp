#include "header/auth.h"
#include "header/fileHandler.h"
#include "header/types.h"
#include <iostream>
#include <vector>
using namespace std;

void mainMenu(vector<User> &user) {
  string input;
  while (true) {
    cout << "1. Login\n";
    cout << "2. Register\n";
    cout << "3. Exit\n";
    if (input == "1")
      loginAccount(user);
    else if (input == "2")
      registerAccount(user);
    else if (input == "3")
      exit(0);
  }
};

int main() {
  vector<User> user;
  vector<Flight> flights;
  vector<Ticket> ticket;
  loadFile(user, ticket, flights);
  mainMenu(user);
  return 0;
}
