#include <iostream>
#include "transactionManager.h"
#include <algorithm>
#include <utility>
#include <fstream>
#include "dateToString.h"
#include <sstream>
#include "parse.h"

/////////////// Create Transaction / ADD transaction //////////////////////////
std::optional<Transaction> TransactionManager::createTransaction(int id, double amount, TransactionType type, Category category,const std::string& description, Date date)
{
    switch(type)
    {
    case TransactionType::income:
    {
        return Transaction(id,amount,type,category,description,date);
    }
    case TransactionType::expenses:
    {
        return Transaction(id,amount,type,category,description,date);
    }
    default:
        return std::nullopt;
    }
}

bool TransactionManager::addTransaction(double amount,TransactionType type, Category category,const std::string& description, Date date)
{
    auto it = createTransaction(nextId,amount,type,category,description,date);
    if(it!=std::nullopt)
    {
        transactions.push_back((*it));
        nextId++;
        return true;
    }
    return false;

}
////////////////////////////////// END ////////////////////////////////////////


////////////////////////////////// VIEW FOR TRANSACTIONS ///////////////////////////////////
void TransactionManager::showAllTransactions() const
{
    for(const auto& transaction : transactions)
    {
        transaction.showTransaction();
    }
}
void TransactionManager::seeSpecificTransaction(std::vector<Transaction>::iterator it) const
{
    if(it!=transactions.end())
    {
        (*it).showTransaction();
    }
}
//////////////////////////////// END /////////////////////////////////////

///////////////////////////// Find Transaction /////////////////////////////////////
std::vector<Transaction>::iterator TransactionManager::findTransactionById(int id)
{
    return findTransactionBy([&id] (Transaction& transaction)
    {
        return transaction.getId()==id;
    });
}
std::vector<Transaction>::iterator TransactionManager::findTransactionByAmount(double amount)
{
    return findTransactionBy([&amount] (Transaction& transaction)
    {
        return transaction.getAmount()==amount;
    });
}
std::vector<Transaction>::iterator TransactionManager::findTransactionByType(TransactionType type)
{
    return findTransactionBy([&type] (Transaction& transaction)
    {
        return transaction.getType()==type;
    });
}
std::vector<Transaction>::iterator TransactionManager::findTransactionByCategory(Category category)
{
    return findTransactionBy([&category] (Transaction& transaction)
    {
        return transaction.getCategory()==category;
    });
}
/*std::vector<Transaction>::iterator TransactionManager::findTransactionByDate(const std::string& dateStr)
{
    return findTransactionBy([&dateStr] (Transaction& transaction)
    {
        return transaction.getDateStr()==dateStr;
    });
}*/

///////////////////////////     END   ///////////////////////////////////////



///////////////////////////////// REMOVE TRANSACTION /////////////////////////
bool TransactionManager::removeTransaction(std::vector<Transaction>::iterator it)
{
    if(it!=transactions.end())
    {
        transactions.erase(it);
        return true;
    }
    return false;
}
///////////////////////// END /////////////////////////////////////


///////////////////////////////  SHOW TRANSACTION BY ////////////////////////////
std::vector<Transaction> TransactionManager::showTransactionsByAmount(double amount) const
{
    return showTransactionsBy([&amount] (const Transaction& transaction)
    {
        return transaction.getAmount()==amount;
    });
}
std::vector<Transaction> TransactionManager::showTransactionsByType(TransactionType type) const
{
    return showTransactionsBy([&type](const Transaction& transaction)
    {
        return transaction.getType()==type;
    });
}
std::vector<Transaction> TransactionManager::showTransactionsByCategory(Category category) const
{
    return showTransactionsBy([&category] (const Transaction& transaction)
    {
        return transaction.getCategory()==category;
    });
}
///////////////////////////////// END //////////////////////////////////////

////////////////////////// CALCULATION /////////////////////////////////
double TransactionManager::showHighestExpense() const
{
    double amount = 0.0;
    if(transactions.empty())
    {
        return amount;
    }
    for (const Transaction& transaction : transactions)
    {
        if(transaction.getType()==TransactionType::expenses && transaction.getAmount()>amount)
        {
            amount=transaction.getAmount();
        }
    }

    return amount;
}

double TransactionManager::calculateCurrentBalance() const
{
    return calculateTotalIncome()-calculateTotalExpenses();
}
//////////////////////////////////////////////////////////////


///////////////// Calculation Categories Amount //////////////////////
double TransactionManager::calculateTotalIncome() const
{
    return calculateAmount([](double amount, const Transaction& transaction)
    {
        if(transaction.getType()==TransactionType::income)
        {
            return amount+transaction.getAmount();
        }
        else return amount;
    });
}
double TransactionManager::calculateTotalExpenses() const
{
    return calculateAmount([](double amount, const Transaction& transaction)
    {
        if(transaction.getType()==TransactionType::expenses)
        {
            return amount+transaction.getAmount();
        }
        else return amount;
    });
}
double TransactionManager::calculateTotalIncomeFromWork() const
{
    return calculateAmount([](double amount,const Transaction& transaction)
    {
        if(transaction.getCategory()==Category::work)
        {
            return amount+transaction.getAmount();
        }
        else return amount;
    });
}
double TransactionManager::calculateTotalIncomeFromBusiness() const
{
    return calculateAmount([](double amount,const Transaction& transaction)
    {
        if(transaction.getCategory()==Category::business)
        {
            return amount+transaction.getAmount();
        }
        else return amount;
    });
}
double TransactionManager::calculateTotalExpensesOnCar() const
{
    return calculateAmount([](double amount,const Transaction& transaction)
    {
        if(transaction.getCategory()==Category::car)
        {
            return amount+transaction.getAmount();
        }
        else return amount;
    });
}
double TransactionManager::calculateTotalExpensesOnHome() const
{
    return calculateAmount([](double amount,const Transaction& transaction)
    {
        if(transaction.getCategory()==Category::home)
        {
            return amount+transaction.getAmount();
        }
        else return amount;
    });
}
double TransactionManager::calculateTotalExpensesOnHoliday() const
{
    return calculateAmount([](double amount,const Transaction& transaction)
    {
        if(transaction.getCategory()==Category::holiday)
        {
            return amount+transaction.getAmount();
        }
        else return amount;
    });
}
double TransactionManager::calculateTotalExpensesOnGym() const
{
    return calculateAmount([](double amount,const Transaction& transaction)
    {
        if(transaction.getCategory()==Category::gym)
        {
            return amount+transaction.getAmount();
        }
        else return amount;
    });
}
double TransactionManager::calculateTotalExpensesOnOther() const
{
    return calculateAmount([](double amount,const Transaction& transaction)
    {
        if(transaction.getCategory()==Category::other)
        {
            return amount+transaction.getAmount();
        }
        else return amount;
    });
}
//////////////////////////////////////////////////////////////////////

void TransactionManager::calculateProcentOfEachExpenses() const
{
    std::cout<<"Car: "<<(calculateTotalExpensesOnCar()/calculateTotalExpenses())*100<<"%"<<std::endl;
    std::cout<<"Home: "<<(calculateTotalExpensesOnHome()/calculateTotalExpenses())*100<<"%"<<std::endl;
    std::cout<<"Holiday: "<<(calculateTotalExpensesOnHoliday()/calculateTotalExpenses())*100<<"%"<<std::endl;
    std::cout<<"Gym: "<<(calculateTotalExpensesOnGym()/calculateTotalExpenses())*100<<"%"<<std::endl;
    std::cout<<"Other: "<<(calculateTotalExpensesOnOther()/calculateTotalExpenses())*100<<"%"<<std::endl;
}
////////////////////////// Modify TRansaction ///////////////////////////////
void TransactionManager::modifyAmountOfTransaction(std::vector<Transaction>::iterator it,double newAmount)
{
    if(it!=transactions.end())
    {
        (*it).changeAmount(newAmount);
    }
}
void TransactionManager::modifyTypeOfTransaction(std::vector<Transaction>::iterator it, TransactionType newType)
{
    if(it!=transactions.end())
    {
        (*it).changeType(newType);
    }
}
void TransactionManager::modifyCategoryOfTransaction(std::vector<Transaction>::iterator it, Category newCategory)
{
    if(it!=transactions.end())
    {
        (*it).changeCategory(newCategory);
    }
}
/*void TransactionManager::modifyDateOfTransaction(std::vector<Transaction>::iterator it, const std::string& newDate)
{
    if(it!=transactions.end())
    {
        (*it).changeDate(newDate);
    }
}*/
void TransactionManager::modifyDescriptionOfTransaction(std::vector<Transaction>::iterator it, const std::string& newDescription)
{
    if(it!=transactions.end())
    {
        (*it).changeDescription(newDescription);
    }
}



////////////////////////////////////////////////////////////
void TransactionManager::showChoosenTransactions(const std::vector<Transaction> result)
{
    for (const Transaction& transaction : result)
    {
        transaction.showTransaction();
    }
}


bool TransactionManager::isEnd(std::vector<Transaction>::iterator it)
{
    if(it==transactions.end())
    {
        return true;
    }
    return false;
}


//////////////////////////// OPERATION WITH FILES//////////////////////////////////
int TransactionManager::setHighestUsedId()
{
    if(transactions.empty())
    {
        return 0;
    }
    auto it = max_element(transactions.begin(), transactions.end(), [] (const Transaction& transaction1, const Transaction& transaction2)
    {
        return transaction1.getId()<transaction2.getId();
    });
    if((*it).getId()>highestUsedIdFromFile)
    {
        return (*it).getId();
    }
    return highestUsedIdFromFile;
}
bool TransactionManager::saveToFile()
{
    std::ofstream plik;
    plik.open("date.txt");
    if(!plik)
    {
        return false;
    }
    if(transactions.empty())
    {
        return false;
    }
    highestUsedId=setHighestUsedId();
    plik<<highestUsedId<<std::endl;
    for (const Transaction& transaction : transactions)
    {
        plik<<transaction.getId()<<'|'<<transaction.getAmount()<<'|'<<typeToString(transaction.getType())<<'|'<<categoryToString(transaction.getCategory())<<'|'
        <<transaction.getDescription()<<'|'<<dateToString(transaction.getDate())<<std::endl;
    }
    plik.close();
    return true;
}

bool TransactionManager::loadFromFile()
{
    std::ifstream plik;
    plik.open("date.txt");
    if(!plik)
    {
        return false;
    }
    std::string line;
    std::string highestUsedIdStr,idStr, amountStr, typeStr,categoryStr, descriptionStr, dateDateStr;
    getline(plik,highestUsedIdStr);
    ParseResultInt highestUsedIdParse = tryParseId(highestUsedIdStr);
    if(highestUsedIdParse.status==ParseStatus::Success)
    {
        highestUsedIdFromFile = highestUsedIdParse.value;
    }
    while(getline(plik,line))
    {
        ParseTransactionResult loadedTransaction;
        invalidTransactionRecord invalidLoadedRecords;
        std::string invalidData, invalidReason;
        std::stringstream ss(line);
        if((!getline(ss,idStr,'|')) || (!getline(ss,amountStr,'|')) || (!getline(ss,typeStr,'|')) || (!getline(ss,categoryStr,'|')) ||
                 (!getline(ss,descriptionStr,'|')) || (!getline(ss,dateDateStr,'|')) )
        {
            addInvalidRecord(line,"Missing record.");
            continue;
        }
        else if(idStr.empty() || amountStr.empty() || typeStr.empty() || categoryStr.empty() || descriptionStr.empty() || dateDateStr.empty())
        {
            addInvalidRecord(line,"Missing record.");
            continue;
        }
        else
        {
            loadedTransaction = tryParseTransaction(idStr,amountStr,descriptionStr,categoryStr,typeStr,dateDateStr);
        }
        if(loadedTransaction.status==ParseStatus::Success)
        {
            std::optional<Transaction> it;
            try
            {
                it = createTransaction(loadedTransaction.id,loadedTransaction.amount,loadedTransaction.type,
                                            loadedTransaction.category,loadedTransaction.description,*loadedTransaction.date);
            }
            catch(const std::invalid_argument& e)
            {
                std::cout<<"unssacesfull"<<std::endl;
                invalidData = idStr+'|'+amountStr+'|'+typeStr+'|'+categoryStr+'|'+descriptionStr+'|'+dateDateStr;
                invalidReason = statusToString(loadedTransaction.status);
                addInvalidRecord(invalidData,invalidReason);
            }
            catch(const std::out_of_range& e)
            {
                invalidData = idStr+'|'+amountStr+'|'+typeStr+'|'+categoryStr+'|'+descriptionStr+'|'+dateDateStr;
                invalidReason = statusToString(loadedTransaction.status);
                addInvalidRecord(invalidData,invalidReason);
            }
            if(it)
            {
                transactions.push_back(*it);
            }
        }
        else
        {
            invalidData = idStr+'|'+amountStr+'|'+typeStr+'|'+categoryStr+'|'+descriptionStr+'|'+dateDateStr;
            invalidReason = statusToString(loadedTransaction.status);
            addInvalidRecord(invalidData,invalidReason);
        }
    }
    if(highestUsedIdFromFile>setHighestUsedId())
    {
        highestUsedId=highestUsedIdFromFile;
    }

    return true;
}

void TransactionManager::addInvalidRecord(const std::string& line,const  std::string& reason)
{
    invalidTransactionRecord invalidRecord;
    invalidRecord.setData(line);
    invalidRecord.setReason(reason);
    invalidRecords.push_back(invalidRecord);
}
