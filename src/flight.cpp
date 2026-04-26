#include "../header/flight.h"
#include "../header/types.h"
#include <string>
#include <vector>
using namespace std;

void viewFlight(const vector<Flight> &flights, string username, Role role) {
  // dapat melihat penerbangan yang sudah di buat, jika role admin dapat melihat
  // semuanya jika role airline dapat melihat jadwal penerbangan dirinya
  // role customer dapat melihat jadwal penerbangan yang tersedia mulai hari ini
}
void searchFlight(const vector<Flight> &flights, string destination) {
  // role admin dapat mencari dan melihat semua penerbangan
  // role customer hanya mencari dan melihat penerbangan yang tersedia
}
bool addFlightData(vector<Flight> &flights, Flight &dataFlights) {
  // generate ID flights
  // jika semua sesaui dan lancar return true, jika tidak return false
  return true;
}
bool deleteFlightData(vector<Flight> &flights, string &idFlights) {
  // lakukan penghapusan sesuai dengan id yang diterima pada vector
  // jika tidak ada return false, jika ada return true
  return true;
}
bool editFlightData(vector<Flight> &flights, Flight &dataFlights) {
  // lakukan timpa vector sesuai dengan id pada dataFlights
  // jika tidak ada return false, jika ada return true
  return true;
}
