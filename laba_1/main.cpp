#include <iostream>
#include <time.h>
#include <stdlib.h>
//#include <>
#include <fstream>

#define SIZE_OF_ARRAY 6

using namespace std;

int partition(double arr[], int start, int end)
{

    int pivot = arr[start];

    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (arr[i] <= pivot)
            count++;
    }

    // Giving pivot element its correct position
    int pivotIndex = start + count;
    swap(arr[pivotIndex], arr[start]);

    // Sorting left and right parts of the pivot element
    int i = start, j = end;

    while (i < pivotIndex && j > pivotIndex) {

        while (arr[i] <= pivot) {
            i++;
        }

        while (arr[j] > pivot) {
            j--;
        }

        if (i < pivotIndex && j > pivotIndex) {
            swap(arr[i++], arr[j--]);
        }
    }

    return pivotIndex;
}

void quickSort(double arr[], int start, int end)
{

    // base case
    if (start >= end)
        return;

    // partitioning the array
    int p = partition(arr, start, end);

    // Sorting the left part
    quickSort(arr, start, p - 1);

    // Sorting the right part
    quickSort(arr, p + 1, end);
}

int shellSort(double arr[], int n)
{
 int countOfSwaps = 0;
    // Start with a big gap, then reduce the gap
    for (int gap = n/2; gap > 0; gap /= 2)
    {
        // Do a gapped insertion sort for this gap size.
        // The first gap elements a[0..gap-1] are already in gapped order
        // keep adding one more element until the entire array is
        // gap sorted
        for (int i = gap; i < n; i += 1)
        {
            // add a[i] to the elements that have been gap sorted
            // save a[i] in temp and make a hole at position i
            int temp = arr[i];

            // shift earlier gap-sorted elements up until the correct
            // location for a[i] is found
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap){
                arr[j] = arr[j - gap];
                countOfSwaps++;
            }


            //  put temp (the original a[i]) in its correct location
            arr[j] = temp;
        }
    }

    return countOfSwaps;
}

void fillArrayWithRandN(double arr[SIZE_OF_ARRAY][SIZE_OF_ARRAY]){
	for(int i = 0; i < SIZE_OF_ARRAY; i++){
		for(int i2 = 0 ;i2 < SIZE_OF_ARRAY; i2++){
				arr[i][i2] = rand() % 100 / 3;
		}
	}
}

void printArray(double arr[SIZE_OF_ARRAY][SIZE_OF_ARRAY])
{
    for (int i=0; i<SIZE_OF_ARRAY; i++){
			for (int i2=0; i2<SIZE_OF_ARRAY; i2++){
						cout << arr[i][i2] << "\t";
			}
			cout << endl;
    }
		cout << endl;
}

void saveToFile(double arr[SIZE_OF_ARRAY][SIZE_OF_ARRAY],string fileName){
	ofstream file(fileName);

	for(int i = 0;i<SIZE_OF_ARRAY;i++){
		for(int i2 = 0;i2<SIZE_OF_ARRAY;i2++){
			file << arr[i][i2] << " ";
		}
		file << endl;
	}

	file.close();

}

int main()
{
		srand(time(nullptr));

    double arr[SIZE_OF_ARRAY][SIZE_OF_ARRAY],arr2[SIZE_OF_ARRAY][SIZE_OF_ARRAY];
		fillArrayWithRandN(arr);

		saveToFile(arr,"unsorted shell.txt");

		fillArrayWithRandN(arr2);

		saveToFile(arr2,"unsorted quick.txt");

		printArray(arr);
		int countOfSwaps = 0;
		double temp[SIZE_OF_ARRAY];
		for(int i = 0;i<SIZE_OF_ARRAY;i++){
			for(int i2 = 0; i2 < SIZE_OF_ARRAY;i2++){
				temp[i2] = arr[i2][i];
			}

			countOfSwaps += shellSort(temp,SIZE_OF_ARRAY);

			for(int i2 = 0; i2 < SIZE_OF_ARRAY;i2++){
				arr[i2][i] = temp[i2];
			}

		}

		printArray(arr);
		saveToFile(arr,"sorted shell.txt");

		ofstream file1("sorted shell.txt",ios::app);

		file1 << "\ncount of swaps " << countOfSwaps;
		file1 << "\ncount of compares " << countOfSwaps << endl;

		file1.close();

		cout << "count of swaps = " << countOfSwaps<< endl;

		cout << "count of compares = " << countOfSwaps<< endl;

		printArray(arr2);

		for(int i = 0;i<SIZE_OF_ARRAY;i++){
			for(int i2 = 0; i2 < SIZE_OF_ARRAY;i2++){
				temp[i2] = arr2[i2][i];
			}
			quickSort(temp,0,SIZE_OF_ARRAY-1);

			for(int i2 = 0; i2 < SIZE_OF_ARRAY;i2++){
				arr2[i2][i] = temp[i2];
			}
		}
		printArray(arr2);
		saveToFile(arr2,"sorted quick.txt");

		ofstream file2("sorted shell.txt",ios::app);

		file2 << "\ncount of swaps " << countOfSwaps;
		file2 << "\ncount of compares " << countOfSwaps << endl;

		file2.close();

    return 0;
}
