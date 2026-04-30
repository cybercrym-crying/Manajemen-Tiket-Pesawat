#include "../header/admin.h"
#include "../header/fileHandler.h"
#include "../header/flight.h"
#include "../header/picosha2.h"
#include "../header/tabulate.hpp"
#include "../header/ticket.h"
#include "../header/types.h"
#include "../header/utils.h"
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using namespace std;
void adminMenu(const string username, vector<User> &user,
               vector<Flight> &flights, vector<Ticket> &ticket) {
  sort(user.begin(), user.end(),
       [](const User &a, const User &b) { return a.username < b.username; });
  int inputUser;
  bool running = true;
  while (running) {
    cout << "Greeting " << username << endl;
    cout << "1. View List Account\n";
    cout << "2. Add New Account\n";
    cout << "3. Ban User Account \n";
    cout << "4. Remove User Account\n";
    cout << "5. View List Flight\n";
    cout << "6. View List Ticket Order\n";
    cout << "7. Exit\n";
    cout << "Input : ";
    cin >> inputUser;

    if (cin.fail())
      continue;
    switch (inputUser) {
    case 1:
      viewListAccount(user);
      break;
    case 2:
      addNewAccount(user);
      break;
    case 3:
      banUserAccount(user);
      break;
    case 4:
      removeUserAccount(user);
      break;
    case 5:
      viewFlight(flights, username, ADMIN);
      break;
    case 6:
      viewHistoryTicket(ticket, username, ADMIN);
      break;
    case 7:
      running = false;
    default:
      cout << "Not In Option\n";
    }
  }
}

void viewListAccount(const vector<User> &user) {
  tabulate::Table tableAccount;
  tableAccount.add_row(
      {"No", "Username", "Password", "Account Status", "Role Account"});
  int i = 1;
  string role;
  for (auto data : user) {
    tableAccount.add_row({to_string(i), data.username, data.password,
                          string(data.isActive ? "Active" : "Inactive"),
                          toStringRole(data.role)});
    i++;
  }
  cout << tableAccount << endl;
}

void addNewAccount(vector<User> &user) {
  string username, password, salt = "s$ltsh4#@";
  ;
  cin.ignore(1000, '\n');
  cout << "Input Airline Name : ";
  getline(cin, username);
  if (haveSymbol(username)) {
    cout << "Name Cannot Contain Symbol\n";
    cout << "Failed To Add Account\n";
    return;
  }
  cout << "Input Password : ";
  getline(cin, password);
  user.emplace_back(username, picosha2::hash256_hex_string(password + salt),
                    true, AIRLINE);
  saveUserFile(user);
}

void banUserAccount(vector<User> &user) {
  string username;
  char inputUser;
  viewListAccount(user);
  cin.ignore(1000, '\n');
  cout << "Input Username : ";
  getline(cin, username);
  auto pos = lower_bound(
      user.begin(), user.end(), username,
      [](const User &a, string username) { return a.username < username; });
  if (pos != user.end() && pos->username == username) {
    cout << "Account Found : " << pos->username << endl;

    cout << "1. Ban Acccount\n";
    cout << "2. Unban Account\n";
    cout << "3. Exit\n";
    cout << "Input Menu : ";
    cin >> inputUser;
    if (inputUser == '1') {
      cout << "Ban Account (y/n) : ";
      cin >> inputUser;
      if (inputUser == 'Y' || inputUser == 'y') {
        pos->isActive = false;
        cout << "Account Banned\n";
        saveUserFile(user);
      } else {
        cout << "Failed Banned\n";
      }
    } else if (inputUser == '2') {
      cout << "Unban Account (y/n) : ";
      cin >> inputUser;
      if (inputUser == 'Y' || inputUser == 'y') {
        pos->isActive = true;
        cout << "Account Unban\n";
        saveUserFile(user);

      } else {
        cout << "Failed To Unban\n";
      }
    } else {
      return;
    }
  }

  else {
    cout << "Account Not Found\n";
  }
}

void removeUserAccount(vector<User> &user) {
  string username;
  char inputUser;
  viewListAccount(user);
  cin.ignore(1000, '\n');
  cout << "Input Username : ";
  getline(cin, username);
  auto pos = lower_bound(
      user.begin(), user.end(), username,
      [](const User &a, string username) { return a.username < username; });
  if (pos != user.end() && pos->username == username) {
    cout << "Account Found : " << pos->username << endl;
    cout << "Remove Account (y/n) ?\n";
    cin >> inputUser;
    if (inputUser == 'Y' || inputUser == 'y') {
      user.erase(pos);
      cout << "Account Remove\n";
      saveUserFile(user);
    } else {
      cout << "Failed To Remove\n";
    }
  } else {
    cout << "Account Not Found\n";
  }
}
