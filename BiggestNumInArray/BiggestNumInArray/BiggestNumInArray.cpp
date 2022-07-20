// BiggestNumInArray.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

void PopulateArray(int arr[], int size);
int GetLargest(int arr[], int size);

int main()
{
    const int size = 5;
    int arr[size];
    PopulateArray(arr, size);
    int largest = GetLargest(arr, size);

    std::cout << "The largest element in the array is " << largest << std::endl;
}

void PopulateArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cin >> arr[i];
    }
}

int GetLargest(int arr[], int size)
{
    int largest = arr[0];

    for (int i = 1; i < size; i++)
    {
        if (arr[i] > largest)
        {
            largest = arr[i];
        }
    }
    return largest;
}