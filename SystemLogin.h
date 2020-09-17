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
	vector <SystemUser*> users;
	SystemUser* suser = nullptr;
	ObjectFactory<SystemUser> *ufactory =nullptr;
	
public:
	SystemLogin(){
		loadPasswordFromFile();
		loadUsersFromFile();
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
			cout <<"������� ���� �������"<< endl;
			cout <<"---------------------\n"<< endl;
			cout << "�������� ��������:\n1 - �����\n2 - ������������������\n0 - �����" << endl;
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
				cout << "������! ��� ������ ������ ����" << endl;
				break;
			}			
		} while (true);

	}
	void userLogin(){
		system("cls");
		cout << "����������� ������������" << endl;
		cout << "-------------------------------------\n" << endl;
		string login, password;	
		char p;
		cout << "�����: ";
		login = getLogin();		
		auto rec = pass.find(login);
		if (rec != pass.end()) {
			cout << "������: ";
			password = getPassword();
			hash <string> h;
			long hpass = h(password);
			if (rec->second == hpass) {//��, ���� � �������, ������� ������������, �������� ��� ����
				this->createSystemUser(login);
			}
			else cout << "������ �����������! ������������ ������" << endl;
		}
		else cout << "������������ � ����� ������� �� ��������������� � �������" << endl;
		system("pause");
	}
	void registerUser(bool isAdmin) {
		system("cls");
		cout << "����������� ������ ������������" << endl;
		cout << "-------------------------------------\n" << endl;
		string login = "admin",role = "SystemAdmin", password,name, lname, sname, address, phone;		
		cout << "���� �������: ";
		getline(cin, sname);
		cout << "���� ���: ";
		getline(cin, name);
		cout << "���� ��������: ";
		getline(cin, lname);
		cout << "�������� �����: ";
		getline(cin, address);
		cout << "�������: ";
		getline(cin, phone);
		if (!isAdmin) {
			role = "SystemStudend";
			bool flag=false;
			cout << "���������� �����: ";
			do {				
				login= getLogin();
				flag = userExist(login);
				if (flag) cout << "����� �����. ��������� ����: ";
			} while (flag);			
		}
		cout << "���������� ������ ��� ����� � �������: ";
		password = getPassword();
		hash<string> h;
		long hpass = h(password);
		pass[login] = hpass;		
		try {
			SystemUser* newUser = ufactory->create(role);
			newUser->setParam(login, role, sname, name, lname, address, phone);
			users.push_back(newUser);
			cout << "\n����������� �������. ��������� ���� � �������, ����� ������ ������\n" << endl;
		}
		catch (ObjectCreatorError err) { cout << err.getError(); }
		
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
	void loadUsersFromFile() {
		int cnt;
		string login, role, name, lname, sname, address, phone;
		ifstream inp("Users.txt");
		if (!inp.is_open()) throw FileError("Users.txt", "�� ���� �������� ���������� � �������������!");
		inp >> cnt; inp.ignore(2, '\n');
		for(int i=0; i<cnt; i++)
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
		out << users.size();
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

	SystemUser* findUser(string login) {
		for (auto s : users) {
			if (s->getLogin() == login) return s;
		}
		return nullptr;
	}
	void deleteUser(string lgn) {
		bool flag = false;
		int j = 0;
		for (j < users.size(); j++ && !flag;) {
			if (users[j]->getLogin() == lgn) flag = true;
		}
		if(!flag) cout << "������������ �� ������" << endl;
		else users.erase(users.begin()+j);
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
	
	void createSystemUser(string ulogin) {
		suser = this->findUser(ulogin);
		if (suser == nullptr)
			cout << "���������� � ������������ �����������. ������������� ��� ��� ������ �����������" << endl;
		else suser->showMenu();
	}
	ObjectFactory<SystemUser>* getUserFactory() { return this->ufactory; }
	SystemUser* getSystemUser() { return this->suser; }
	
	~SystemLogin() {
		this->savePasswordToFile();
		this->saveUsersToFile();
		if (suser != nullptr) delete suser;
		if (ufactory != nullptr) delete ufactory;
		pass.clear();
	}
};

