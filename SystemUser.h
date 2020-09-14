#pragma once
#include <iostream>
#include<string>
#include<Windows.h>
using namespace std;
class SystemUser {
protected:
	string login;
	string role;
	string sname;
	string name;
	string lname;	
	string address;
	string phone;
public:
	SystemUser(){}
	void setParam(string login,	string role,string sname, string name, string lname,string address,	string phone) {
		this->login = login;
		this->role = role;
		this->sname = sname;
		this->name = name;
		this->lname = lname;
		this->address = address;
		this->phone = phone;
	}
	virtual void showMenu(){
		system("cls");
		cout << "������������ " << login << "( " << getUserFio() << ")\n" << endl;
		cout << "����� �������� �� ������ ���������?" << endl;
	}
	virtual ~SystemUser(){};
private:
	string getUserFio(){
		return sname + " " + name[0] + ". " + lname[0] + ".";
	}
};

class SystemStudend :public SystemUser {
public:
	SystemStudend():SystemUser(){}
	void showMenu() {
		do {
		SystemUser::showMenu();
			char m;
			cout << "\n0- ��������� � ������� ���� \n1- ������ ������������\n2- ���������� ����������\n3- ���������� ������������\n4" << endl;
			cin >> m;
			cin.ignore();
			switch (m)
			{
			case '0':
				return;
			case '1':
				break;
			case '2': break;
			case '3':
				break;
			default:
				cout << "������ �����. ��� ������ ������ ����" << endl;
				break;
			}
		} while (true);	    
	}
	void getResult() {
		//������� ���� � ��������� = �����
		//������� ������ (����� ResultTest-??)
		//���������� �� �����
	}
	void doTesting() {
		//�������� ������ ������
		//��������� ���� �� �����
	}
	void saveResult() {

	}
};

class SystemAdmin : public SystemUser {
public:
	SystemAdmin():SystemUser(){}
	void createTest(){}
	void createCategory(){}

};