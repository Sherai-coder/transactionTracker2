#pragma once
#include <iostream>
#include "transaction.h"
#include <vector>
#include <optional>
#include <algorithm>
#include <numeric>

struct invalidTransactionRecord
{
    std::string data;
    std::string reason;
    void setData(const std::string& information)
    {
        data=information;
    }
    void setReason(const std::string& information)
    {
        reason=information;
    }
};
class TransactionManager
{
    std::vector<Transaction> transactions;
    std::vector<invalidTransactionRecord> invalidRecords;
    int nextId=highestUsedId+1;
    int highestUsedIdFromFile=0;
    int highestUsedId=0;
public:
    std::optional<Transaction> createTransaction(int id, double amount, TransactionType type, Category category,const std::string& description, Date date);
    bool addTransaction(double amount,TransactionType type, Category category,const std::string& description, Date date);
    int setHighestUsedId();

    void showAllTransactions() const;
    void seeSpecificTransaction(std::vector<Transaction>::iterator it) const;

    ///////////// Find Transaction By ///////////////////////
    template <typename FindHow>
    std::vector<Transaction>::iterator findTransactionBy(FindHow findhow);
    std::vector<Transaction>::iterator findTransactionById(int id);
    std::vector<Transaction>::iterator findTransactionByAmount(double amount);
    std::vector<Transaction>::iterator findTransactionByType(TransactionType type);
    std::vector<Transaction>::iterator findTransactionByCategory(Category category);
    //std::vector<Transaction>::iterator findTransactionByDate(const std::string& date);

    ///////////// Filter Transaction /////////////////
    template <typename SearchTransactionsBy>
    std::vector<Transaction> showTransactionsBy(SearchTransactionsBy searchtransactionsby) const;
    std::vector<Transaction> showTransactionsByAmount(double amount) const;
    std::vector<Transaction> showTransactionsByType(TransactionType type) const;
    std::vector<Transaction> showTransactionsByCategory(Category category) const;

    ///////////// Calculation//////////////
    double showHighestExpense() const;
    double calculateCurrentBalance() const;

    ///////////////// Calculation Categories Amount //////////////////////
    template <typename CalculateWhat>
    double calculateAmount(CalculateWhat calculatewhat) const;
    double calculateTotalIncome() const;
    double calculateTotalExpenses() const;
    double calculateTotalIncomeFromWork() const;
    double calculateTotalIncomeFromBusiness() const;
    double calculateTotalExpensesOnCar() const;
    double calculateTotalExpensesOnHome() const;
    double calculateTotalExpensesOnHoliday() const;
    double calculateTotalExpensesOnGym() const;
    double calculateTotalExpensesOnOther() const;


    ///////////////// Calculation % of Expenses///////////////////////////
    void calculateProcentOfEachExpenses() const;


    /////////////////// Modify Transaction ////////////////////////////
    void modifyAmountOfTransaction(std::vector<Transaction>::iterator it,double newAmount);
    void modifyTypeOfTransaction(std::vector<Transaction>::iterator it,TransactionType newType);
    void modifyCategoryOfTransaction(std::vector<Transaction>::iterator it,Category newCategory);
    //void modifyDateOfTransaction(std::vector<Transaction>::iterator it,const std::string& newDate);
    void modifyDescriptionOfTransaction(std::vector<Transaction>::iterator it,const std::string& newDescription);


    bool removeTransaction(std::vector<Transaction>::iterator it);

    void showChoosenTransactions(const std::vector<Transaction> result);

    bool isEnd(std::vector<Transaction>::iterator it);

    /////////////////////// OPERATION WITH FILES ////////////////////////
    bool saveToFile();
    bool loadFromFile();
    void addInvalidRecord(const std::string& line,const  std::string& reason);

};



template <typename FindHow>
std::vector<Transaction>::iterator TransactionManager::findTransactionBy(FindHow findhow)
{
    if(transactions.empty())
    {
        return transactions.end();
    }
    auto it = find_if(transactions.begin(), transactions.end(), findhow);
    if(it!=transactions.end())
    {
        return it;
    }
    return transactions.end();
}

template <typename SearchTransactionsBy>
std::vector<Transaction> TransactionManager::showTransactionsBy(SearchTransactionsBy searchtransactionsby) const
{
    std::vector<Transaction>result;
    std::copy_if(transactions.begin(), transactions.end(),std::back_inserter(result), searchtransactionsby);
    return result;
}

template <typename CalculateWhat>
double TransactionManager::calculateAmount(CalculateWhat calculatewhat) const
{
    double amount= 0.0;
    amount = accumulate(transactions.begin(), transactions.end(),0.0, calculatewhat);
    return amount;
}
