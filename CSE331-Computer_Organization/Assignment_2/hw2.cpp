#include <iostream>

using std::cin;
using std::cout;
using std::endl;

#define MAX_SIZE 16

int CheckSumPossibility(int num, int arr[], int size);
void print_array(int arr[], int size);

int function_call_number = 1;

int main() {
	int arraySize;
	int arr[MAX_SIZE];
	int num;
	int returnVal;
	
	cout<<"Array Size: ";
	cin >> arraySize;

	cout<<"Target Number: ";
	cin >> num;
	
	cout<<"Enter the all elements of the array: \n";
	for(int i = 0; i < arraySize; ++i){
		cout<<"Enter number: ";
		cin >> arr[i];
	}

	cout<<"The array is as follows: ";
	print_array(arr, arraySize);
	
	cout<<"The sequence giving the target number: ";
	returnVal = CheckSumPossibility(num, arr, arraySize);
	if (returnVal) cout<<endl;

	if(returnVal == 1){
		cout << "Possible!" << endl;
	}

	else{
		cout << "Not possible!" << endl;
	}
	cout<<"Number of function calls: "<<function_call_number<<endl;

	return 0;
}

void print_array(int arr[], int size){
	cout<<"The array is as follows: ";
	for(int i=0 ; i<size ; ++i){
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}

int CheckSumPossibility(int num, int arr[], int size){
	if(num == 0) return 1;

	if(num < 0 || size <= 0) return 0;

	++function_call_number;
	if(CheckSumPossibility(num-(*arr), arr+1, size-1)){
		cout << *arr << " ";
		return 1;
	}

	++function_call_number;
	return CheckSumPossibility(num, arr+1, size-1);
}
