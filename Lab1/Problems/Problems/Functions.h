// David Strikaitis
#pragma once
#include <iostream>

bool isLeapYear(int year)
{
	if (year % 4 == 0)
	{
		if (year % 100 == 0)
		{
			if (year % 400 == 0)
			{
				return true;
			}
		}
		else
		{
			return true;
		}
	}
	return false;
}

int Reversed(int testNumber)
{
	return 0;
}
int inputCharToNum()
{
	char* input;
	input = new char();
	std::cin >> input;
	int multi = 1;
	int i = 0;
	int out = 0;
	while (input[i] != NULL)
	{
		i++;
	}
	i--;
	while (i != -1)
	{
		if (input[i] >= 48 && input[i] <= 57)
		{
			out += (input[i] - 48) * multi;
			multi *= 10;
		}
		else
		{
			return 0;
		}
		i--;
	}
	return out;
}

bool isAPalindrome(int testNumber)
{
	bool check = true;
	int numSize = 0;
	int sqr = 10;

	for (int i = 0; i < 20; i++)
	{
		sqr = sqr * 10;
		if (sqr > testNumber)
			break;

		numSize++;
	}

	int factor = 10;

	for (int i = 0; i < numSize; i++)
		factor = factor * 10;

	int newFactor = 10;

	for (int i = 0; i < numSize; i++)
	{
		if ((testNumber % newFactor) / (newFactor / 10) == (testNumber / factor) % 10)
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
bool isAPrimeNumber(int numbertoTest)
{
	if (numbertoTest == 0)
		return false;

	if (numbertoTest < 0)
		numbertoTest *= -1;

	for (int i = 2; i < numbertoTest; i++)
	{
		if (numbertoTest % i == 0)
		{
			return false;
		}
	}
	return true;
}
int input5CharsConvertToInt()
{
	int returnInt = 0;
	char inputChar;
	int sqr = 1;
	for (int i = 0; i < 5; i++)
	{
		std::cin >> inputChar;
		
		if (inputChar >= 48 && inputChar <= 57)
		{
			returnInt += (inputChar - 48) * (sqr);
			sqr = sqr * 10;
			std::cout << "so far: " << returnInt << std::endl;
		}
	}
	return returnInt;
}
int convertBinarytoDecimal(int binaryNumber)
{
	int i = 1;
	int digitFactor = 1;
	int factor = 2;
	int total = binaryNumber % 10;
	std::cout << total + 1 << std::endl;

	while (i * digitFactor < binaryNumber)
	{
		total += (binaryNumber % (digitFactor)) * factor;
		factor *= 2;
		digitFactor *= 10;

		std::cout << total + 1 << std::endl;

		i++;
	} 
	total += 1;
	return total;
}
void drawRightAngledTriangle()
{

}
void drawIsocelesTriangle()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 1 + i; j++)
		{
			std::cout << "A";
		}
		std::cout << std::endl;
	}
}
void drawIsocelesTriangle2()
{
	int change = 0;
	for (int i = 0; i < 9; i++)
	{
		if (i > 3)
			change = 8 - i;
		else
			change = i;
		for (int j = 0; j < 1 + change; j++)
		{
			std::cout << "A";
		}
		std::cout << std::endl;
	}
}

int find(int size, int arr[], int toFind)
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == toFind)
		{
			return i;
		}
	}
	return -1;
}
int find2ndLargest(int size, int arr[])
{
	if (size <= 0)
		return -1;

	int biggest = arr[0];
	int second = arr[0];

	for (int i = 1; i < size; i++)
	{
		if (arr[i] > biggest)
		{
			second = biggest;
			biggest = arr[i];
		}
	}
	return second;
}
void copyArraytoArray(int size, int arr1[], int arr2[])
{
	for (int i = 0; i < size; i++)
	{
		arr2[i] = arr1[i];
	}
}
bool insertElement(int& size, int& count, int arr[], int elementToInsert, int insertIndex)
{
	if (insertIndex > size || insertIndex < 0)
		return false;

	count++;

	for (int i = insertIndex; i < count; i++)
	{
		if (i + 1 < size)
		{
			arr[i + 1] = arr[i];
		}
	}
	arr[insertIndex] = elementToInsert;
	return true;
}
bool deleteElement(int& size, int& count, int arr[], int deleteIndex)
{
	if (deleteIndex < 0 || deleteIndex > count)
		return false;

	for (int i = deleteIndex; i < count; i++)
	{
		if (i - 1 > 0)
		{
			arr[i - 1] = arr[i];
		}
	}
	count--;
	return true;
}
int frequencyCount(int size, int arr[], int value)
{
	int count = 0;

	for (int i = 0; i < size; i++)
	{
		if (arr[i] == value)
			count++;
	}

	return count;
}
int countDuplicates(int size, int arr[])
{
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		bool notFound = true;
		for (int j = i; j > 0; j--)
		{
			if (arr[i] == arr[j])
			{
				notFound = false;
				break;
			}
		}
		if (notFound)
		{
			for (int j = i; j < size; j++)
			{

				if (arr[i] == arr[j])
					count++;
			}
		}
	}
	return count;
}
void reverse(int size, int arr[])
{
	for (int i = 0; i < size; i++)
	{
		int temp = arr[i];
		arr[i] = arr[size - i];
		arr[size - i] = temp;
	}
}
int rotateLeft(int size, int arr[])
{
	int first = arr[0];
	for (int i = 0; i < size - 1; i++)
	{
		arr[i] = arr[i + 1];
	}
	arr[size - 1] = first;
}
bool twoMovies(int flightLength, int movieLengths[], int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i == j)
				continue;
			if (movieLengths[i] + movieLengths[j] == flightLength)
			{
				return true;
			}
		}
	}
	return false;
}
int wordCounter(int size, char characters[])
{
	int words = 1; // start at one word because the last word wont have a space after it
	for (int i = 0; i < size; i++)
	{
		if (characters[i] == ' ')
		{
			words++;
		}
	}
	return words;
}