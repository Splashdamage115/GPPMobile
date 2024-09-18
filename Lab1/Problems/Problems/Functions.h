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
	return 0;
}
void drawRightAngledTriangle()
{

}
void drawIsocelesTriangle()
{

}
void drawIsocelesTriangle2()
{

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
	return;
}
bool insertElement(int& size, int& count, int arr[], int elementToInsert, int insertIndex)
{

	return false;
}
bool deleteElement(int& size, int& count, int arr[], int deleteIndex)
{

	return true;
}
int frequencyCount(int size, int arr[], int value)
{

	return 0;
}
int countDuplicates(int size, int arr[])
{

	return 0;
}
void reverse(int size, int arr[])
{
	return;
}
int rotateLeft(int size, int arr[])
{
	return -1;
}
bool twoMovies(int flightLength, int movieLengths[], int size)
{
	return false;
}
int wordCounter(int size, char characters[])
{
	return 0;
}