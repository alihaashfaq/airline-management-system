#ifndef PASSENGER_H
#define PASSENGER_H
#include <QString>

class Person {
protected:
    QString name;
public:
    Person(QString n = "") : name(n) {}
    QString getName() { return name; }
};

class Passenger : public Person {
public:
    Passenger(QString n = "") : Person(n) {}
};

#endif
