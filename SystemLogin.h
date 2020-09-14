#pragma once
#include <fstream>
#include <iostream>
#include<string>
//#include<Windows.h>
#include<conio.h>
#include <map>
#include <ctype.h>
#include"SystemUser.h"
#include "ObjectFactory.h"
#include"ErrorTS.h"
using namespace std;

class SystemLogin {
	map<string, long>pass;
	ObjectFactory<SystemUser> *ufactory =nullptr;
	
public:
	SystemLogin(){
		loadPasswordFromFile();
		ufactory = new ObjectFactory<SystemUser>();
		ufactory->add("SystemStudend", new ObjectCreator< SystemStudend, SystemUser>);
		ufactory->add("SystemAdmin", new ObjectCreator<SystemAdmin, SystemUser>);
	}
	void loadPasswordFromFile() {
		ifstream inp("Login.txt");
		if (inp.is_open()) {
			string l; long p;
			while (!inp.eof()) {
				inp >> l >> p;				
				pass[l] = p;
			}			
			inp.close();
		}
	}
	void savePasswordToFile() {
		ofstream out("Login.txt");
		for (auto i : pass)
			out << i.first << " " << i.second << endl;
		out.close();
	}
	void showMainMenu() {
		showName();	
		if (!userExist("admin")) this->createAdmin();
		do {
			system("cls");
			char t;
			cout <<"Главное меню системы"<< endl;
			cout <<"---------------------\n"<< endl;
			cout << "Выберите действие:\n1 - ВОЙТИ\n2 - ЗАРЕГИСТРИРОВАТЬСЯ\n0 - ВЫХОД" << endl;
			cin >> t;
			cin.ignore(32000, '\n');
			switch (t)
			{
			case '1':
				try {
					this->userLogin();
				}
				catch (ErrorTS err) {
					err.getError();
				}				
				
				break;
			case '2':
				this->registerUser(false);
				break;
			case '0':
				return;
			default:
				cout << "Ошибка! Нет такого пункта меню" << endl;
				break;
			}			
		} while (true);

	}
	void userLogin(){
		system("cls");
		cout << "Авторизация пользователя" << endl;
		cout << "-------------------------------------\n" << endl;
		string login, password;	
		char p;
		cout << "Логин: ";
		login = getLogin();		
		auto rec = pass.find(login);
		if (rec != pass.end()) {
			cout << "Пароль: ";
			password = getPassword();
			hash <string> h;
			long hpass = h(password);
			if (rec->second == hpass) {//ок, вход в систему, создать пользователя, показать его меню
				this->createSystemUser(login);
			}
			else cout << "Ошибка авторизации! Неправильный пароль" << endl;
		}
		else cout << "Пользователь с таким логином не зарегистрирован в системе" << endl;
		system("pause");
	}
	void registerUser(bool isAdmin) {
		system("cls");
		cout << "Регистрация нового пользователя" << endl;
		cout << "-------------------------------------\n" << endl;
		string login = "admin",role = "SystemAdmin", password,name, lname, sname, address, phone;		
		cout << "Ваша фамилия: ";
		getline(cin, sname);
		cout << "Ваше имя: ";
		getline(cin, name);
		cout << "Ваше отчество: ";
		getline(cin, lname);
		cout << "Домашний адрес: ";
		getline(cin, address);
		cout << "Телефон: ";
		getline(cin, phone);
		if (!isAdmin) {
			role = "SystemStudend";
			bool flag=false;
			cout << "Придумайте логин: ";
			do {				
				login= getLogin();
				flag = userExist(login);
				if (flag) cout << "Логин занят. Повторите ввод: ";
			} while (flag);			
		}
		cout << "Придумайте пароль для входа в систему: ";
		password = getPassword();
		hash<string> h;
		long hpass = h(password);
		pass[login] = hpass;
		savePasswordToFile();
		saveNewUser(login,role, sname, name, lname, address, phone);
		cout << "\nРегистрация успешна. Выполните вход в систему, чтобы начать работу\n" << endl;
		system("pause");


	}
	void showName() {
		cout << "TESTING SYSTEM:" << endl;
		cout << endl;
		cout << "KK   KK  NN     NN    OOOO   WWW        WWWWWW        WWW LL       EEEEEEEEE DDDDDD      GGGGGG    EEEEEEEEE" << endl;
		cout << "KK  KK   NNN    NN  OO    OO  WW         WWWW         WW  LL       EE        DD    DD  GG      GG  EE       " << endl;
		cout << "KK KK    NNNN   NN OO      OO  WW       WW  WW       WW   LL       EE        DD     DD GG       GG EE       " << endl;
		cout << "KKKK     NN NN  NN OO      OO   WW     WW    WW     WW    LL       EEEEEEE   DD     DD GG          EEEEEEE  " << endl;
		cout << "KK KK    NN  NN NN OO      OO    WW   WW      WW   WW     LL       EE        DD     DD GG          EE       " << endl;
		cout << "KK  KK   NN   NNNN OO      OO     WW WW        WW WW      LL       EE        DD     DD GG    GGGG  EE       " << endl;
		cout << "KK   KK  NN    NNN  OO    OO       WWW          WWW       LL       EE        DDD   DD  GG      GG  EE       " << endl;
		cout << "KK    KK NN     NN    OOOO         WWW          WWW       LLLLLLLL EEEEEEEEE DDDDDD      GGGGGG    EEEEEEEEE" << endl;
		cout << endl;
		for (int i = 1; i <11; i++) {
			cout << " .";
			Sleep(1000);
		}
	}
private:
	void createAdmin() {
		system("cls");
		cout << "Необходимо создать учетную запись администратора системы" << endl;
		system("pause");
		this->registerUser(true);
	}
	string getPassword() {
		char p;
		string st;
		do {
			p = _getch();
			if (p != 13) {
				st.push_back(p);
				cout << '*';
			}
		} while (p != 13);
		return st;
	}
	string getLogin() {
		string lgn;
		getline(cin, lgn);
		for (int i = 0; i < lgn.size(); i++)
			lgn[i] = tolower(lgn[i]);
		return lgn;
	}

	bool userExist(string login) {
		auto rec = pass.find(login);
		if (rec != pass.end()) return true;
		else return false;
	}
	void saveNewUser(string login, string role, string surname, string name, string lastname, string address, string phone) {
		ofstream out("Users.txt", ios::app);
		out << login << endl;
		out << role << endl;
		out << surname << endl;
		out << name << endl;
		out << lastname << endl;
		out << address << endl;
		out << phone << endl;
		out.close();
	}
	void createSystemUser(string ulogin) {
		string login, role, name, lname, sname, address, phone;
		ifstream inp("Users.txt");
		if (!inp.is_open()) throw FileError("Users.txt", "Не могу получить информацию о пользователе!");
		do {
			getline(inp, login);
			getline(inp, role);
			getline(inp, sname);
			getline(inp, name);
			getline(inp, lname);
			getline(inp, address);
			getline(inp, phone);
		} while (login != ulogin && !inp.eof());
		if (login != ulogin) throw ObjectInfoNotFound("Информация о пользователе отсутствует. Рекомендуется повторно зарегистрироваться");
		SystemUser* suser = ufactory->create(role);
		suser->setParam(login, role, sname, name, lname, address, phone);
		suser->showMenu();
	}
};