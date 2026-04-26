#include "../header/ticket.h"
#include "../header/fileHandler.h"
#include <iostream>
#include <vector>
using namespace std;
void bookTicket(string username, int amountTicket, vector<Ticket> &ticket,
                vector<Flight> &flights) {
  // tambahkan informasi ticket pada vector ticket dan kurangi jumlah seat pada
  // flight sesuai dengan jumlah seat yang di pesan
  // pastikan status masih pending
}

void paymentTicket(string ticketID, vector<Ticket> &ticket) {
  // lakukan perubahan status sesuai dengan nomor ticket
  //  pada nomor ticket yang telah di bayar
  // ubah status menjadi paid
}
bool cancelTicket(vector<Ticket> &ticket, vector<Flight> &flights,
                  string ticketID) {
  // ubah status ticket menjadi canceled jika belum di bayar
  // jika sudah di bayar maka tidak bisa di lakukan canceled
  // ubah juga ukuran seat pada flight yang di pesan
  // tambah jumlah seat karena sesua jumlah seat yang di batalkan
}
void viewHistoryTicket(vector<Ticket> &ticket, string username, Role role) {
  // melihat history pesanan ticket sesuai username dan role
  // role admin dapat melihat semuanya
  // role airline hanya melihat miliknya
  // role customer hanya melihat ticket yang pernah ia pesan
}
