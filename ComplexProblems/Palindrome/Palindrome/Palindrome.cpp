#include <iostream>

bool palindrome(int num)
{
    bool check = true;
    int numSize = 0;
    int sqr = 10;

    for (int i = 0; i < 20; i++)
    {
        numSize++;

        sqr = sqr * 10;
        if (sqr > num)
            break;
    }

    int factor = 10;

    for (int i = 0; i < numSize; i++)
        factor = factor * 10;

    int newFactor = 10;

    for (int i = 0; i < numSize; i++)
    {
        if ((num % newFactor) / (newFactor / 10) == (num / factor) % 10)
        {
            factor = factor / 10;
            newFactor = newFactor * 10;
        }
        else
        {
            check = false;
            break;
        }
    }
    return check;
}

int main()
{
    int numToCheck = 321123;

    if (palindrome(numToCheck))
    {
        std::cout << "is a palindrome" << std::endl;
    }
    else
    {
        std::cout << "not a palindrome" << std::endl;
    }
}


