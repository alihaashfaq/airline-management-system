#include "ticket.h"

Ticket::Ticket(Passenger p, QString fn, int s,
               QString pay, QString sc, int pr)
    : passenger(p), flightNo(fn), seat(s),
    payment(pay), seatClass(sc), price(pr) {}

QString Ticket::toDisplay() {
    return QString(
               "===== BOOKING CONFIRMATION =====\n"
               "Passenger : %1\n"
               "Flight    : %2\n"
               "Seat      : %3\n"
               "Class     : %4\n"
               "Price     : Rs. %5\n"
               "Payment   : %6\n"
               "Status    : Confirmed"
               ).arg(passenger.getName()).arg(flightNo)
        .arg(seat).arg(seatClass).arg(price).arg(payment);
}