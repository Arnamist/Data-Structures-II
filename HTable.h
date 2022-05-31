#include<iostream>
#include<string>
using namespace std;

int main() {
	int x = 0;
	for (int i = 0; i < 100; i++) {
		x++;
		if (x % 3 == 0) {
			cout << "| Fizz (" << x << ") | ";
		} 
		if (x % 5 == 0) {
			cout << "| Buzz (" << x << ") | ";
		}
		if (x % 3 != 0 && x % 5 != 0) {
			cout << x;
		}
	}

	return 0;
}
