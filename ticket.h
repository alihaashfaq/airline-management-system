#ifndef TICKET_H
#define TICKET_H
#include "passenger.h"
#include <QString>

class Ticket {
private:
    Passenger passenger;
    QString flightNo, payment, seatClass;
    int seat, price;

public:
    Ticket(Passenger p, QString fn, int s,
           QString pay, QString sc, int pr);

    QString toDisplay();
};

#endif