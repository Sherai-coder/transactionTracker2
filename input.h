#include <iostream>
#include "transaction.h"
#include "dateToString.h"
#include "date.h"
#include <optional>

int getInt(const std::string& message, const int& minRange, const int& maxRange);
std::string getNumber(const std::string& message,const int& minRange, const int&maxRange);
TransactionType getTransactionType(const std::string& message);
double getDouble(const std::string& message, const double& minRange, const double& maxRange);
Category getCategoryType(const std::string& message);
std::string getDescription(const std::string& message,const size_t& minRange, const size_t& maxRange);
std::string getWord(const std::string);
void pause();
std::optional<Date> returnDateDate(const std::string& message);

