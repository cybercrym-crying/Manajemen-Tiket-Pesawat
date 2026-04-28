#include "../header/admin.h"
#include "../header/fileHandler.h"
#include "../header/flight.h"
#include "../header/ticket.h"
#include "../header/types.h"
#include <iostream>
#include <vector>

using namespace std;

void adminMenu(const string username, vector<User> &user,
               vector<Flight> &flights, vector<Ticket> &ticket) {

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
  // melihat semua list akun pada vector

};
void addNewAccount(vector<User> &user) {
  // menambahkan akun baru, pastikan input sudha di validasi
  // perbarui pada file csv dengan fungsi filehandler
};
void banUserAccount(vector<User> &user) {
  // melakukan perubahan status active akun user tertentu
  // perbarui pada file csv dengan fungsi filehandler
}
void removeUserAccount(vector<User> &user) {
  // menhapus akun user
  //  perbarui pada file csv dengan fungsi filehandler
}
