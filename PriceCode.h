//
// Created by gaetan on 12.06.19.
//

#ifndef rentalRENTAL_PRICECODE_H
#define rentalRENTAL_PRICECODE_H

//#include <utility>
#define BONUS_COND 1
#define POINT_BONUS 1
#define POINT_MIN 1

class PriceCode {
public:
    explicit PriceCode();
    virtual double getAmount(const unsigned int days) = 0;
    virtual int bonus(const unsigned int days) = 0;
};

PriceCode::PriceCode() = default;

class Regular : public PriceCode {
public:
    explicit Regular();
    virtual int bonus(const unsigned int days) override;
    virtual double getAmount(const unsigned int days) override;
private:
    const double MIN_AMOUNT = 2;
    const unsigned int DAYS_COND = 2;
    const double DEC = 2;
    const double RATIO = 1.5;
};

int Regular::bonus(const unsigned int days) {return POINT_MIN;}

double Regular::getAmount(const unsigned int days) {
    double thisAmount = 0;
    if(days)
        thisAmount = MIN_AMOUNT;
    if ( days > DAYS_COND )
        thisAmount += ( days - DEC ) * RATIO ;
    return thisAmount;
}

Regular::Regular() : PriceCode() {}

class Childrens : public PriceCode{
public:
    explicit Childrens();
    virtual int bonus(const unsigned int days) override;
    virtual double getAmount(const unsigned int days) override;
private:
    const double RATIO = 3;
};

double Childrens::getAmount(const unsigned int days) {
    return days * RATIO;
}

int Childrens::bonus(const unsigned int days) {return POINT_MIN;}

Childrens::Childrens() : PriceCode() {}

class NewRelease : public PriceCode{
public:
    explicit NewRelease();
    virtual int bonus(const unsigned int days) override;
    virtual double getAmount(const unsigned int days);
private:
    const double MIN_AMOUNT = 1.5;
    const unsigned int DAYS_COND = 3;
    const double DEC = 3;
    const double RATIO = 1.5;
};

double NewRelease::getAmount(const unsigned int days) {
    double thisAmount = 0;
    if(days)
        thisAmount = MIN_AMOUNT;
    if ( days > DAYS_COND )
        thisAmount += (days - DEC ) * RATIO;
    return thisAmount;
}

int NewRelease::bonus(const unsigned int days) {
    return (days > BONUS_COND) ? (POINT_BONUS + POINT_MIN) : POINT_MIN;
}

NewRelease::NewRelease() : PriceCode(){}


#endif //rentalRENTAL_PRICECODE_H
