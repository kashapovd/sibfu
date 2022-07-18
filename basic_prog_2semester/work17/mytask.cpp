#include "mytask.h"
#include <math.h>
MyTask::MyTask() {}

LIST::Node *MyTask::searchPerfect(LIST::Node *list)
{
    while (list)
    {
        if(isPerfect(list->data))
        {
            return list;
        }
        list = list->link;
    }

    return nullptr;
}

bool MyTask::isPerfect(int num)
{
    int divsum = 0;
    if (num == 1)
        return false;
    for (int i = sqrt(num) ; i > 1; i--)
    {
        if (num % i == 0)
        {
            divsum+=i;
            divsum+=num/i;
        }
    }
    if (divsum+1 == num)
        return true;
    return false;

}

int MyTask::genNum(int startNum)
{
    return startNum + abs(rand() % 10);
}
