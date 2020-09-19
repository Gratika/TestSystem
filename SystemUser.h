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
	virtual string showMenu() { return ""; }	
	virtual void editUser(SystemUser* s) {}
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
	virtual ~SystemUser() {};

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
			cout << "\n0- Выход \n1- Пройти тестирование\n2- Посмотреть результаты\n3- Продолжить тестирование\n4" << endl;
			cin >> m;
			cin.ignore();
			switch (m)
			{
			case '0':
				return "exit";
			case '1':
				return "";
			case '2':
				return "";
			case '3':
				return "";
			default:
				cout << "Ошибка ввода. Нет такого пункта меню" << endl;
				break;
			}
		} while (m < '0' || m>'4');
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
	SystemAdmin() :SystemUser() {}
	string showMenu() override {
		char m;
		do {
			system("cls");
			cout << "Пользователь " << login << "( " << getUserFio() << ")\n" << endl;
			cout << "--------------------------------------------------------\n" << endl;
			cout << "Какое действие Вы хотите выполнить?" << endl;
			cout << "\n0- Выход \n1- Создать новую категорию\n2- Создать новый тест\n3- Просмотреть тест\n4- Изменить данные пользователя" << endl;
			cout << "5- Зарегистрировать нового пользователя\n6- Удалить пользователя \n7- Просмотреть структуру\n8- Просмотреть пользователей" << endl;

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
				return"showStructure";
			case '8':
				return"showAllUser";
			default:
				cout << "Ошибка ввода. Нет такого пункта меню" << endl;
				break;
			}
		} while (m < '0' || m > '6');
	}	

	void editUser(SystemUser* s) override {
		system("cls");
		cout << "Редактирование пользователя " << s->getLogin() << endl;
		s->print();
		cout << "----------------------------------------\n";
		char rpt = 'н', ch;
		do {
			string st, login, password, name, lname, sname, address, phone;
			cout << "Что будем менять?" << endl;
			cout << "1- Фамилию;\n2- Имя;\n3- Отчество;\n4- Домашний адрес;\n5- Телефон;\n6- Логин;\n7- Все\n0- Выход\n";
			cin >> ch; cin.ignore(2, '\n');
			switch (ch)
			{
			case '1':
				cout << "Укажите новую фамилию: ";
				getline(cin, st);
				s->setSurname(st);
				break;
			case '2':
				cout << "Укажите новое имя: ";
				getline(cin, st);
				s->setName(st);
				break;
			case '3':
				cout << "Укажите новое отчество: ";
				getline(cin, st);
				s->setLastName(st);
				break;
			case '4':
				cout << "Укажите новый домашний адрес: ";
				getline(cin, st);
				s->setAddress(st);
				break;
			case '5':
				cout << "Укажите новый телефон: ";
				getline(cin, st);
				s->setPhone(st);
				break;
			case '6':
				cout << "Укажите новый логин: ";
				st = this->getLogin();
				s->setLogin(st);
				break;
			case '7':
				cout << "Укажите новую фамилию: ";
				getline(cin, st);
				s->setSurname(st);
				cout << "Укажите новое имя: ";
				getline(cin, st);
				s->setName(st);
				cout << "Укажите новое отчество: ";
				getline(cin, st);
				s->setLastName(st);
				cout << "Укажите новый домашний адрес: ";
				getline(cin, st);
				s->setAddress(st);
				cout << "Укажите новый телефон: ";
				getline(cin, st);
				s->setPhone(st);
				cout << "Укажите новый логин: ";
				st = this->getLogin();
				s->setLogin(st);
			case '0':
				return;
			default:
				cout << "Ошибка! Нет такого пункта меню" << endl;
				break;
				break;
			}
			cout << "Хотите изменить данные другого пользователя?(д/н): ";
			cin >> rpt; cin.ignore(2, '\n');
		} while (rpt == 'д');


	}
};