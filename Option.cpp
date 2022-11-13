//
// Created by Udbhav on 29/07/2020.
//

#include "Option.h"
#include <boost/math/distributions/normal.hpp>
#include <boost/math/distributions.hpp>
#include <math.h>
using namespace boost::math;

Option::Option(): T(0), K(0), S(0), sig(0), r(0), b(0), C(0), P(0) {}

Option::Option(double t, double k, double sigma, double R, double s, double B): T(t), K(k), S(s), sig(sigma), r(R), b(B)
{
    C=0.0;
    P=0.0;
}

Option::~Option() {}

Option::Option(const Option &obj)
{
    T = obj.T;
    K = obj.K;
    S= obj.S;
    r = obj.r;
    sig = obj.sig;
    b = obj.b;
}

double Option::getK()  const{return K;}

double Option::getS()  const{return S;}

double Option::getT() const {return T;}

double Option::getb()  const{return b;}

double Option::getsig() const {return sig;}

double Option::getr() const {return r;}

double Option::getC() const {return C;}

double Option::getP() const {return P;}

void Option::setC(double input) {C = input;}

void Option::setP(double input) {P= input;}

void Option::setb(double input) {b=input;}

void Option::setK(double input) {K= input;}

void Option::setT(double input) {T = input;}

void Option::setSig(double input) {sig = input;}

void Option::setr(double input) {r=input;}

double Option::setS(double input) {S= input;}

double Option::callPrice() const
{
    double Call;
    double d1 = ((log(S/K)) + ((b + (pow(sig,2)/2)) * T)) / (sig*sqrt(T));
    double d2 = d1 - (sig*sqrt(T));
    boost::math::normal norm;
    Call =  (S * exp((b-r) * T) * cdf(norm, d1)) - (K * exp((-r) * T) * cdf(norm,d2));
    return Call;
}

double Option::putPrice() const
{
    double Put;
    double d1 = ((log(S/K)) + ((b + (pow(sig,2)/2)) * T)) / (sig*sqrt(T));
    double d2 = d1 - (sig*sqrt(T));
    boost::math::normal norm;
    Put = (K* exp((-r) * T) * cdf( norm, (-d2) ) ) - (S * exp((b-r)*T) * cdf(norm, -d1));
    return Put;
}

double Option::parity_callPrice(double input) const
{
    double Call;
    Call = input + S - (K * exp((-r)*T));
    return Call;
}

double Option::parity_putPrice(double input) const
{
    double Put;
    Put = input + (K * exp((-r)*T)) - S;
    return Put;
}

bool Option::parity_test(double Call, double Put) const
{
    return ((Call + (K * exp((-r)*T)) ) - (Put + S)) < 0.001;
}

double Option::paritytest_difference(double Call, double Put) const
{
    return (Call + (K * exp((-r)*T)) ) - (Put + S);
}

double Option::getAmerican_callPrice() const
{
    double Call;
    double y1 = 0.5 - (b/pow(sig,2)) + (sqrt( pow(((b/pow(sig,2)) - 0.5),2) + ((2*r)/(pow(sig,2)))));
    Call = ( (K)/(y1-1) ) * (pow ( ( ( ((y1-1)*S) / ((y1)*K) ) ),(y1)));
    return Call;
}

double Option::getAmerican_putPrice() const
{
    double Put;
    double y2 = 0.5 - (b/pow(sig,2)) - (sqrt( pow(((b/pow(sig,2)) - 0.5),2) + ((2*r)/(pow(sig,2)))));
    Put = ( (K)/(1-y2) ) * (pow( ( ((y2-1)/(y2))*(S/K) ),(y2)));
    return Put;
}


double Option::getCallDelta() const
{
    double delta;
    double d1 = ((log(S/K)) + ((b + (pow(sig,2)/2)) * T)) / (sig*sqrt(T));
    boost::math::normal norm;
    delta = exp((b-r)*T) * cdf(norm,d1);
    return delta;
}

double Option::getPutDelta() const
{
    double delta;
    double d1 = ((log(S/K)) + ((b + (pow(sig,2)/2)) * T)) / (sig*sqrt(T));
    boost::math::normal norm;
    delta = exp((b-r)*T) * (cdf(norm,d1)-1);
    return delta;
}



double Option::getVega() const
{
    double vega;
    double d1 = ((log(S/K)) + ((b + (pow(sig,2)/2)) * T)) / (sig*sqrt(T));
    boost::math::normal norm;
    vega = S * sqrt(T) * exp((b-r)*T) * pdf(norm,d1) * 0.01;
    return vega;
}

double Option::getCallTheta() const
{
    double theta;
    double d1 = ((log(S/K)) + ((b + (pow(sig,2)/2)) * T)) / (sig*sqrt(T));
    double d2 = d1 - (sig*sqrt(T));
    boost::math::normal norm;
    theta = (1/T) * (-((S*sig* exp((b-r)*T) * pdf(norm,d1))/(2*sqrt(T))) + ((b-r) * S * exp((b-r)*T) * cdf(norm,d1)) - (r * K * exp((-r)*T) * cdf(norm,d2)));
    return theta;

}

double Option::getPutTheta() const
{
    double theta;
    double d1 = ((log(S/K)) + ((b + (pow(sig,2)/2)) * T)) / (sig*sqrt(T));
    double d2 = d1 - (sig*sqrt(T));
    boost::math::normal norm;
    theta = (1/T) * (-((S*sig* exp((b-r)*T) * pdf(norm,d1))/(2*sqrt(T))) - ((b-r) * S * exp((b-r)*T) * cdf(norm,(-d1))) + (r * K * exp((-r)*T) * cdf(norm,(-d2))));
    return theta;
}

double Option::getGamma() const
{
    double gamma;
    double d1 = ((log(S/K)) + ((b + (pow(sig,2)/2)) * T)) / (sig*sqrt(T));
    boost::math::normal norm;
    gamma = (exp((b-r)*T) * pdf(norm,d1))/ (S * sig * (sqrt(T))) ;
    return gamma;
}

std::ostream &operator << (std::ostream & os, const Option &o)
{
    os << "| " << o.getT() << " \t| " << o.getK() << " \t| " << o.sig << " \t| " << o.getr() << " \t| " << o.getS() << " \t| " <<  o.getb() << " |"<< std::endl;
}


double Option::get_callPrice_Approximation(double h) const
{
    double Call;
    double d1 = ((log((S+h)/K)) + ((b + (pow(sig,2)/2)) * T)) / (sig*sqrt(T));
    double d2 = d1 - (sig*sqrt(T));
    boost::math::normal norm;
    Call =  ((S+h) * exp((b-r) * T) * cdf(norm, d1)) - (K * exp((-r) * T) * cdf(norm,d2));
    return Call;
}

double Option::get_putPrice_Approximation(double h) const
{
    double Put;
    double d1 = ((log((S+h)/K)) + ((b + (pow(sig,2)/2)) * T)) / (sig*sqrt(T));
    double d2 = d1 - (sig*sqrt(T));
    boost::math::normal norm;
    Put = (K* exp((-r) * T) * cdf( norm, (-d2) ) ) - ((S+h) * exp((b-r)*T) * cdf(norm, -d1));
    return Put;
}


double Option::delta_call_Sensitivity(double h) const
{
    double delta;
    delta = (get_callPrice_Approximation(h)-get_callPrice_Approximation(-h))/(2*h);
    return delta;
}

double Option::delta_put_Sensitivity(double h) const
{
 double delta;
 delta = (get_putPrice_Approximation(h)-get_putPrice_Approximation(-h))/(2*h);
 return delta;
}


double Option::gamma_Sensitivity(double h) const
{
    double gamma;
    gamma = (get_callPrice_Approximation(h) - (2* get_callPrice_Approximation(0)) + get_callPrice_Approximation(-h))/(pow(h,2));
    return gamma;
}




