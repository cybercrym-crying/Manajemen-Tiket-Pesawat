#include "../header/customer.h"
#include "../header/constants.h"
#include "../header/fileHandler.h"
#include "../header/flight.h"
#include "../header/ticket.h"
#include "../header/types.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void customerMenu(const string username, vector<User> &user,
                  vector<Flight> &flights, vector<Ticket> &ticket) {

  std::cout << "Berhasil";
}

void bookingTicket(const string username) {
  //  minta input dulu user  mau kemana
  //  tampilkan jadwal flight sesaui destinasi
  //  minta input user berupa flightID dan jumlah
  // jika berhasil maka panggil book ticket dari ticket.h
}
void payTicket(const string username) {
  // tampilkan ticket yang pending
  // input nomor ticket yang mau di bayar
  // simulasikan pembayaran
  // panggil payingTIcket dari ticket.h
}

bool cancelTicket(const string username) {
  // perlihatkan ticket yang di pesan
  // masukan input nomor ticket yang ingin di batalkan
  // pangggil cancelTicket dari ticket.h
  return true;
}
void updateAccount(vector<User> &user, const string username) {
  // minta input nama,password yang baru kosongkan jika tidak mau bangung logic
  // nya
}
