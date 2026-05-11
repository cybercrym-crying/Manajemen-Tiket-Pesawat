#include "../header/auth.h"
#include "../header/fileHandler.h"
#include "../header/picosha2.h"
#include "../header/types.h"
#include "../header/utils.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <optional>
using namespace std;

std::optional<User> loginAccount(vector<User> &user) {
  clearScreen();
  string name, pass, salt = "s$ltsh4#@", checkHash;
  cin.ignore(1000, '\n');
  cout << "Input Name : ";
  getline(cin, name);
  cout << "Input Pass : ";
  getline(cin, pass);
  sort(user.begin(), user.end(),
       [](const User &a, const User &b) { return a.username < b.username; });
  auto pos = lower_bound(
      user.begin(), user.end(), name,
      [](const User &a, string username) { return a.username < username; });
  if (pos != user.end() && pos->username == name) {
    if (pos->isActive == false) {
      cout << "This Account Not Active\n";
      return std::nullopt;
    }
    checkHash = picosha2::hash256_hex_string(pass + salt);
    if (!(pos->password == checkHash)) {
      clearScreen();
      cout << "Wrong Password, Try Again!\n";
        return std::nullopt;
    }
    return *pos;
  } else {
    clearScreen();
    cout << "Account Not Found, Regist First\n";
    return std::nullopt;
  }
}

void registerAccount(vector<User> &user) {
  clearScreen();
  string name, pass, salt = "s$ltsh4#@";
  cin.ignore(1000, '\n');
  cout << "Input Name : ";
  getline(cin, name);
  cout << "Input Pass : ";
  getline(cin, pass);
  sort(user.begin(), user.end(),
       [](const User &a, const User &b) { return a.username < b.username; });
  auto it = lower_bound(
      user.begin(), user.end(), name,
      [](const User &a, const string &b) { return a.username < b; });

  if (it != user.end() && it->username == name) {
    cout << "Username Already User By Another User\n";
    return;
  }
  if (haveSymbol(name)) {
    cout << "Name Cannot Contain Symbol\n";
    cout << "Failed To Add Account\n";
    return;
  }

  else {
    pass = picosha2::hash256_hex_string(pass + salt);
    user.emplace_back(generateIdUser(user), name, pass, true, CUSTOMER);
    saveUserFile(user);
    cout << "Registration Succes\n";
    sort(user.begin(), user.end(),
         [](const User &a, const User &b) { return a.username < b.username; });
  }
}
