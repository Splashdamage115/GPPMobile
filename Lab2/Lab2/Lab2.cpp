// David Strikaitis
#include <iostream>

#define X_SIZE 5
#define Y_SIZE 5

int ReplaceWithMinusOne(char arr[X_SIZE][Y_SIZE])
{
    int score = 0;
    for (int x = 0; x < X_SIZE; x++)
    {
        for (int y = 0; y < Y_SIZE; y++)
        {
            if (arr[x][y] == 5)
                continue;
            int count = 0;
            for (int i = x + 1; i < X_SIZE; i++)
            {
                if (arr[x][y] == arr[i][y])
                {
                    count++;
                }
                else
                    break;
            }
            if (count >= 2)
            {
                if (arr[x][y] != 32)
                    score += (count + 1) * arr[x][y];
                for (int i = x; i <= x + count; i++)
                {
                    arr[i][y] = 32;
                }
            }

            count = 0;
            for (int i = y + 1; i < Y_SIZE; i++)
            {
                if (arr[x][y] == arr[x][i])
                {
                    count++;
                }
                else
                    break;
            }
            if (count >= 2)
            {
                if(arr[x][y] != 32)
                    score += (count + 1) * arr[x][y];
                for (int i = y; i <= y + count; i++)
                {
                    arr[x][i] = 32;
                }
            }
        }
    }
    return score;
}

void printTable(char arr[X_SIZE][Y_SIZE])
{
    for (int x = 0; x < X_SIZE; x++)
    {
        for (int y = 0; y < Y_SIZE; y++)
        {
            std::cout << arr[y][x] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "-------------------------";
    std::cout << std::endl;
}

void FallDownAndReplace(char arr[X_SIZE][Y_SIZE])
{
    for (int x = 0; x < X_SIZE; x++)
    {
        for (int y = 0; y < Y_SIZE; y++)
        {
            if (arr[x][y] == 32)
            {
                for (int i = y; i >= 0; i--)
                {
                    arr[x][i] = arr[x][i - 1];
                }
                arr[x][0] = 5;
            }
        }
    }
}

void makeTables(char arr[X_SIZE][Y_SIZE])
{
    int score = 0;

   

    printTable(arr);
    score += ReplaceWithMinusOne(arr);
    printTable(arr);
    FallDownAndReplace(arr);
    printTable(arr);
}

int main()
{
    char arr[X_SIZE][Y_SIZE];
    srand(time(nullptr));

    for (int x = 0; x < X_SIZE; x++)
        for (int y = 0; y < Y_SIZE; y++)
            arr[x][y] = rand() % 4 + 1;

    

    while (true)
    {
        makeTables(arr);
        std::cin.get();
    }

}


