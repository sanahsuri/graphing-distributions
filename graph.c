/***********************************************************************
 * Homework: Pointers, Functions and Arrays
 ***********************************************************************/

/* Program that takes squares of random values in [0,1.0], discretizes them and graphs their distribution
in a histogram and a cumulative distribution */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include <assert.h>
#define BINS 10 //defining a macro used for array sizes


//function declarations
void randFunc(double *arr0);
void binDistribute(double *arr1, int *arr2);
void scalingFunc(int *arr3);
void makeCumulative(int *arr4, int *arr5);
void drawGraph(int *arr6);
void testBinDistribute(double *arr);
void testScalingFunc(int *arr);
void testCumulative(int *arr);
void testDrawGraph(int *arr);

//variable declarations
const unsigned int SAMPLE_SIZE=1000;
const unsigned int WIDTH=0;
double randomArray[SAMPLE_SIZE];
int countArray[BINS];
int cumulativeArray[BINS];

int
main (void)
{

  //making calls to functions
    printf("Histogram of uniformly distributed values squared:\n");
    randFunc(randomArray);
    binDistribute(randomArray, countArray);
    testBinDistribute(randomArray);
    drawGraph(countArray);
    testDrawGraph(countArray);
    printf("\n");
    printf("Cumulative distribution of squared values:\n");
    makeCumulative(countArray, cumulativeArray);
    testCumulative(cumulativeArray);
    drawGraph(cumulativeArray);
    testDrawGraph(cumulativeArray);
  return 0;
}

/* Creates an array of size SAMPLE_SIZE with random values ranging from 0 to 1.0
 *
 *  pre-conditions: none
 *
 *  post-conditions: in resulting array each element will lie between 0 and 1, inclusive
 *
 */
void
randFunc(double *arr0)
{
  int i;
  srand(time(NULL));
  for (i=0; i<SAMPLE_SIZE; i++)
  {
    arr0[i] = pow((rand()%100)/100.0, 2);
  }
}//randFunc

/* Discretizes values from an array into bins between 0 and 1.0 by
creating an array of size BINS with each index representing number of
values in that range
*
*  pre-conditions: elements in arr1 must lie between 0 and 1.0
*  post-conditions: resulting array will be of length BINS with each element having a value
*  such that 0<=value<=SAMPLE_SIZE
*
*/
void
binDistribute(double *arr1, int *arr2)
{
  const double size_bin = 1.0/BINS;
  double min = 0;
  double max = min + size_bin;

  for (int i=0; i<BINS; i++)
  {
    for (int j=0; j<SAMPLE_SIZE; j++)
    {
      if (arr1[j]>=min && arr1[j]<max)
        arr2[i]++;
    }
    min+=size_bin;
    max=min+size_bin;
  }
}//binDistribute

/* Function that tests and asserts the pre-conditions of binDistribute */
void
testBinDistribute(double *arr)
{
  for (int i =0; i < SAMPLE_SIZE; i++)
  {
    assert (arr[i]<=1);
    assert (arr[i]>=0);
  }
}//testBinDistribute

/* Builds a new array from the array returned by binDistribute with
values cumilating at each index
*
*  pre-conditions: length of arr4 = BINS
*
*  post-conditions: element in array, arr5[i+1]>arr5[i]
*                   largest element in array = arr5[BINS-1]
*/
void
makeCumulative(int *arr4, int *arr5)
{
  arr5[0]=arr4[0];
  for (int i=0; i<BINS; i++)
  {
    arr5[i+1]=arr4[i+1]+arr5[i];
  }
}//makeCumulative

/* Tests and asserts the pre-conditions for makeCumulative */
void
testCumulative(int *arr)
{
  int counter=0;
  for (int i=0; i<BINS; i++)
  {
    counter++;
  }
  assert(counter==BINS);
  for (int j=0; j<BINS; j++)
  {
    assert(arr[j+1]>=arr[j]);
  }
  int maximum = 0;
  for (int k=0; k<BINS; k++)
  {
    if (arr[k]>maximum)
      maximum = arr[k];
  }
  assert(maximum == arr[BINS-1]);
}//testCumulative

/* Scales the elements of the array for proper display on terminal window
*  and in accordance with WIDTH
*  Prints a histogram for values in each index of the scaled array
*
*  pre-conditions: length of arr6=BINS
*
*  post-conditions: largest element in array = WIDTH
*
*/
void
drawGraph(int *arr6)
{
  double size_bin = 1.0/BINS;
  double min = 0;
  double max = min + size_bin;

 //calculates max value in array
  double maxArray = 0;
  for (int i=0; i<BINS; i++)
  {
    if (arr6[i]>maxArray)
      maxArray=arr6[i];
  }

  for (int j=0; j<BINS; j++)
  {
    arr6[j]=arr6[j] /maxArray*WIDTH;
  }
  printf("Largest frequency = %d\n",WIDTH);
  printf("Size of each range = %0.2lf\n",size_bin);
  printf("Number of ranges = %d\n", BINS);
  printf("   Range\tFrequency\n");
  for (int i=0; i<BINS; i++)
  {
    printf("%0.2lf - %0.2lf: ", min, max);
    min+=size_bin;
    max=min+size_bin;
    for (int j=0; j<arr6[i]; j++)
    {
      printf("*");
    }
    printf("\n");
  }
}//drawGraph

/* Tests and asserts the pre-conditions for testDrawGraph */
void
testDrawGraph(int *arr)
{
  int counter=0;
  for (int i=0; i<BINS; i++)
  {
    counter++;
  }
  assert(counter==BINS);
  int maximum = 0;
  for (int k=0; k<BINS; k++)
  {
    if (arr[k]>maximum)
      maximum = arr[k];
  }
  assert(maximum == WIDTH);
}//testDrawGraph

/* Summary Statement: Given an array of random numbers between 0 and 1.0, the code successfully prints
two different types (histogram and cumulative) distributions with all pre-conditions for functions asserted */
