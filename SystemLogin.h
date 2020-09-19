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

class SystemLoginTS {
	map<string, long>pass;
	vector <SystemUser*> users;
	SystemUser* suser = nullptr;
	ObjectFactory<SystemUser>* ufactory = nullptr;

public:
	SystemLoginTS() {
		loadPasswordFromFile();		
		ufactory = new ObjectFactory<SystemUser>();
		ufactory->add("SystemStudend", new ObjectCreator< SystemStudend, SystemUser>);
		ufactory->add("SystemAdmin", new ObjectCreator<SystemAdmin, SystemUser>);
		loadUsersFromFile();
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
	string showMainMenu() {
		showName();
		if (!userExist("admin")) this->createAdmin();
		system("cls");
		char t;
		do {
			cout << "������� ���� �������" << endl;
			cout << "---------------------\n" << endl;
			cout << "�������� ��������:\n1 - �����\n2 - ������������������\n0 - �����" << endl;
			cin >> t;
			cin.ignore(32000, '\n');
			switch (t)
			{
			case '1':
				return "userLogin";
			case '2':
				return "userSingUp";
			case '0':
				return "exit";
			default:
				cout << "������! ��� ������ ������ ����" << endl;
				break;
			}
		} while (t < '0' || t > '3');

	}	

	bool userLogin() {
		system("cls");
		cout << "����������� ������������" << endl;
		cout << "-------------------------------------\n" << endl;
		string login, password;
		char p;
		login = getLogin();
		auto rec = pass.find(login);
		if (rec == pass.end())throw UserNotFindError("������������ � ����� ������� �� ��������������� � �������");
		cout << "������: ";
		password = getPassword();
		hash <string> h;
		long hpass = h(password);
		if (rec->second != hpass) throw ObjectInfoNotFound("������ �����������! ������������ ������");
		suser = this->findUser(login);
		if (suser == nullptr)
			throw ObjectInfoNotFound("���������� � ������������ �����������. ������������� ��� ��� ������ �����������");
		cout << "\n���� � ������� ��������" << endl;
		system("pause");
	}
	void registerUser(bool isAdmin) {
		system("cls");
		cout << "����������� ������ ������������" << endl;
		cout << "-------------------------------------\n" << endl;
		string login = "admin", role = "SystemAdmin", password, name, lname, sname, address, phone;
		cout << "������� �������: ";
		getline(cin, sname);
		cout << "������� ���: ";
		getline(cin, name);
		cout << "������� ��������: ";
		getline(cin, lname);
		cout << "������� �������� �����: ";
		getline(cin, address);
		cout << "������� �������: ";
		getline(cin, phone);
		if (!isAdmin) {
			role = "SystemStudend";
			bool flag = false;
			do {
				login = getLogin();
				flag = userExist(login);
				if (flag) cout << "����� �����. ��������� ����: ";
			} while (flag);
		}
		cout << "���������� ������ ��� ����� � �������: ";
		password = getPassword();
		hash<string> h;
		long hpass = h(password);
		pass[login] = hpass;
		this->savePasswordToFile();
		SystemUser* newUser = ufactory->create(role);
		newUser->setParam(login, role, sname, name, lname, address, phone);
		users.push_back(newUser);
		this->saveUsersToFile();
		cout << "\n����������� �������.\n" << endl;	
		system("pause");
	}
	string showUserMenu() {
		return suser->showMenu();
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
		for (int i = 1; i < 11; i++) {
			cout << " .";
			Sleep(1000);
		}
	}
	void loadUsersFromFile() {
		int cnt;
		string login, role, name, lname, sname, address, phone;
		ifstream inp("Users.txt");
		if (!inp.is_open()) throw FileError("Users.txt", "�� ���� �������� ���������� � �������������!");
		inp >> cnt; inp.ignore(2, '\n');
		for (int i = 0; i < cnt; i++)
		{
			getline(inp, login);
			getline(inp, role);
			getline(inp, sname);
			getline(inp, name);
			getline(inp, lname);
			getline(inp, address);
			getline(inp, phone);
			SystemUser* suser = ufactory->create(role);
			suser->setParam(login, role, sname, name, lname, address, phone);
			users.push_back(suser);
		}
		inp.close();
	}

	void saveUsersToFile() {
		ofstream out("Users.txt");
		out << users.size()<<endl;
		for (auto s : users) {
			out << s->getLogin() << endl;
			out << s->getRole() << endl;
			out << s->getSurname() << endl;
			out << s->getName() << endl;
			out << s->getLastName() << endl;
			out << s->getAddress() << endl;
			out << s->getPhone() << endl;
		}
		out.close();
	}
	void showAllUser() {
		system("cls");
		cout << "������������ �������" << endl;
		cout << "----------------------------------------\n";
		for (auto s : users)
			s->print();
		system("pause");
	}
	SystemUser* findUser(string login) {
		for (auto s : users) {
			if (s->getLogin() == login) return s;
		}
		return nullptr;
	}
	void deleteUser() {
		char rpt = '�', ch;
		do {
			system("cls");
			cout << "�������� ������������" << endl;
			cout << "----------------------------------------\n";
			string login = this->getLogin();
			bool flag = false;
			int j = 0;
			for (j < users.size(); j++ && !flag;) {
				if (users[j]->getLogin() == login) flag = true;
			}
			if (!flag) cout << "������������ �� ������" << endl;
			else users.erase(users.begin() + j);
			cout << "������ ������� ������� ������������?(�/�): ";
			cin >> rpt; cin.ignore(2, '\n');
		} while (rpt == '�');

	}

	void createAdmin() {
		system("cls");
		cout << "���������� ������� ������� ������ �������������� �������" << endl;
		system("pause");
		this->registerUser(true);
	}
	string getPassword() {
		char p;
		string st;
		do {
			p = _getch();
			if (p != 13 && p != 8) {
				st.push_back(p);
				cout << '*';
			}
		} while (p != 13);
		return st;
	}
	string getLogin() {
		cout << "������� ����� ������������: ";
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


	ObjectFactory<SystemUser>* getUserFactory() { return this->ufactory; }
	SystemUser* getSystemUser() { return this->suser; }

	~SystemLoginTS() {
		this->savePasswordToFile();
		this->saveUsersToFile();
		if (suser != nullptr) delete suser;
		if (ufactory != nullptr) delete ufactory;
		pass.clear();
	}
};

