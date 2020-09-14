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
		cout << "Пользователь " << login << "( " << getUserFio() << ")\n" << endl;
		cout << "Какое действие Вы хотите выполнить?" << endl;
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
			cout << "\n0- Вернуться в главное меню \n1- Пройти тестирование\n2- Посмотреть результаты\n3- Продолжить тестирование\n4" << endl;
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
				cout << "Ошибка ввода. Нет такого пункта меню" << endl;
				break;
			}
		} while (true);	    
	}
	void getResult() {
		//открыть файл с названием = логин
		//считать данные (класс ResultTest-??)
		//отобразить на экран
	}
	void doTesting() {
		//показать дерево тестов
		//загрузить тест из файла
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