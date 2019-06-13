//
// Created by gaetan on 12.06.19.
//

#ifndef rentalRENTAL_PRICECODE_H
#define rentalRENTAL_PRICECODE_H

#include <utility>

class PriceCode {
public:
    explicit PriceCode();
    virtual double getAmount(const int days) = 0;
    virtual bool bonus() = 0;
};

PriceCode::PriceCode() = default;

class Regular : public PriceCode {
public:
    explicit Regular();
    virtual bool bonus() override;
    virtual double getAmount(const int days) override;
};

bool Regular::bonus() {return false;}

double Regular::getAmount(const int days) {
    double thisAmount = 2;
    if ( days > 2 )
        thisAmount += ( days - 2 ) * 1.5 ;
    return thisAmount;
}

Regular::Regular() : PriceCode() {}

class Childrens : public PriceCode{
public:
    explicit Childrens();
    virtual bool bonus() override;
    virtual double getAmount(const int days) override;
};

double Childrens::getAmount(const int days) {
    return days * 3;
}

bool Childrens::bonus() {return false;}

Childrens::Childrens() : PriceCode() {}

class NewRelease : public PriceCode{
public:
    explicit NewRelease();
    virtual bool bonus();
    virtual double getAmount(const int days);
};

double NewRelease::getAmount(const int days) {
    double thisAmount = 1.5;
    if ( days > 3 )
        thisAmount += (days - 3 ) * 1.5;
    return thisAmount;
}

bool NewRelease::bonus() {return true;}

NewRelease::NewRelease() : PriceCode(){}


#endif //rentalRENTAL_PRICECODE_H
