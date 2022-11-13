//
// Created by Udbhav on 30/07/2020.
//

#ifndef HW9_MATRIX_H
#define HW9_MATRIX_H
#include <vector>
#include "Option.h"

class Matrix
{
    struct Greek
            {
                double delta_call;
                double delta_put;
                double gamma;
                double vega;
                double theta_call;
                double theta_put;
            };
    struct Prices
            {
                double European_Call;
                double European_Put;
                double American_Call;
                double American_Put;
            };

    private:
        std::vector<Option> Raw_data;
        std::vector<Greek>  Greeks;
        std::vector<Prices> Pricing_Data;
    public:
        Matrix(); //defauult
        ~Matrix(); //destructor
        Matrix(std::vector<Option> abc);
        Matrix(const Matrix &obj);// copy constructor

        //printers for the function
        void RawData_Printer() const;
        void Price_Printer() const;
        void Greeks_Printer() const;
        void PrintOptionAt(int input) const;
        void view_Greeks(int input)const;
        void view_Pricing(int input) const;
        void view_Approximation_Greeks(double h ) const;


        //data setters and getters & functionality
        void addOption(const Option& input);
        void addGreeks(int i);
        void addPrices(int i);
        void monotonic_Addition(int optionNumber, int input, double start, double end, double increment_step);
        void EditOption(int optionNumber, int variable, double change);
        int getSize();
        Option getOptionAt(int input) const;
        void Erase_ElementAt(int input);
};


#endif //HW9_MATRIX_H
