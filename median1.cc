//********************************************************************
// Course: CPSC2620 Fall 2013
// Name: Josh Tymburski
// Assignment #1
// Problem #2
// Professor: Howard Cheng
// Program: median1.cc
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


int main()
{
	// Variable Declarations
	int n;
	int *A;
	double Median;
	
	cout << "Enter the size of the list (< 1 to quit): ";
	cin >> n;
	
	while (n > 0)
	{
		// Creates new array of user defined size
		A = new int[n];
		
		// Prompts user to enter all values into the array
		for (int i = 1; i <= n; i++)
		{
			cout << "Enter element " << i << ":";
			cin >> A[i-1];
		}
		
		// Calculations and Output
		
		// Sorts Array from smallest to largest integer
		sort(A, n);
		
		// Calculates and returns the median value of the array
		Median = median(A, n);
		
		cout << "The median is " << Median << "." << endl;
		
		delete[] A;
		A = NULL;
		
		cout << "Enter the size of the list (< 1 to quit): ";
		cin >> n;
	}
	
	return 0;
}

//Functions
//********************************************************************
// Function takes in array and sorts it from least to greatest
//********************************************************************
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

//********************************************************************
// Function swaps two values in the array
//********************************************************************
void swap(int& a, int&b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}

//********************************************************************
// Function takes the sorted array and determines the median
//********************************************************************
double median(int *A, int n)
{
	double Median;
	bool even;
	double tempValue, tempValue2;
	
	even = isEven(n);
		
	if (even)
	{
		tempValue = static_cast<double>(A[n/2]);
		tempValue2 = static_cast<double>(A[n/2 - 1]);
		Median = (tempValue + tempValue2) / 2;
		return Median;
	}
	else
	{
		Median = static_cast<double>(A[n/2]);
		return Median;
	}
}

//********************************************************************
// Function determines whether the number of elements in the array is
// even or not
//********************************************************************
bool isEven(int a)
{
	if (a%2 == 0)
		return true;
	else
		return false;
}
