#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <map>
#include <string_view>
#define SIZE 5
using namespace std;

void MergeSortedIntervals(vector<int>& v, int s, int m, int e) {


	vector<int> temp;

	int i, j;
	i = s;
	j = m + 1;

	while (i <= m && j <= e) {

		if (v[i] <= v[j]) {
			temp.push_back(v[i]);
			++i;
		}
		else {
			temp.push_back(v[j]);
			++j;
		}

	}

	while (i <= m) {
		temp.push_back(v[i]);
		++i;
	}

	while (j <= e) {
		temp.push_back(v[j]);
		++j;
	}

	for (int i = s; i <= e; ++i)
		v[i] = temp[i - s];

}

void MergeSort(vector<int>& v, int s, int e) {
	if (s < e) {
		int m = (s + e) / 2;
		MergeSort(v, s, m);
		MergeSort(v, m + 1, e);
		MergeSortedIntervals(v, s, m, e);
	}
}

void print_map(std::string_view comment, const std::map<int, std::vector<int>>& m){
    std::cout << comment;
    // Iterate using C++17 facilities
    for (const auto& [key, value] : m)
	{
        std::cout << '[' << key << ']';
			for(int i: value){
				cout << i << " ";
			}
			cout << "\n";
	}


// C++11 alternative:
//  for (const auto& n : m)
//      std::cout << n.first << " = " << n.second << "; ";
//
// C++98 alternative:
//  for (std::map<std::string, int>::const_iterator it = m.begin(); it != m.end(); ++it)
//      std::cout << it->first << " = " << it->second << "; ";

    std::cout << '\n';
}

int getMax(std::vector<int> arr, int n)
{
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

void countSort(std::vector<int>& arr, int n, int exp)
{


    int output[n];
    int i, count[10] = { 0 };

    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;


    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

		// Build the output array
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixsort(std::vector<int>& arr, int n)
	{

    int m = getMax(arr, n);

    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

int main(){
	srand(time(nullptr));
	int a[SIZE][SIZE];

	for(int i = 0;i<SIZE;i++){
			for(int j = 0;j<SIZE;j++){
				a[i][j] = rand()%100;
				cout << a[i][j] << "\t";
			}
		cout << "\n";
	}
	cout << "++++++++++++++++++++++++++++++++++++++\n";
	bool un = false;
	int tmp[SIZE];
	std::map<int,std::vector<int>> test;

	for(int i = 0;i<SIZE;i++){
			for(int j = 0;j<SIZE;j++){
				if(i == j){
					un = true;
				}
				if(!un){
					std::vector<int> vec = test[j];
					vec.push_back(a[i][j]);
					test[j] = vec;
					cout << a[i][j] << "\t";
				}else{
					cout << " \t";
				}
			}
			cout << "\n";
			un = false;
	}
	cout << "+++++++++++++++++++++++++++++++++\n";
	print_map("",test);

	for(int i = 0;i<SIZE-1;i++){

			MergeSort(test[i],0,test[i].size()-1);
			//radixsort(test[i],test[i].size());
	}
	cout << "+++++++++++++++++++++++++++++++++\n";


	print_map("",test);
	return 0;
}
