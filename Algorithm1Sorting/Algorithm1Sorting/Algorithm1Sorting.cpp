// Algorithm1Sorting.cpp : This file contains the 'main' function. Program execution begins and ends there.
// 1. Implement a sorting algorithm using the chrono library profile, sometimes using varying sample sizes

// Includes
#include <iostream>
#include <chrono>
#include <stdlib.h>

// Defines
#define ARRAY_SIZE 100

// Namespaces
using namespace std;

// Helper Functions
uint32_t GetNanos();
void FillArray(int arr[], int size);
int ChooseASearchKey(int arr[], int size);

// Sorting Algorithms
void BubbleSort(int arr[], int size);

// Search Algorithms

void LinearSearch(int arr[], int size, int SearchKey);
void BinarySearch(int arr[], int low, int high, int SearchKey);

int main()
{
    // Create array
    int arr[ARRAY_SIZE];

    // Seed random geenerator and fill the array with random numbers
    srand(time(nullptr));
    FillArray(arr, ARRAY_SIZE);

    // Pick a random number that exists in the array to search for
    const int SearchKey = ChooseASearchKey(arr, ARRAY_SIZE);

    // Perform Linear Search
    uint32_t StartNanos = GetNanos();
    LinearSearch(arr, ARRAY_SIZE, SearchKey);
    uint32_t StopNanos = GetNanos();
    cout << "Linear Search took: " << (StopNanos - StartNanos) << " ns" << endl;

    // Bubble Sort
    StartNanos = GetNanos();
    BubbleSort(arr, ARRAY_SIZE);
    StopNanos = GetNanos();
    cout << "Bubble Sort took: " << (StopNanos - StartNanos) << " ns" << endl;

    // Perform Binary Search
    StartNanos = GetNanos();
    BinarySearch(arr, 0, ARRAY_SIZE, SearchKey);
    StopNanos = GetNanos();
    cout << "Binary Search took: " << (StopNanos - StartNanos) << " ns" << endl;

    
}

uint32_t GetNanos()
{
    using namespace std::chrono;
    return static_cast<uint32_t>(duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count());
}

void FillArray(int arr[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        arr[i] = rand()%size;
    }
}

int ChooseASearchKey(int arr[], int size)
{
    return arr[rand() % size];
}


void BubbleSort(int arr[], int size)
{
    int comparisons = 0;

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size-1; j++)
        {
            ++comparisons;

            if (arr[i] > arr[j])
            {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    cout << comparisons << " comparisons were made.\n";
}

void LinearSearch(int arr[], int size, int SearchKey)
{
    int comparisons = 0;

    for (int i = 0; i < size; ++i)
    {
        ++comparisons;

        if (arr[i] == SearchKey)
        {
            cout << "Linear Search complete. Found " << SearchKey << " at index: " << i << endl;
            cout << comparisons << " comparisons were made.\n";
            break;
        }
    }
}

void BinarySearch(int arr[], int low, int high, int SearchKey)
{
    int middle = 0;
    int comparisons = 0;

    while (low < high)
    {
        ++comparisons;

        middle = (low + high) / 2;

        // If the middle element matches, search is complete
        if (SearchKey == arr[middle])
        {
            cout << "Search key " << SearchKey << " found at index: " << middle << endl;
            cout << comparisons << " comparisons were made.\n";
            break;
        }
        else if (SearchKey < arr[middle])
        {
            high = middle - 1;
        }
        else
        {
            low = middle + 1;
        }
    }
}
