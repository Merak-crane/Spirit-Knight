#include<iostream>
#include<string>
using namespace std;
int main() {
	string a = "hollow";
	string b = ":";
	int c = 1;
	string d = a + to_string(c) + b;
	cout << d << endl;
}