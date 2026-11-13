#include "menu.h"
#include "input.h"
using namespace std;

void Menu::menuRun()
{
    if(!transactions.loadFromFile())
    {
        cout<<"There was a problem to load a file."<<endl;
    }
    mainMenu();
    if(!transactions.saveToFile())
    {
        cout<<"Records cound't be saved."<<endl;
    }
}
void Menu::mainMenu()
{
    while (true)
    {
        cout<<"1. Show all transactions."<<endl;
        cout<<"2. See specific transaction."<<endl;
        cout<<"3. Add transaction."<<endl;
        cout<<"4. Search transactions by:"<<endl;
        cout<<"5. Make calculations."<<endl;
        cout<<"6. Make specific calculations."<<endl;
        cout<<"7. Calculate procent of each expanses."<<endl;
        cout<<"8. Modify transaction."<<endl;
        cout<<"9. Remove transaction."<<endl;
        cout<<"10. Exit."<<endl;
        MainMenuOption choice = static_cast<MainMenuOption>(getInt("Choose: ",1,10));
        switch(choice)
        {
        case MainMenuOption::ShowAllTransactions:
        {
            showAllTransactionsMenu();
            break;
        }
        case MainMenuOption::ShowSpecificTransaction:
        {
            seeSpecificTransactionMenu();
            break;
        }
        case MainMenuOption::AddTransaction:
        {
            addTransactionMenu();
            break;
        }
        case MainMenuOption::SearchTransactionsBy:
        {
            searchTransactionsByMenu();
            break;
        }
        case MainMenuOption::MakeCalculations:
        {
            makeCalculationsMenu();
            break;
        }
        case MainMenuOption::MakeSpecificCalculations:
        {
            makeSpecificCalculationsMenu();
            break;
        }
        case MainMenuOption::CalculateProcentOfEachExpenses:
        {
            calculateProcentOfEachExpensesMenu();
            break;
        }
        case MainMenuOption::ModifyTransaction:
        {
            modifyTransactionMenu();
            break;
        }
        case MainMenuOption::RemoveTransaction:
        {
            removeTransactionMenu();
            break;
        }
        case MainMenuOption::Exit:
        {
            cout<<"Goodbye."<<endl;
            return;
        }
        default:
            {
                cout<<"There is no such option in menu."<<endl;
                pause();
            }

        }
    }

}
void Menu::showAllTransactionsMenu()
{
    transactions.showAllTransactions();
    pause();
}
void Menu::seeSpecificTransactionMenu()
{
    cout<<"How would you like to find transaction to display."<<endl;
    auto it = findTransactionByMenu();
    if(!it)
    {
        pause();
        return;
    }
    if(transactions.isEnd(*it))
    {
        pause();
        return;
    }
    transactions.seeSpecificTransaction(*it);
    pause();
}

optional<std::vector<Transaction>::iterator> Menu::findTransactionByMenu()
{
    int searchId;
    double searchAmount;
    string typeStr, categoryStr;
    TransactionType searchType;
    Category searchCategory;
    string dateStr;
    std::vector<Transaction>::iterator it;
    cout<<"1. By id."<<endl;
    cout<<"2. By amount."<<endl;
    cout<<"3. By type."<<endl;
    cout<<"4. By category."<<endl;
    cout<<"5. By date."<<endl;
    cout<<"6. Exit."<<endl;
    FindTransactionBy choice = static_cast<FindTransactionBy>(getInt("Choose: ",1,6));
    switch(choice)
    {
    case FindTransactionBy::ById:
    {
        cout<<"Enter id: ";
        cin>>searchId;
        it=transactions.findTransactionById(searchId);
        break;
    }
    case FindTransactionBy::ByAmount:
    {
        cout<<"Enter amount: ";
        cin>>searchAmount;
        it=transactions.findTransactionByAmount(searchAmount);
         break;
    }
    case FindTransactionBy::ByType:
    {
        cout<<"Enter type: ";
        cin>>typeStr;
        it=transactions.findTransactionByType(stringToType(typeStr));
         break;
    }
    case FindTransactionBy::ByCategory:
    {
        cout<<"Enter category: ";
        cin>>categoryStr;
        it=transactions.findTransactionByCategory(stringToCategory(categoryStr));
         break;
    }
    case FindTransactionBy::ByDate:
    {
        cout<<"Enter date: ";
        cin>>dateStr;
        it=transactions.findTransactionByDate(dateStr);
         break;
    }
    case FindTransactionBy::Exit:
    {
        cout<<"Return to main menu."<<endl;
        return nullopt;
    }
    default:
        return nullopt;
    }
    if(transactions.isEnd(it))
    {
        cout<<"There is no such transaction."<<endl;
    }
    return it;
}

void Menu::addTransactionMenu()
{
    double amount = getDouble("Enter amount: ",1,100000);
    TransactionType type = getTransactionType("Enter type: ");
    Category category = getCategoryType("Enter category: ");
    string dateStr = returnDate("Enter date: ");
    string description = getDescription("Enter description (max 150 characters): ",1,150);
    if(transactions.addTransaction(amount,type,category,dateStr,description))
    {
        cout<<"Transaction successfully added."<<endl;
    }
    else cout<<"Cound't add transaction."<<endl;
    pause();
}

void Menu::searchTransactionsByMenu()
{
    vector<Transaction> result;
    cout<<"How would you like to search transactions(1.amount, 2.type, 3.category): "<<endl;
    SearchTransactionsBy choice = static_cast<SearchTransactionsBy>(getInt("Choose: ",1,3));
    switch(choice)
    {
    case SearchTransactionsBy::ByAmount:
    {
        result = transactions.showTransactionsByAmount(getDouble("Enter amount: ", 1, 30000));
        break;
    }
    case SearchTransactionsBy::ByType:
    {
        result = transactions.showTransactionsByType(getTransactionType("Enter type: "));
        break;
    }
    case SearchTransactionsBy::ByCategory:
    {
        result = transactions.showTransactionsByCategory(getCategoryType("Enter category: "));
        break;
    }
    case SearchTransactionsBy::Exit:
    {
        cout<<"Return to main menu."<<endl;
        return;
    }
    default:
        return;
    }
    if(result.empty())
    {
        cout<<"There is no transaction with this criteria."<<endl;
    }
    else transactions.showChoosenTransactions(result);
    pause();
}


void Menu::makeCalculationsMenu()
{
    double result;
    cout<<"1. Show highest expenses."<<endl;
    cout<<"2. Calculate current balance."<<endl;
    cout<<"3. Exit."<<endl;
    MakeCalculationsOf choice = static_cast<MakeCalculationsOf>(getInt("Choose: ",1, 3));
    switch(choice)
    {
    case MakeCalculationsOf::HighestExpenses:
    {
        result = transactions.showHighestExpense();
        break;
    }
    case MakeCalculationsOf::CurrentBalance:
    {
        result = transactions.calculateCurrentBalance();
        break;
    }
    case MakeCalculationsOf::Exit:
    {
        cout<<"Return to main menu."<<endl;
        pause();
        return;
    }
    default:
        return;
    }
    cout<<"Result: "<<result<<endl;
    pause();
}

void Menu::makeSpecificCalculationsMenu()
{
    double amount=0.0;
    cout<<"Which calculation would you like to do: "<<endl;
    cout<<"1. Total income."<<endl;
    cout<<"2. Total expenses."<<endl;
    cout<<"3. Income from work."<<endl;
    cout<<"4. Income from business."<<endl;
    cout<<"5. Expenses on car."<<endl;
    cout<<"6. Expenses on home."<<endl;
    cout<<"7. Expenses on holiday."<<endl;
    cout<<"8. Expenses on gym."<<endl;
    cout<<"9. Expenses on other."<<endl;
    cout<<"10. Exit."<<endl;
    ShowSpecificCalculation choice = static_cast<ShowSpecificCalculation>(getInt("Choose: ", 1, 10));
    switch(choice)
    {
    case ShowSpecificCalculation::TotalIncome:
    {
        amount = transactions.calculateTotalIncome();
        break;
    }
    case ShowSpecificCalculation::TotalExpenses:
    {
        amount = transactions.calculateTotalExpenses();
        break;
    }
    case ShowSpecificCalculation::IncomeFromWork:
    {
        amount = transactions.calculateTotalIncomeFromWork();
        break;
    }
    case ShowSpecificCalculation::IncomeFromBusiness:
    {
        amount = transactions.calculateTotalIncomeFromBusiness();
        break;
    }
    case ShowSpecificCalculation::ExpensesOnCar:
    {
        amount = transactions.calculateTotalExpensesOnCar();
        break;
    }
    case ShowSpecificCalculation::ExpensesOnHome:
    {
        amount = transactions.calculateTotalExpensesOnHome();
        break;
    }
    case ShowSpecificCalculation::ExpensesOnHoliday:
    {
        amount = transactions.calculateTotalExpensesOnHoliday();
        break;
    }
    case ShowSpecificCalculation::ExpensesOnGym:
    {
        amount = transactions.calculateTotalExpensesOnGym();
        break;
    }
    case ShowSpecificCalculation::ExpensesOnOther:
    {
        amount = transactions.calculateTotalExpensesOnOther();
        break;
    }
    case ShowSpecificCalculation::Exit:
    {
        cout<<"Back to main menu."<<endl;
        return;
    }
    default:
        return;
    }
    cout<<"Amount: "<<amount<<endl;
    pause();
}

void Menu::calculateProcentOfEachExpensesMenu()
{
    transactions.calculateProcentOfEachExpenses();
    pause();
}

void Menu::modifyTransactionMenu()
{
    cout<<"Choose the way to find transaction to modify."<<endl;
    auto it = findTransactionByMenu();
    if(!it || transactions.isEnd(*it) )
    {
        cout<<"Return to main menu."<<endl;
        pause();
        return;
    }

    cout<<"What would you like to modify: "<<endl;
    cout<<"1. Amount."<<endl;
    cout<<"2. Type."<<endl;
    cout<<"3. Category."<<endl;
    cout<<"4. Date."<<endl;
    cout<<"5. Description."<<endl;
    cout<<"6. Exit."<<endl;
    ModifyChoices choice = static_cast<ModifyChoices>(getInt("Choose: ",1,6));
    switch(choice)
    {
    case ModifyChoices::Amount:
    {
        transactions.modifyAmountOfTransaction(*it,getDouble("Enter new amount: ",1, 10000));
        break;
    }
    case ModifyChoices::Type:
    {
        transactions.modifyTypeOfTransaction(*it,getTransactionType("Enter new type: "));
        break;
    }
    case ModifyChoices::Category:
    {
        transactions.modifyCategoryOfTransaction(*it,getCategoryType("Enter new category: "));
        break;
    }
    case ModifyChoices::Date:
    {
        transactions.modifyDateOfTransaction(*it,returnDate("Enter date: "));
        break;
    }
    case ModifyChoices::Description:
    {
        transactions.modifyDescriptionOfTransaction(*it,getDescription("Enter description: ", 1, 150));
        break;
    }
    case ModifyChoices::Exit:
    {
        cout<<"Return to main menu."<<endl;
        return;
    }
    default: return;
    }
    pause();
}

void Menu::removeTransactionMenu()
{
    cout<<"How would you like to find transaction to remove."<<endl;
    auto it = findTransactionByMenu();
    if(!it)
    {
        pause();
        return;
    }
    if(transactions.isEnd(*it))
    {
        cout<<"There is no such transaction."<<endl;
        pause();
        return;
    }
    bool resultOfDelate = transactions.removeTransaction(*it);
    if(resultOfDelate)
    {
        cout<<"Transaction has been delated."<<endl;
    }
    else cout<<"Transaction could't be delete."<<endl;
    pause();
}
