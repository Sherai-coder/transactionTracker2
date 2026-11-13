#pragma once
#include <string>


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
    std::string dateStr;
    std::string description;
public:
    Transaction(int id,double a, TransactionType t, Category c,std::string dateStr, std::string description);
    void showTransaction() const;
    int getId() const;
    double getAmount() const;
    TransactionType getType() const;
    Category getCategory() const;

    int getDay();
    int getMonth();
    int getYear();
    std::string getDateStr() const;
    std::string getDescription() const;
    void changeAmount(double newAmount);
    void changeType(TransactionType newType);
    void changeCategory(Category newCategory);
    void changeDate(const std::string& newDate);
    void changeDescription(std::string newDescription);
    bool validationOfDate(std::string dateStr);
    int dateConverter(std::string& dateStr);
    std::size_t countWhiteSpaces(std::string dateStr);
    std::string trimSpaces(std::string& dateStr);
    bool isNumeric(std::string& dateStr);
};
