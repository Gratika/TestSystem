#pragma once
#include<iostream>
using namespace std;

double getValue() {
	double a;
	while (true) {
		cin >> a;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "������ �����. ��������� ���� ��������� ��������" << endl;
		}
		else {
			cin.ignore(32767, '\n');
			return a;
		}
	}

}
