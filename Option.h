//
// Created by Udbhav on 29/07/2020.
//

#include <iostream>

class Option
        {
            private:
                double T;
                double K;
                double sig;
                double r;
                double S;
                double b;
                double C =0;
                double P=0;
            public:
                Option(); //default
                Option(double t, double k, double sigma, double R, double s, double B); //paramterized
                ~Option(); //destructor
                Option(const Option &obj); //copy consturctor

                //setters and getters
                double getT() const;
                double getK() const;
                double getsig() const;
                double getr() const;
                double getS() const;
                double getP() const;
                double getC() const;
                double getb() const;
                void setP(double input);
                void setC(double input);
                void setb(double input);
                void setT(double input);
                void setK(double input);
                void setSig(double input);
                void setr(double input);
                double setS(double input);


                //functions to return prices
                double callPrice()  const;
                double get_callPrice_Approximation(double h) const;
                double get_putPrice_Approximation(double h) const;
                double putPrice() const;
                double parity_putPrice(double input)  const;
                double parity_callPrice(double input) const;
                bool parity_test(double Call, double Put) const;
                double paritytest_difference(double Call, double Put) const;
                double getAmerican_callPrice() const;
                double getAmerican_putPrice() const;

                //greeks
                double getCallDelta() const;
                double getPutDelta() const;
                double getGamma() const;
                double getPutTheta() const;
                double getCallTheta() const;
                double getVega() const;
                double delta_call_Sensitivity(double h) const;
                double delta_put_Sensitivity(double h) const;
                double gamma_Sensitivity(double h) const;
                friend  std::ostream &operator << (std::ostream & os, const Option &o);
        };


#endif //HW9_OPTION_H
