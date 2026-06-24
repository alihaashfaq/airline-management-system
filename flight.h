#ifndef FLIGHT_H
#define FLIGHT_H
#include <QString>

class Flight {
private:
    QString flightNo, destination, departureTime, arrivalTime, airline;
    int seats;

public:
    static int totalFlights;

    Flight(QString fn="", QString d="", int s=0,
           QString dep="", QString arr="", QString air="");

    QString getFlightNo()    { return flightNo; }
    QString getDestination() { return destination; }
    QString getDeparture()   { return departureTime; }
    QString getArrival()     { return arrivalTime; }
    QString getAirline()     { return airline; }
    int     getSeats()       { return seats; }

    QString toDisplay();
    QString toConfidential();
};

#endif