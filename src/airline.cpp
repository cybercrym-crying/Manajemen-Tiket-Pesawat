#include "../header/airline.h"
#include "../header/fileHandler.h"
#include "../header/flight.h"
#include "../header/types.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void airlineMenu(const string username, vector<User> &user,
                 vector<Flight> &flights, vector<Ticket> &ticket) {
  // tampilan menu airline pilihan aksi atau keluar aksi
}
void viewTotalTransaction(const string username) {
  // ambil data dari tiket.csv dan filter lalu cari sesuai flightsID
  // cek apakah airlane name sesuai dengan username
}

void createFlight(const string username, vector<Flight> &flights) {
  // lakun input  untuk menyimpan data di struct flight dan pastikan data sesuai
}
void deleteFlight(const string username, vector<Flight> &flights) {
  // lakukan input untuk id dan cek apakah id merupakan milik username airline
  // saat ini jika sesuai kirim flight.cpp untuk di delete
}
