#include <iostream>
#include <string>
#include "input.h"
#include <conio.h>



int getInt(const std::string& message, const int& minRange, const int& maxRange)
{
    int value;
    if(!message.empty() && message.back()!=' ')
    {
        message+' ';
    }
    std::cout<<message;
    while(true)
    {
        std::cin>>value;
        if(!std::cin.fail())
        {
            if(value>=minRange && value <= maxRange)
            {
                return value;
            }
        }
        std::cerr<<"Invalid input. Try again."<<std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
}

std::string getNumber(const std::string& message, const int& minRange, const int& maxRange)
{
    int number;
    std::cout<<message;
    while(true)
    {
        std::cin>>number;
        if(!std::cin.fail())
        {
            if(number>=minRange && number<=maxRange)
            {
                return std::to_string(number);
            }
        }
        std::cerr<<"Invalid input. Try again."<<std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
}

std::string returnDate(const std::string message)
{
    std::cout<<message<<std::endl;
    return getNumber("Day: ",1,31)+":"+getNumber("Month: ",1,12)+":"+getNumber("Year: ", 1,2026);
}

TransactionType getTransactionType(const std::string& message)
{
    std::string transactionTypeStr;
    std::cout<<message;
    while(true)
    {
        std::cin>>transactionTypeStr;
        if(!std::cin.fail())
        {
            return stringToType(transactionTypeStr);
        }
        std::cerr<<"Invalid input. Try again."<<std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
}

double getDouble(const std::string& message, const double& minRange, const double& maxRange)
{
    double amount;
    std::cout<<message;
    while(true)
    {
        std::cin>>amount;
        if(!std::cin.fail())
        {
            if(amount>=minRange && amount<=maxRange)
            {
                return amount;
            }
        }
        std::cerr<<"Invalid input. Try again."<<std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
}

Category getCategoryType(const std::string& message)
{
    std::string categoryTypeStr;
    std::cout<<message;
    while(true)
    {
        std::cin>>categoryTypeStr;
        if(!std::cin.fail())
        {
            return stringToCategory(categoryTypeStr);
        }
        std::cerr<<"Invalid input.Try Again."<<std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
}
std::string getDescription(const std::string& message, const size_t& minRange, const size_t& maxRange)
{
    std::string description;
    std::cout<<message;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    while(true)
    {
        getline(std::cin,description);
        if(!std::cin.fail())
        {
            if(description.length()>=minRange && description.length()<=maxRange)
            {
                return description;
            }
            else
            {
                std::cerr<<"Description too long. Try again."<<std::endl;
            }
        }
        if(std::cin.fail())
        {
        std::cerr<<"Invalid input. Try again."<<std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
    }
}

void pause()
{
    std::cout<<"Press button to continue."<<std::endl;
    getch();
    system("cls");
}
