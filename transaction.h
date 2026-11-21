#pragma once
#include <string>
#include "date.h"


enum class TransactionType
{
    income=1,
    expenses,
    unknown
};

enum class Category
{
    work=1,
    business,
    food,
    car,
    home,
    holiday,
    gym,
    other
};

class Transaction
{
    int id;
    double amount;
    TransactionType type;
    Category category;
    std::string description;
    Date date;
public:
    Transaction(int id,double a, TransactionType t, Category c, std::string description, Date date);
    void showTransaction() const;
    int getId() const;
    double getAmount() const;
    TransactionType getType() const;
    Category getCategory() const;
    Date getDate() const;
    int dateGetDay();
    int dateGetMonth();
    int dateGetYear();
    std::string saveDate(Date date);
    bool dateSetDate(int day, int month, int year);
    int getDay();
    int getMonth();
    int getYear();
    std::string getDescription() const;
    void changeAmount(double newAmount);
    void changeType(TransactionType newType);
    void changeCategory(Category newCategory);
    void changeDescription(std::string newDescription);
};
