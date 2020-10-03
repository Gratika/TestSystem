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
		cout <<'\n'<< sname << " " << name << " " << lname << endl;
		cout << setw(11) << "login: " << login << endl;
		cout << setw(11) << "address: " << address << endl;
		cout<<setw(11)<<"phone: " << phone << endl;
		cout << "\n-------------------------------------------------------------------------------------------" << endl;
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
			cout << "\n0- Выход \n1- Просмотреть структуру\n2- Пройти тестирование\n3- Посмотреть статистику\n" << endl;
			cin >> m;
			cin.ignore();
			switch (m)
			{
			case '0':
				return "exit";
			case '1':
				return "showStructure";
			case '2':
				return "beginTesting";
			case '3':
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
			cout << "\n0- Выход \n1- Просмотреть структуру\n2- Создать новую категорию\n3- Создать новый тест\n4- Просмотреть тест\n5- Изменить данные пользователя" << endl;
			cout << "6- Зарегистрировать нового пользователя\n7- Удалить пользователя \n8- Просмотреть статистику\n9- Просмотреть пользователей" << endl;

			cin >> m;
			cin.ignore();
			switch (m)
			{
			case '0':
				return "exit";
			case '1':
				return "showStructure";
			case '2':
				return "createCategory";
			case '3':
				return "createTest";
			case '4':
				return "showTest";
			case '5':
				return"adminEditUser";
			case '6':
				return"adminCreateUser";
			case '7':
				return"adminDeleteUser";
			case '8':
				return "adminGetStatistics";
			case '9':
				return"showAllUser";
			default:
				cout << "Ошибка ввода. Нет такого пункта меню" << endl;
				break;
			}
		} while (m < '0' || m > '6');
	}		
};