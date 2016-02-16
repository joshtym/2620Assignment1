//********************************************************************
// Course: CPSC2620 Fall 2013
// Name: Josh Tymburski
// Assignment #1
// Problem #2
// Professor: Howard Cheng
// Program: median2.cc
// Purpose: Given a set of numbers, the program takes them and allocates
//          an array which is then sorted and the median is found.
// Programming Partner: Anthony Tymburski
//********************************************************************
#include<iostream>
using namespace std;

// Function Prototypes
void sort(int*, int);
void swap(int&, int&);
double median(int*, int);
bool isEven(int);
int *resize(int*, int);

int main()
{
	// Variable Declarations
	int value;
	int n = 0;
	int *A;
	double Median;
	
	// Creates new array of size 0
	A = new int[n];

	cout << "Enter a positive integer (< 1 to quit): ";
	cin >> value;
	
	while (value > 0)
	{	
		// Calculations and Output
		
		// Makes the array one slot bigger
		A = resize(A, n);
		
		// Inputs the user entered value into the newly sized array
		A[n] = value;
		
		n++;
		
		// Sorts the array from smallest to largest integer
		sort(A, n);
		
		// Returns the value of the median of the dynamically changing
		// array
		Median = median(A, n);
		
		cout << "The median is now " << Median << "." << endl;
		
		cout << "Enter a positive integer(< 1 to quit): ";
		cin >> value;
	}
	
	delete[] A;
	A = NULL;
	
	return 0;
}

//Functions
//*****************************************************************
// Function takes in array and sorts it from least to greatest
//*****************************************************************
void sort(int *A, int n)
{
	bool switched = true;
	int lastValue = n - 1;
	
	while (switched && lastValue > 0)
	{
		switched = false;
		for (int i = 0; i < lastValue; i++)
		{
			if (A[i+1] < A[i])
			{
				switched = true;
				swap (A[i+1], A[i]);
			}
		}
		lastValue--;
	}
}

//******************************************************************
// Function swaps two values in the array
//******************************************************************
void swap(int& a, int&b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}

//******************************************************************
// Function takes the sorted array and determines the median
//******************************************************************
double median(int *A, int n)
{
	double Median;
	bool even;
	int tempValue, tempValue2;
	
	even = isEven(n);
		
	if (even)
	{
		tempValue = A[n/2];
		tempValue2 = A[n/2 - 1];
		Median = (tempValue + tempValue2) / 2.0;
		return Median;
	}
	else
	{
		Median = static_cast<double>(A[n/2]);
		return Median;
	}
}

//*******************************************************************
// Function determines whether the number of elements in the array is
// even or not
//*******************************************************************
bool isEven(int a)
{
	if (a%2 == 0)
		return true;
	else
		return false;
}

int *resize(int *A, int n)
{
	int *temp;
	
	temp = new int[n+1];
	
	for (int i = 0; i < n; i++)
	{
		temp[i] = A[i];
	}
	
	delete[] A;
	A = NULL;
	
	return temp;
}
