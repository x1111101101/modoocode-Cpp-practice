#include <iostream>

int main() {
	const int a = 1;
	const int& ref = a;
	int arr[3] = { 1, };
	int* p = arr;
	int* (&arr_ref) = p;
	void* rp = &arr_ref;
	std::cout << "ARR: " << arr << " p: " << p << " arr_ref: " << arr_ref << " rp: " << rp << std::endl;
}
