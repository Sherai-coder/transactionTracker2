#include <iostream>
#include "transaction.h"
#include "transactionManager.h"
#include "parse.h"
#include "input.h"
#include "menu.h"
#include "date.h"

using namespace std;

TransactionManager transactions;

int main()
{
    Menu menu(transactions);
    menu.menuRun();











    return 0;
}
