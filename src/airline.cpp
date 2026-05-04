#include "../header/airline.h"
#include "../header/fileHandler.h"
#include "../header/flight.h"
#include "../header/types.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// using namespace std;


// tampilan menu airline pilihan aksi atau keluar aksi
void airlineMenu(const string username, vector<User> &user,
                 vector<Flight> &flights, vector<Ticket> &ticket) {
  std::cout << "1. Transaction" << std::endl;
  std::cout << "2. New Flight Schedule" << std::endl;
  std::cout << "3. Remove Flight" << std::endl;
  std::cout << "4. View Flight" << std::endl;
}

std::vector<Ticket> ticketlist;

// ambil data dari tiket.csv dan filter lalu cari sesuai flightsID
// cek apakah airlane name sesuai dengan username
void viewTotalTransaction(const string username) {
  fstream fin;

  fin.open("data/ticket.csv", ios::in); //ambil data tiket

  string line;
  getline(fin, line);

  while(std::getline(fin, line)){
    std::stringstream ss(line);
    std::string token;
    Ticket t;

    std::getline(ss, token, ','); 
    t.flightID = stoi(token);
    std::getline(ss, t.customerName, ',');
    std::getline(ss, t.flightID, ',');
    std::getline(ss, t.seatNumber, ',');
    std::getline(ss, t.date);

    ticketlist.push_back(t);
  }

  for (auto& t : ticketlist) {
    if (t.customerName == username){
      std::cout << "Flight ID : " << t.flightID << "\n";
      std::cout << "Name      : " << t.customerName << "\n";
      std::cout << "SeatNumber: " << t.seatNumber << "\n";
      std::cout << "Date : " << t.date << "\n";

    }
  }

  fin.close();

  
}

void createFlight(const string username, vector<Flight> &flights) {
  // lakun input  untuk menyimpan data di struct flight dan pastikan data sesuai
}
void deleteFlight(const string username, vector<Flight> &flights) {
  // lakukan input untuk id dan cek apakah id merupakan milik username airline
  // saat ini jika sesuai kirim flight.cpp untuk di delete
}
