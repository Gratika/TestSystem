#pragma once
#include <iostream>
#include<string>
#include<Windows.h>
#include"ErrorTS.h"
#include"IElementTS.h"

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
	SystemUser() {}
	virtual void setParam(string login, string role, string sname, string name, string lname, string address, string phone) {
		this->login = login;
		this->role = role;
		this->sname = sname;
		this->name = name;
		this->lname = lname;
		this->address = address;
		this->phone = phone;
	}
	void print() {
		cout << sname<<" "<<name<<" "<<lname<< " login: " << login << " address: " << address << " phone: " << phone << endl;
	}
	virtual string showMenu() = 0;
	string getLogin() { return this->login; }
	string getRole() { return this->role; }
	string getSurname() { return this->sname; }
	string getName() { return this->name; }
	string getLastName() { return this->lname; }
	string getAddress() { return this->address; }
	string getPhone() { return this->phone; }

	void setLogin(string login) { this->login = login; }
	void setRole(string role) { this->role = role; }
	void setSurname(string sname) { this->sname = sname; }
	void setName(string name) { this->name = name; }
	void setLastName(string lname) { this->lname = lname; }
	void setAddress(string address) { this->address = address; }
	void setPhone(string phone) { this->phone = phone; }
	virtual ~SystemUser()=0 {};

protected:	
	string getUserFio() {
		return sname + " " + name[0] + ". " + lname[0] + ".";
	}
};

class SystemStudend :public SystemUser {
public:
	SystemStudend() :SystemUser() {}
	string showMenu() override {
		char m;
		do {
			system("cls");
			cout << "Пользователь " << login << "( " << getUserFio() << ")\n" << endl;
			cout << "--------------------------------------------------------\n" << endl;
			cout << "Какое действие Вы хотите выполнить?" << endl;
			cout << "\n0- Выход \n1- Пройти тестирование\n2- Посмотреть статистику\n" << endl;
			cin >> m;
			cin.ignore();
			switch (m)
			{
			case '0':
				return "exit";
			case '1':
				return "beginTesting";
			case '2':
				return "userGetStatistics";			
			default:
				cout << "Ошибка ввода. Нет такого пункта меню" << endl;
				break;
			}
		} while (m < '0' || m>'3');
	}	
};

class SystemAdmin : public SystemUser {

public:
	SystemAdmin() :SystemUser() {}
	string showMenu() override {
		char m;
		do {
			system("cls");
			cout << "Пользователь " << login << "( " << getUserFio() << ")\n" << endl;
			cout << "--------------------------------------------------------\n" << endl;
			cout << "Какое действие Вы хотите выполнить?" << endl;
			cout << "\n0- Выход \n1- Создать новую категорию\n2- Создать новый тест\n3- Просмотреть тест\n4- Изменить данные пользователя" << endl;
			cout << "5- Зарегистрировать нового пользователя\n6- Удалить пользователя \n7- Просмотреть статистику\n8- Просмотреть пользователей" << endl;

			cin >> m;
			cin.ignore();
			switch (m)
			{
			case '0':
				return "exit";
			case '1':
				return "createCategory";
			case '2':
				return "createTest";
			case '3':
				return "showTest";
			case '4':
				return"adminEditUser";
			case '5':
				return"adminCreateUser";
			case '6':
				return"adminDeleteUser";
			case '7':
				return "adminGetStatistics";
			case '8':
				return"showAllUser";
			default:
				cout << "Ошибка ввода. Нет такого пункта меню" << endl;
				break;
			}
		} while (m < '0' || m > '6');
	}		
};