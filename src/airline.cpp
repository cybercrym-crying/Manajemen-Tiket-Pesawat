#include "../header/airline.h"
#include "../header/fileHandler.h"
#include "../header/flight.h"
#include "../header/types.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// using namespace std;

// tampilan menu airline pilihan aksi atau keluar aksi
void airlineMenu(const string username, vector<User> &user,
                 vector<Flight> &flights, vector<Ticket> &ticket) {
  std::cout << "1. Transaksi" << std::endl;
  std::cout << "2. Penerbangan Baru" << std::endl;
  std::cout << "3. delete" << std::endl;
  std::cout << "4. View Flight" << std::endl;

}

  // ambil data dari tiket.csv dan filter lalu cari sesuai flightsID
  // cek apakah airlane name sesuai dengan username
void viewTotalTransaction(const string username) {
  fstream fin;

  fin.open(data/ticket.csv, ios::in);

}

void createFlight(const string username, vector<Flight> &flights) {
  // lakun input  untuk menyimpan data di struct flight dan pastikan data sesuai
}
void deleteFlight(const string username, vector<Flight> &flights) {
  // lakukan input untuk id dan cek apakah id merupakan milik username airline
  // saat ini jika sesuai kirim flight.cpp untuk di delete
}
