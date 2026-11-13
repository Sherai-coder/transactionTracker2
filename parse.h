#include <iostream>
#include "transaction.h"
#include "dateToString.h"

enum class ParseStatus
{
    Success,
    InvalidArgument,
    OutOfRange,
    InvalidFormat
};


struct ParseResultInt
{
    ParseStatus status;
    int value;
};

struct ParseResultDouble
{
    ParseStatus status;
    double value;
};

struct ParseResultDescription
{
    ParseStatus status;
    std::string description;
};

struct ParseDateResult
{
    ParseStatus status;
    std::string date;
};

struct ParseTransactionResult
{
    ParseStatus status;
    int id;
    double amount;
    TransactionType type;
    Category category;
    std::string date;
    std::string description;
};



ParseResultInt tryParseId(const std::string& idStr);
ParseResultDouble tryParseAmount(const std::string& amountStr);
ParseDateResult tryParseDate(const std::string& dateStr);
ParseResultDescription tryParseDescription(const std::string& description);
ParseTransactionResult tryParseTransaction(const std::string& idStr,const std::string& amountStr,const std::string&  dateStr,const std::string&  description,
                                           const std::string& categoryStr,const std::string&  typeStr);



std::string statusToString(ParseStatus status);
bool isValidDay(int day);
bool isValidMonth(int month);
bool isValidYear(int year);
bool checkLeapYear(int year);
int daysOfMonth(int month,int year);


