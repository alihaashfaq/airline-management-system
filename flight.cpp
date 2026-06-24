#include "flight.h"

int Flight::totalFlights = 0;

Flight::Flight(QString fn, QString d, int s,
               QString dep, QString arr, QString air)
    : flightNo(fn), destination(d), seats(s),
    departureTime(dep), arrivalTime(arr), airline(air)
{
    totalFlights++;
}

QString Flight::toDisplay() {
    return QString("Flight: %1 | Airline: %2 | Destination: %3 | "
                   "Departure: %4 | Arrival: %5 | Seats: %6")
        .arg(flightNo).arg(airline).arg(destination)
        .arg(departureTime).arg(arrivalTime).arg(seats);
}

QString Flight::toConfidential() {
    return QString("Flight: %1 | Seats: %2")
    .arg(flightNo).arg(seats);
}
