#pragma once

#include <iostream>
#include <string>
using namespace std;


template <typename processor>
class shell {
	string buf;

	


	void run() {
		cout << ">> ";
		cin >> buf;
		cout << '\n'l
		getline(cin, buf);
		processor(buf);
		
	}
};