#include <iostream>
#include <boost/random.hpp>
#include <ctime>
#include <map>
#include "bits/stdc++.h"
#include "Option.h"
#include "Matrix.h"
#include <vector>
#include <list>
#include <iterator>


int main()
{

    std::cout << std::fixed;
    std::cout << std::setprecision(3);
    int userInput=1;
    std::vector<std::string> files_Names; //creating a vector to store the files & data sets
    std::vector<Matrix> Data_Table; ///creating a vector matix to store the rvarious data sets
    int submenu_Input;
    int sub_submenu;
    int dummy;
    int variable_select;
    double dummy_t;
    double dummy_k;
    double dummy_s;
    double dummy_sig;
    double dummy_r;
    double dummy_b;
    double delta;
    double start,end,increment;
    std::string name;


    std::vector<Option> HW_9_Data; ///creating a HW9 dataset to test the code as required.
    HW_9_Data.push_back(Option(0.25,65,0.30,0.08,60,0.08));
    HW_9_Data.push_back(Option(1,100,0.2,0,100,0));
    HW_9_Data.push_back(Option(1,10,0.5,0.12,5,0.12));
    HW_9_Data.push_back(Option(30,100,0.30,0.08,100,0.08));
    HW_9_Data.push_back(Option(0.5,100,0.36,0.1,105,0));
    HW_9_Data.push_back(Option(7,100,0.1,0.1,110,0.02));
    Data_Table.push_back(Matrix(HW_9_Data)); ///adding the HW9 data set to the matrix.
    files_Names.push_back("HW-9");


    //////// OPTIONS CALCULATOR MAIN MENU ///////////
    while (userInput!=0)
    {
        std::cout << "  \n***>>> Welcome to Options Calculator ! <<<***\n" << std::endl;
        std:: cout <<"Please input the integer corresponding to one of the following options:\n\n***  Main Menu  ***\n1. Load HW 9 Output\n2. View Data Set Directory\n3.Add New Data Set\n0.Exit" << std::endl;
        std:: cin >> userInput;

        switch (userInput)
        {
            case 1:
                Data_Table.at(0).RawData_Printer();
                Data_Table.at(0).Price_Printer();
                Data_Table.at(0).Greeks_Printer();
                Data_Table.at(0).view_Approximation_Greeks(0.01);

                break;

            case 2:
                std::cout <<"Please select data set to be loaded.\n0. Exit" << std::endl;

                for(int i=0; i< files_Names.size(); i++)
                {
                    std::cout << i+1 << ". " << files_Names.at(i) << "(Contains " << Data_Table.at(i).getSize()<<" Options)" << std::endl;
                }

                std::cin>> submenu_Input;
                while(submenu_Input!=0)
                {

                    if(submenu_Input==0){break;}
                    else if(submenu_Input > files_Names.size() || submenu_Input <0)
                        {
                            std::cout << submenu_Input << " is not a valid input. Please input an integer between 0 & " << files_Names.size() << std::endl;;
                        }
                    else
                        {
                            std::cout << "You have picked " << files_Names.at(submenu_Input-1) << " Data Set!" << std::endl;
                            Data_Table.at(submenu_Input-1).RawData_Printer();
                            std::cout << "\n"<< files_Names.at(submenu_Input-1) << " DATA SET\n1. View Option\n2. Add Option\n3.Edit Option\n4.View Greeks\n5. View Prices\n6. Call-Put Parity (Get Put Price)\n7. Put Parity (Get Call Price)\n8. Monotonic Option Addition\n9. Remove Option\n0. Exit" << std::endl;
                            std::cin >> sub_submenu;
                            if(sub_submenu == 0 ){submenu_Input=0;}
                             while (sub_submenu!=0)
                             {

                                 switch (sub_submenu)
                                 {
                                     case 1:
                                         std::cout << "Please input Option number to be viewed" << std::endl;
                                         std::cin>>dummy;
                                         if(dummy>= Data_Table.at(submenu_Input-1).getSize() || dummy<0)
                                             {
                                                 std::cout << "Please input a valid integer between 0 & " << Data_Table.at(submenu_Input-1).getSize() << std::endl;
                                                 sub_submenu = 0;
                                             }
                                         else
                                             {
                                                Data_Table.at(submenu_Input-1).PrintOptionAt(dummy);
                                                Data_Table.at(submenu_Input-1).view_Greeks(dummy);
                                                Data_Table.at(submenu_Input-1).view_Pricing(dummy);
                                                 sub_submenu = 0;
                                             }
                                         break;

                                     case 2:
                                         std:: cout << "Please input the necessary Variables" << std::endl;
                                         std::cout << "1. T (expiry time/maturity) = " ;
                                         std:: cin >> dummy_t;
                                         std::cout << "2. Sigma (volatility) = " ;
                                         std:: cin >> dummy_sig;
                                         std::cout << "3. r (risk-free interest rate) = " ;
                                         std:: cin >> dummy_r;
                                         std::cout << "4. S (current stock price where we wish to price the option) = " ;
                                         std:: cin >> dummy_s;
                                         std::cout << "5. K (strike Price) = " ;
                                         std:: cin >> dummy_k;
                                         std::cout << "6.\ni. b = r for Black Sholes Stock Option model\nii. b = r-q for Morton  model with 'q' dividend yeild\niii. b = 0 for Black Sholes Futures  model\niv. b = r -R for Garman and Kohlhagen currency option model, where R is the foreign risk-free interest rate\nb (Cost of Carry) = ";
                                         std:: cin >> dummy_b;
                                         Data_Table.at(submenu_Input-1).addOption(Option(dummy_t,dummy_k,dummy_sig, dummy_r, dummy_s, dummy_b));
                                         sub_submenu=0;
                                         break;

                                     case 3:
                                         std::cout << "Please input the following!\n1. Option Number: ";
                                         std::cin>>dummy;
                                         if(dummy>= Data_Table.at(submenu_Input-1).getSize() || dummy<0)
                                             {
                                                 std::cout << "Please input a valid integer between 0 & " << Data_Table.at(submenu_Input-1).getSize() << std::endl;
                                                 sub_submenu = 0;
                                             }
                                         else
                                             {
                                                 Data_Table.at(submenu_Input-1).PrintOptionAt(dummy);
                                                 std:: cout << " Variable to be Edited: \n1. T\n2. K\n3. Sigma\n4. S\n5.r\n6. b"<<std::endl;
                                                 std::cin >> variable_select;
                                                 std:: cout << " Enter new Value: ";
                                                 std::cin >> delta;
                                                 Data_Table.at(submenu_Input-1).EditOption(dummy,variable_select,delta);
                                                 sub_submenu = 0;
                                             }
                                         break;

                                     case 4:
                                         if(Data_Table.at(submenu_Input-1).getSize()==0){sub_submenu = 0; std::cout << "No Options! Please add Options first." << std::endl;}
                                         else{Data_Table.at(submenu_Input-1).Greeks_Printer(); sub_submenu = 0;}
                                         break;

                                     case 5:
                                         if(Data_Table.at(submenu_Input-1).getSize()==0){sub_submenu = 0; std::cout << "No Options! Please add Options first." << std::endl;}
                                         else{Data_Table.at(submenu_Input-1).Price_Printer(); sub_submenu = 0;}
                                         break;

                                     case 6:
                                         std::cout << "Please input the following!\n1. Option Number: ";
                                         std::cin>>dummy;
                                         if(dummy>= Data_Table.at(submenu_Input-1).getSize() || dummy<0)
                                             {
                                                 std::cout << "Please input a valid integer between 0 & " << Data_Table.at(submenu_Input-1).getSize() << std::endl;
                                                 sub_submenu = 0;
                                             }
                                         else
                                             {
                                                Data_Table.at(submenu_Input-1).PrintOptionAt(dummy);
                                                std::cout << "Enter Call Price: " ;
                                                std::cin >> start;
                                                std::cout << " The corresponding Put price is: " << Data_Table.at(submenu_Input-1).getOptionAt(dummy).parity_putPrice(start) << std::endl;
                                                 sub_submenu = 0;
                                             }
                                         break;
                                     case 7:
                                         std::cout << "Please input the following!\n1. Option Number: ";
                                         std::cin>>dummy;
                                         if(dummy>= Data_Table.at(submenu_Input-1).getSize() || dummy<0)
                                         {
                                             std::cout << "Please input a valid integer between 0 & " << Data_Table.at(submenu_Input-1).getSize() << std::endl;
                                             sub_submenu = 0;
                                         }
                                         else
                                         {
                                             Data_Table.at(submenu_Input-1).PrintOptionAt(dummy);
                                             std::cout << "Enter Put Price: " ;
                                             std::cin >> start;
                                             std::cout << " The corresponding Put price is: " << Data_Table.at(submenu_Input-1).getOptionAt(dummy).parity_callPrice(start) << std::endl;
                                             sub_submenu = 0;
                                         }
                                         break;
                                     case 8:
                                         std::cout << "Please input the following data:\n1. Option Num: ";
                                         std::cin >> dummy;
                                         if(dummy>= Data_Table.at(submenu_Input-1).getSize() || dummy<0)
                                         {
                                             std::cout << "Please input a valid integer between 0 & " << Data_Table.at(submenu_Input-1).getSize() << std::endl;
                                             sub_submenu = 0;
                                         }
                                         else
                                         {
                                             Data_Table.at(submenu_Input-1).PrintOptionAt(dummy);
                                             std::cout << "Variable To Experiment on:\n1. T\n2. K\n3. Sigma\n4. S\n5.r\n6. b" << std::endl;
                                             std::cin >> variable_select;
                                             std::cout << "Starting Point: ";
                                             std::cin>> start;
                                             std::cout << "Ending Point: ";
                                             std::cin>> end;
                                             std::cout << "Increment: ";
                                             std::cin>> increment;
                                             Data_Table.at(submenu_Input-1).monotonic_Addition(dummy,variable_select,start,end,increment);
                                             sub_submenu = 0;
                                         }
                                         break;
                                     case 9:
                                         int input;
                                         std::cout << "Please Input Option number to be removed: ";
                                         std::cin >>input;
                                         if(input>= Data_Table.at(submenu_Input-1).getSize() || input<0)
                                         {
                                             std::cout << "Please input a valid integer between 0 & " << Data_Table.at(submenu_Input-1).getSize() << std::endl;
                                             sub_submenu = 0;
                                         }
                                         else{Data_Table.at(submenu_Input-1).Erase_ElementAt(input);sub_submenu = 0;}
                                         break;
                                     case 0:
                                         submenu_Input=0;
                                         break;
                                     default: { std::cout << sub_submenu << " is not a valid input. Please input an integer between 0 & 9" << std::endl; sub_submenu = 0; }
                                 }
                             }
                        }
                }

                break;

            case 3:
                    std::cout << "Please Data Set name" <<std::endl;
                    std::cin >> name;
                    files_Names.push_back(name);
                    Data_Table.push_back(Matrix());
                    std::cout << "File " + name + " has been added to the directory. You now have " << files_Names.size() << " data sets!" << std::endl;
                    std::cout << "Data Sets Available:" << std:: endl;
                    for(int i =0; i < files_Names.size(); i++)
                    {
                        std :: cout << i << ". " <<files_Names.at(i) << " (Contains "  << Data_Table.at(i).getSize()<< " Options)."<< std::endl;
                    }
                break;

            case 0:

                break;
            default: std::cout<< userInput <<  " is not a valid input. Please re-enter an integer between 1-4."<< std::endl;
        }
    }



    return 0;

}
