//********************************************************************
// Course: CPSC2620 Fall 2013
// Name: Josh Tymburski
// Assignment #1
// Problem #3
// Professor: Howard Cheng
// Program: filter.cc
// Purpose: This program reads an image file in PGM format and applies
//          three different filters to the image.  The result of each
//          filter is written into a separate image.
// Programming Partner: Anthony Tymburski
//********************************************************************

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// allocates an m x n two-dimensional array of integers
int **allocate(int m, int n);

// deallocates a two-dimensional array of integers with m rows
void deallocate(int **A, int m);

// reads a PGM image from the given file name and return the dimensions
// and the image in a two dimensional array.  No error checking is done
// to see whether the image file is valid (other than whether it can
// be opened for reading).
bool read_image(const char *filename, int &m, int &n, int **&img);

// writes a PGM image to the given file name and suffix
bool write_image(const char *filename, int m, int n, int **img,
		 const char *suffix);

// process the image with the appropriate filter
void process(int **img, int m, int n, int **output, 
	     int (*filter)(int A[5][5]));

// computes the average (rounded to the nearest integer) of the array
int average(int A[5][5]);

// computes the median of the array
int median(int A[5][5]);

// computes the strange function as given in the assignment
int strange(int A[5][5]);

int main(int argc, char *argv[])
{
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " file.pgm" << endl;
    return 1;
  }

  int m, n, **img;
  if (!read_image(argv[1], m, n, img)) {
    cerr << "Cannot open " << argv[1] << " for reading." << endl;
    return 2;
  }

  int **output = allocate(m, n);

  cout << "Applying average filter." << endl;
  
  // Implemented function call to process
  process(img, m, n, output, average);
  
  if (!write_image(argv[1], m, n, output, ".avg")) {
    cerr << "Cannot write result." << endl;
    return 3;
  }
  
  cout << "Applying median filter." << endl;
  
  // Implemented function call to process
  process(img, m, n, output, median);
  
  if (!write_image(argv[1], m, n, output, ".med")) {
    cerr << "Cannot write result." << endl;
    return 3;
  }

  cout << "Applying strange filter." << endl;
  
  // Implemented function call to process
  process(img, m, n, output, strange);
  
  if (!write_image(argv[1], m, n, output, ".str")) {
    cerr << "Cannot write result." << endl;
    return 3;
  }
  
  deallocate(img, m);
  deallocate(output, m);

  return 0;
}

// allocates an m x n two-dimensional array of integers
int **allocate(int m, int n)
{
  int **A;
  A = new int *[m];
  for (int i = 0; i < n; i++)
  {
	  A[i] = new int[n];
  }
  
  return A;
}

// deallocates a two-dimensional array of integers with m rows
void deallocate(int **A, int m)
{
  for (int i = 0; i < m; i++)
  {
	  delete[] A[i];
  }
  delete[] A;
}

// reads a PGM image from the given file name and return the dimensions
// and the image in a two dimensional array.  No error checking is done
// to see whether the image file is valid (other than whether it can
// be opened for reading).
bool read_image(const char *filename, int &m, int &n, int **&img)
{
  ifstream is(filename, ios::binary);
  if (!is) {
    return false;
  }

  string s;

  is >> s;
  is >> n >> m >> s;
  is.ignore(1024, '\n');
  img = allocate(m, n);

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      img[i][j] = is.get();
    }
  }
  return true;
}

// writes a PGM image to the given file name and suffix
bool write_image(const char *filename, int m, int n, int **img,
		 const char *suffix)
{
  string s = filename;
  s += suffix;

  ofstream os(s.c_str(), ios::binary);
  if (!os) {
    return false;
  }
  os << "P5" << endl;
  os << n << " " << m << endl;
  os << 255 << endl;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      os.put(static_cast<unsigned char>(img[i][j]));
    }
  }
  return os;
}

// process the image with the appropriate filter
void process(int **img, int m, int n, int **output, 
	     int (*filter)(int A[5][5]))
{
  int A[5][5];

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (i < 2 || i >= m-2 || j < 2 || j >= n-2) {
	output[i][j] = 0;
      } else {
	for (int k = 0; k < 5; k++) {
	  for (int l = 0; l < 5; l++) {
	    A[k][l] = img[i-2+k][j-2+l];
	    output[i][j] = filter(A);
	  }
	}
      }
    }
  }
}

// computes the average (rounded to the nearest integer) of the array
int average(int A[5][5])
{
  double accurateAverage = 0;
  int totalSum = 0;
  double divisor = 1;
  int roundedAverage;
  
  
  for (int i = 0; i < 5; i++)
  {
	  for (int j = 0; j < 5; j++)
	  {
		  totalSum = totalSum + A[i][j];
		  divisor++;
	  }
  }
  
  accurateAverage = totalSum / divisor;
  
  roundedAverage = accurateAverage + 0.5;
  
  return roundedAverage;
}

// computes the median of the array
int median(int A[5][5])
{
	int *temp;
	bool switched = true;
	int currentPos = 0;
	int tempInt;
	int median;
	
	temp = new int[25];
	
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			temp[currentPos] = A[i][j];
			currentPos++;
		}
	}
	
	while (switched)
	{
		switched = false;
		for (int i = 0; i < 25; i++)
		{
			if (temp[i+1] < temp[i])
			{
				switched = true;
				tempInt = temp[i+1];
				temp[i+1] = temp[i];
				temp[i] = tempInt;
				
			}
		}
	}
	
	median = temp[12];
	
	delete[] temp;
	temp = NULL;
	
	return median;
}

// computes the strange function as given in the assignment
int strange(int A[5][5])
{
  double currentValue;
  int strangeValue;
  
  currentValue = ((255.0/2040) * (-A[1][1] - 2 * A[2][1] - A[3][1] +
				  A[1][3] + 2 * A[2][3] + A[3][3] + 1020));
  
  strangeValue = currentValue + 0.5;
  
  return strangeValue;
}
