#pragma once
#include <string>
#include "transaction.h"


std::string typeToString(TransactionType type);
TransactionType stringToType(const std::string& typeStr);
Category stringToCategory(const std::string& categoryStr);
std::string categoryToString(Category category);
std::string proceedDataToString(int day, int month, int year);
std::string dateToString(Date date);
