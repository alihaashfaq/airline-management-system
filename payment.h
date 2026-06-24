#ifndef PAYMENT_H
#define PAYMENT_H
#include <QString>

class Payment {
public:
    virtual QString pay() = 0;
    virtual ~Payment() {}
};

class Cash : public Payment {
public:
    QString pay() { return "Payment via Cash"; }
};

class Card : public Payment {
public:
    QString pay() { return "Payment via Card"; }
};

#endif