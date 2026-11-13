#include <iostream>
#include "transaction.h"
#include "transactionManager.h"
#include "parse.h"
#include "input.h"
#include "menu.h"
#include "date.h"

using namespace std;



int main()
{
    Transaction transaction(1,2,TransactionType::income, Category::car,"20.2.1994","blablabla");

    Date date(+10,01,1994);
    string data = date.showDate();
    cout<<data<<endl;







    return 0;
}
