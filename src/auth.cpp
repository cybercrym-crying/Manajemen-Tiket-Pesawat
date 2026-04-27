#include "../header/auth.h"
#include "../header/fileHandler.h"
#include "../header/picosha2.h"
#include "../header/types.h"
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
User *loginAccount(vector<User> &user) {
  string name, pass, salt = "s$ltsh4#@", checkHash;
  cin.ignore(1000, '\n');
  cout << "Input Name : ";
  getline(cin, name);
  cout << "Input Pass : ";
  getline(cin, pass);
  auto pos = lower_bound(
      user.begin(), user.end(), name,
      [](const User &a, string username) { return a.username < username; });
  if (pos != user.end() && pos->username == name) {
    checkHash = picosha2::hash256_hex_string(pass + salt);
    if (!(pos->password == checkHash)) {
      return nullptr;
    }
    return &(*pos);
  } else {
    cout << "Account Not Found, Regist First\n";
    return nullptr;
  }
}
void registerAccount(vector<User> &user) {
  string name, pass, salt = "s$ltsh4#@";
  bool inUse;
  cin.ignore(1000, '\n');
  cout << "Input Name : ";
  getline(cin, name);
  cout << "Input Pass : ";
  getline(cin, pass);
  inUse = binary_search(
      user.begin(), user.end(), name,
      [](const User &a, const string &b) { return a.username < b; });

  if (inUse) {
    cout << "Username Already User By Another User\n";
    return;
  } else {
    pass = picosha2::hash256_hex_string(pass + salt);
    user.push_back({name, pass});
    saveUserFile(user);
    cout << "Registration Succes\n";
    sort(user.begin(), user.end(),
         [](const User &a, const User &b) { return a.username < b.username; });
  }
}
