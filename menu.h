#pragma once
#include "transactionManager.h"

enum class MainMenuOption
{
    ShowAllTransactions=1,
    ShowSpecificTransaction,
    AddTransaction,
    SearchTransactionsBy,
    MakeCalculations,
    MakeSpecificCalculations,
    CalculateProcentOfEachExpenses,
    ModifyTransaction,
    RemoveTransaction,
    Exit
};

enum class FindTransactionBy
{
    ById=1,
    ByAmount,
    ByType,
    ByCategory,
    Exit
};

enum class SearchTransactionsBy
{
    ByAmount=1,
    ByType,
    ByCategory,
    Exit
};

enum class MakeCalculationsOf
{
    HighestExpenses=1,
    CurrentBalance,
    Exit
};

enum class ShowSpecificCalculation
{
    TotalIncome=1,
    TotalExpenses,
    IncomeFromWork,
    IncomeFromBusiness,
    ExpensesOnCar,
    ExpensesOnHome,
    ExpensesOnHoliday,
    ExpensesOnGym,
    ExpensesOnOther,
    Exit

};

enum class ModifyChoices
{
    Amount=1,
    Type=2,
    Category=3,
    Description,
    Exit
};
class Menu
{
    TransactionManager& transactions;

public:
    Menu(TransactionManager& transactions) : transactions(transactions){}
    void menuRun();
    void mainMenu();
    void showAllTransactionsMenu();
    void seeSpecificTransactionMenu();
    std::optional<std::vector<Transaction>::iterator> findTransactionByMenu();
    void addTransactionMenu();
    void searchTransactionsByMenu();
    void makeCalculationsMenu();
    void makeSpecificCalculationsMenu();
    void calculateProcentOfEachExpensesMenu();
    void modifyTransactionMenu();
    void removeTransactionMenu();
};
