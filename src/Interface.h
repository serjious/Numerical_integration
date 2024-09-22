#pragma once
#include "NumericalIntegration.h"
#define I_PI 3.1415926535
#define I_E  2.7182818284
// interface

enum Method {
    L_RIENMANN, R_RIENMANN, M_RIENMANN, TRAPEZ, SIMPSON
};

class Interface
{
public:
    Interface();
    Interface(const char* expression_, double a_, double b_, double precision_, const char* meth_);

    void initGUI();
    void init(const char* expression_, double a_, double b_, double precision_, const char* meth_);
    double calcIntegral();
    double calcIntegral(int& i);
    double getPrecision();

private:
    NumericalIntegration integral;
    double precision;
    Method method;

    void setMethod(const char *meth_);
    void setPrecision(double prec_);

    void GUI();
    void setMethod_GUI();
    void setInterval_GUI();
    void setExpression_GUI();
    void setPrecision_GUI();

    void calcIntegral_GUI();

    void printBanner() const;
    void printInformation() const;
    void printIntegral(int y, int x) const;
    void scanString(int y, int x, char* str);
    void scanDoubleString(int y, int x, char* str);

    double calcSelectMethod();

};
