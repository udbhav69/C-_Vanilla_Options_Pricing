//
// Created by Udbhav on 30/07/2020.
//

#include "Matrix.h"

Matrix::Matrix()
{
    Raw_data =std::vector<Option>();
    Greeks =std::vector<Greek>();
    Pricing_Data= std:: vector<Prices>();
}

Matrix::Matrix(std::vector<Option> abc)
{
   Raw_data = abc;
   Greeks = std::vector<Greek>();
   Pricing_Data = std::vector<Prices>();
   for(int i=0; i < abc.size(); i ++)
   {
       Raw_data.at(i)= abc.at(i);
       addGreeks(i);
       addPrices(i);
   }

}

Matrix::~Matrix(){}

Matrix::Matrix(const Matrix &obj)
{
    Raw_data = obj.Raw_data;
    Greeks = obj.Greeks;
    Pricing_Data= obj.Pricing_Data;

}

void Matrix::RawData_Printer() const
{
    std::cout << " _________________________________________________________________________________________________" << std:: endl;
    std::cout << "\t|\t T \t|\t K \t|\t sig \t|\t r \t|\t S \t|  b\t|" <<std::endl;
    std::cout << " -------------------------------------------------------------------------------------------------" << std:: endl;
    for(int i =0; i <Raw_data.size(); i++)\
    {
        std::cout << "Option"<< i << " "<<Raw_data.at(i);
    }
    std::cout << " -------------------------------------------------------------------------------------------------" << std:: endl;
}

void Matrix::view_Greeks(int input) const
{
    std::cout << " --------------------------------------------------------" << std:: endl;
    std::cout << "Call Delta: " << Greeks.at(input).delta_call << "\t"  << "Put Delta: "<<  Greeks.at(input).delta_put<<std::endl;
    std::cout << "Call Theta: " << Greeks.at(input).theta_call << "\t"  << "Put Theta: "<<  Greeks.at(input).theta_put<<std::endl;
    std::cout << "Gamma: " << Greeks.at(input).gamma <<std::endl;
    std::cout << "Vega: " << Greeks.at(input).vega <<std::endl;
    std::cout << " --------------------------------------------------------" << std:: endl;
}

void Matrix::view_Pricing(int input) const
{
    std::cout << " --------------------------------------------------------" << std:: endl;
    std::cout << " | Option |   European  |   American  | " << std:: endl;
    std::cout << " |  Call  |" <<  Pricing_Data.at(input).European_Call  << " \t| " <<  Pricing_Data.at(input).American_Call <<  " | " << std:: endl;
    std::cout << " |  Put   |" <<  Pricing_Data.at(input).European_Put  << " \t|  " <<  Pricing_Data.at(input).American_Put <<  " | " << std:: endl;
    std::cout << " --------------------------------------------------------" << std:: endl;
}

void Matrix::PrintOptionAt(int input) const
{
    if(input >= Raw_data.size())
        {
            std::cout <<  "Option" << input <<" Does not exits.\nPlease try an integer between 0 & " << Raw_data.size() << std::endl;
        }
    else
        {
            std::cout << "                      OPTION # " << input << std::endl;
            std::cout << " _________________________________________________________________________________________________" << std:: endl;
            std::cout << "\t|\t T \t|\t K \t|\t sig \t|\t r \t|\t S \t|  b\t|" <<std::endl;
            std::cout << " -------------------------------------------------------------------------------------------------" << std:: endl;
            std::cout<< "\t" << Raw_data.at(input);
        }
}

void Matrix::Greeks_Printer() const
{
    std::cout << " __________________________________________________ GREEKS  __________________________________________________ " << std::endl;
    std::cout << " Option #   |\tDelta_C|\t Delta_P|\tTheta_C|\tTheta_P|\t Vega|\t\tGamma|" <<std::endl;
    std::cout << " --------------------------------------------------------------------------------------------------------------" <<std::endl;
    for(int i =0; i < Greeks.size(); i++)
    {
        std::cout << " Option # " << i <<  " |\t "<<Greeks.at(i).delta_call << " |\t " <<  Greeks.at(i).delta_put << " |\t "<< Greeks.at(i).theta_call << " |\t " << Greeks.at(i).theta_put << " | \t" << Greeks.at(i).vega << " | \t" << Greeks.at(i).gamma <<" |\t " <<std::endl;
    }
    std::cout << " ______________________________________________________________________________________________________________ " <<std::endl;
}

void Matrix::Price_Printer() const
{
    std::cout << "  Option   |Euro_C\t| USA_C\t| Euro_P\t| USA_P\t|" << std:: endl;
    for(int i =0; i < Greeks.size(); i++)
    {
        std::cout << " Option # " << i << "|  " << Raw_data.at(i).callPrice() << " \t|" << Raw_data.at(i).getAmerican_callPrice() << "\t| " << Raw_data.at(i).putPrice() << " \t|" << Raw_data.at(i).getAmerican_putPrice() << "\t|"<<  std::endl;
    }
}



void Matrix::addGreeks(int i)
{
    Greeks.push_back(Greek{Raw_data.at(i).getCallDelta() , Raw_data.at(i).getPutDelta() , Raw_data.at(i).getGamma() , Raw_data.at(i).getVega(), Raw_data.at(i).getCallTheta(), Raw_data.at(i).getPutTheta() });
}

void Matrix::addPrices(int i)
{
    Pricing_Data.push_back(Prices{Raw_data.at(i).callPrice(), Raw_data.at(i).putPrice(), Raw_data.at(i).getAmerican_callPrice(), Raw_data.at(i).getAmerican_putPrice()});
}
void Matrix::addOption(const Option& input)
{
    Raw_data.push_back(input);
    addGreeks(Raw_data.size()-1);
    addPrices(Raw_data.size()-1);
    std::cout<<"Option Succesfully Added!"<<std::endl;
}

void Matrix::monotonic_Addition( int optionNumber, int input, double start, double end,  double increment_step)
{
    int counter =0;
    switch(input)
    {
        case 1: //T
            for(start; start<=end; start+=increment_step)
            {
                addOption(Option(start,Raw_data.at(optionNumber).getK(),Raw_data.at(optionNumber).getsig(),Raw_data.at(optionNumber).getr(),Raw_data.at(optionNumber).getS(),Raw_data.at(optionNumber).getb()));
                counter++;
            }
            break;
        case 2: //K
                for(start; start<=end; start+=increment_step)
                {
                    addOption(Option(Raw_data.at(optionNumber).getT(),start,Raw_data.at(optionNumber).getsig(),Raw_data.at(optionNumber).getr(),Raw_data.at(optionNumber).getS(),Raw_data.at(optionNumber).getb()));
                    counter++;
                }
            break;
        case 3: //sig
            for(start; start<=end; start+=increment_step)
            {
                addOption(Option(Raw_data.at(optionNumber).getT(),Raw_data.at(optionNumber).getK(),start,Raw_data.at(optionNumber).getr(),Raw_data.at(optionNumber).getS(),Raw_data.at(optionNumber).getb()));
                counter++;
            }
            break;
        case 4: //S
            for(start; start<=end; start+=increment_step)
            {
                addOption(Option(Raw_data.at(optionNumber).getT(),Raw_data.at(optionNumber).getK(),Raw_data.at(optionNumber).getsig(),Raw_data.at(optionNumber).getr(),start,Raw_data.at(optionNumber).getb()));
                counter++;
            }
            break;
        case 5: //R
            for(start; start<=end; start+=increment_step)
            {
                addOption(Option(Raw_data.at(optionNumber).getT(),Raw_data.at(optionNumber).getK(),Raw_data.at(optionNumber).getsig(),start,Raw_data.at(optionNumber).getS(),Raw_data.at(optionNumber).getb()));
                counter++;
            }
            break;
        case 6: //B
            for(start; start<=end; start+=increment_step)
            {
                addOption(Option(Raw_data.at(optionNumber).getT(),Raw_data.at(optionNumber).getK(),Raw_data.at(optionNumber).getsig(),Raw_data.at(optionNumber).getr(),Raw_data.at(optionNumber).getS(),start));
                counter++;
            }
            break;
        default:
            std::cout << input <<"is not an choice. Please input a number corrosponding to the desired variable!" << std::endl;
    }
    std::cout << counter << " new Options have been added to the Matrix!" << std::endl;
    std::cout  <<Raw_data.size() << " is the Options count!" << std::endl;
}

int Matrix::getSize() {return Raw_data.size();}

void Matrix::EditOption(int optionNumber, int variable, double change)
{
    if(optionNumber >= Raw_data.size())
        {
            std::cout << "Please input integer in range of 0 & " << Raw_data.size() << std::endl;
        }
    else
        {
            switch (variable)
            {
                case 1://t
                    Raw_data.at(optionNumber) = Option(change,Raw_data.at(optionNumber).getK(),Raw_data.at(optionNumber).getsig(),Raw_data.at(optionNumber).getr(),Raw_data.at(optionNumber).getS(),Raw_data.at(optionNumber).getb());
                    Greeks.at(optionNumber) = Greek{Raw_data.at(optionNumber).getCallDelta() , Raw_data.at(optionNumber).getPutDelta() , Raw_data.at(optionNumber).getGamma() , Raw_data.at(optionNumber).getVega(), Raw_data.at(optionNumber).getCallTheta(), Raw_data.at(optionNumber).getPutTheta()};
                    Pricing_Data.at(optionNumber) = Prices{Raw_data.at(optionNumber).callPrice(), Raw_data.at(optionNumber).putPrice(), Raw_data.at(optionNumber).getAmerican_callPrice(), Raw_data.at(optionNumber).getAmerican_putPrice()};
                    std::cout << "Variable T at Option# " << optionNumber << " was succesfully changed to " << change << std::endl;
                    break;
                case 2://k
                    Raw_data.at(optionNumber) = Option(Raw_data.at(optionNumber).getT(),change,Raw_data.at(optionNumber).getsig(),Raw_data.at(optionNumber).getr(),Raw_data.at(optionNumber).getS(),Raw_data.at(optionNumber).getb());
                    Greeks.at(optionNumber) = Greek{Raw_data.at(optionNumber).getCallDelta() , Raw_data.at(optionNumber).getPutDelta() , Raw_data.at(optionNumber).getGamma() , Raw_data.at(optionNumber).getVega(), Raw_data.at(optionNumber).getCallTheta(), Raw_data.at(optionNumber).getPutTheta()};
                    Pricing_Data.at(optionNumber) = Prices{Raw_data.at(optionNumber).callPrice(), Raw_data.at(optionNumber).putPrice(), Raw_data.at(optionNumber).getAmerican_callPrice(), Raw_data.at(optionNumber).getAmerican_putPrice()};
                    std::cout << "Variable K at Option# " << optionNumber << " was succesfully changed to " << change << std::endl;
                    break;
                case 3://sig
                    Raw_data.at(optionNumber) = Option(Raw_data.at(optionNumber).getT(),Raw_data.at(optionNumber).getK(),change,Raw_data.at(optionNumber).getr(),Raw_data.at(optionNumber).getS(),Raw_data.at(optionNumber).getb());
                    Greeks.at(optionNumber) = Greek{Raw_data.at(optionNumber).getCallDelta() , Raw_data.at(optionNumber).getPutDelta() , Raw_data.at(optionNumber).getGamma() , Raw_data.at(optionNumber).getVega(), Raw_data.at(optionNumber).getCallTheta(), Raw_data.at(optionNumber).getPutTheta()};
                    Pricing_Data.at(optionNumber) = Prices{Raw_data.at(optionNumber).callPrice(), Raw_data.at(optionNumber).putPrice(), Raw_data.at(optionNumber).getAmerican_callPrice(), Raw_data.at(optionNumber).getAmerican_putPrice()};
                    std::cout << "Variable Sigma at Option# " << optionNumber << " was succesfully changed to " << change << std::endl;
                    break;
                case 4://s
                    Raw_data.at(optionNumber) = Option(Raw_data.at(optionNumber).getT(),Raw_data.at(optionNumber).getK(),Raw_data.at(optionNumber).getsig(),Raw_data.at(optionNumber).getr(),change,Raw_data.at(optionNumber).getb());
                    Greeks.at(optionNumber) = Greek{Raw_data.at(optionNumber).getCallDelta() , Raw_data.at(optionNumber).getPutDelta() , Raw_data.at(optionNumber).getGamma() , Raw_data.at(optionNumber).getVega(), Raw_data.at(optionNumber).getCallTheta(), Raw_data.at(optionNumber).getPutTheta()};
                    Pricing_Data.at(optionNumber) = Prices{Raw_data.at(optionNumber).callPrice(), Raw_data.at(optionNumber).putPrice(), Raw_data.at(optionNumber).getAmerican_callPrice(), Raw_data.at(optionNumber).getAmerican_putPrice()};
                    std::cout << "Variable S at Option# " << optionNumber << " was succesfully changed to " << change << std::endl;
                    break;
                case 5://r
                    Raw_data.at(optionNumber) = Option(Raw_data.at(optionNumber).getT(),Raw_data.at(optionNumber).getK(),Raw_data.at(optionNumber).getsig(),change,Raw_data.at(optionNumber).getS(),Raw_data.at(optionNumber).getb());
                    Greeks.at(optionNumber) = Greek{Raw_data.at(optionNumber).getCallDelta() , Raw_data.at(optionNumber).getPutDelta() , Raw_data.at(optionNumber).getGamma() , Raw_data.at(optionNumber).getVega(), Raw_data.at(optionNumber).getCallTheta(), Raw_data.at(optionNumber).getPutTheta()};
                    Pricing_Data.at(optionNumber) = Prices{Raw_data.at(optionNumber).callPrice(), Raw_data.at(optionNumber).putPrice(), Raw_data.at(optionNumber).getAmerican_callPrice(), Raw_data.at(optionNumber).getAmerican_putPrice()};
                    std::cout << "Variable r at Option# " << optionNumber << " was succesfully changed to " << change << std::endl;
                    break;
                case 6://b
                    Raw_data.at(optionNumber) = Option(Raw_data.at(optionNumber).getT(),Raw_data.at(optionNumber).getK(),Raw_data.at(optionNumber).getsig(),Raw_data.at(optionNumber).getr(),Raw_data.at(optionNumber).getS(),change);
                    Greeks.at(optionNumber) = Greek{Raw_data.at(optionNumber).getCallDelta() , Raw_data.at(optionNumber).getPutDelta() , Raw_data.at(optionNumber).getGamma() , Raw_data.at(optionNumber).getVega(), Raw_data.at(optionNumber).getCallTheta(), Raw_data.at(optionNumber).getPutTheta()};
                    Pricing_Data.at(optionNumber) = Prices{Raw_data.at(optionNumber).callPrice(), Raw_data.at(optionNumber).putPrice(), Raw_data.at(optionNumber).getAmerican_callPrice(), Raw_data.at(optionNumber).getAmerican_putPrice()};
                    std::cout << "Variable b at Option# " << optionNumber << " was succesfully changed to " << change << std::endl;
                    break;
                    default:
                    std::cout << optionNumber <<"is not an choice. Please input a number corrosponding to the desired variable!" << std::endl;
            }

        }
}

Option Matrix::getOptionAt(int input) const
{
    return Raw_data.at(input);
}

void Matrix::view_Approximation_Greeks(double h) const
{
    std::cout << "______________________________________________________________" <<std::endl;
    std::cout << "\t\tGreeks Approximation @ h = " <<h <<std::endl;
    std::cout << "--------------------------------------------------------------" <<std::endl;
    std::cout << "  Option #   |\tDelta_C|\t Delta_P|\t Gamma|" <<std::endl;
    std::cout << "--------------------------------------------------------------" <<std::endl;
    for(int i =0; i < Raw_data.size();i++)
    {
        std::cout << " Option  " << i << " |\t" << Raw_data.at(i).delta_call_Sensitivity(h) << "\t|\t" <<Raw_data.at(i).delta_put_Sensitivity(h) << "\t|\t" << Raw_data.at(i).gamma_Sensitivity(h) << " |" <<std::endl;
    }
}

void Matrix::Erase_ElementAt(int input)
{
    int j =0;
    auto g =  Greeks.begin();
    auto p = Pricing_Data.begin();
    if(input< 0 || input >= Raw_data.size())
        {
            std::cout << "Invalid Input!" <<input << "th  element does not Exist!" <<std::endl;
        }
    else
        {
            std::cout<< "Option # " << input << " is being removed." <<std::endl;
            PrintOptionAt(input);
          for(auto i = Raw_data.begin(); i !=Raw_data.end();i++,j++, g++, p++)
          {
             if(j == input)
             {
                 Raw_data.erase(i);
                 Greeks.erase(g);
                 Pricing_Data.erase(p);
             }
          }
          std::cout << "\nNew Data Set Size is: " << Raw_data.size() << std::endl;
          RawData_Printer();
        }
}