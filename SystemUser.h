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
	virtual string showMenu() {}
	//virtual void createCategory(IElementTS* root_, ObjectFactory<IElementTS>* factory_) {}
	//virtual void createTest(IElementTS* root_, ObjectFactory<IElementTS>* factory_) {}
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
	/*virtual IElementTS* getCategory(IElementTS* root_) {
		IElementTS* elm = root_;
		int ch;
		do {
			cout << "0 - ������� ���������;" << endl;
			elm->show();
			ch = getValue();
			if (ch != 0)
				try { elm = elm->getElement(ch); }
			catch (OutOfRangeError err) {
				cout << "������! " << err.getError() << endl;
			}

		} while (ch != '0');
	}*/

	/*double getValue() {
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

	}*/
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
			cout << "������������ " << login << "( " << getUserFio() << ")\n" << endl;
			cout << "--------------------------------------------------------\n" << endl;
			cout << "����� �������� �� ������ ���������?" << endl;			
			cout << "\n0- ����� \n1- ������ ������������\n2- ���������� ����������\n3- ���������� ������������\n4" << endl;
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
				cout << "������ �����. ��� ������ ������ ����" << endl;
				break;
			}
		} while (m>='0' && m<'4');
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
	SystemAdmin() :SystemUser() {}
	string showMenu() override {
		char m;
		do {
			system("cls");
			cout << "������������ " << login << "( " << getUserFio() << ")\n" << endl;
			cout << "--------------------------------------------------------\n" << endl;
			cout << "����� �������� �� ������ ���������?" << endl;
			cout << "\n0- ����� \n1- ������� ����� ���������\n2- ������� ����� ����\n3- �������� ������ ������������" << endl;
			cout << "4- ���������������� ������ ������������\n5- ������� ������������ " << endl;

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
				return"adminEditUser";
			case '4':
				return"adminCreateUser";
			case '5':
				return"adminDeleteUser";
			default:
				cout << "������ �����. ��� ������ ������ ����" << endl;
				break;
			}
		} while (m >= '0' && m < '6');
	}
	//void createCategory(IElementTS* root_, ObjectFactory<IElementTS>* factory_)override {
	//	string creatorId = "TestCategoryTS";
	//	IElementTS* newElem = this->createNewElement(factory_, creatorId);
	//	cout << "� ����� ��������� ���������: " << endl;
	//	IElementTS* category_ = this->getCategory(root_);
	//	category_->add(newElem);
	//}

	//void createTest(IElementTS* root_, ObjectFactory<IElementTS>* factory_) override {
	//	string creatorId = "TestTS";
	//	IElementTS* newElem = this->createNewElement(factory_, creatorId);
	//	cout << "� ����� ��������� ���������: " << endl;
	//	IElementTS* category_ = this->getCategory(root_);
	//	category_->add(newElem);
	//	char ch = '�';
	//	do {
	//		IElementTS* question_ = this->createNewQuestion(newElem->getName());
	//		newElem->add(question_);
	//		cout << "�������� ��� ���� ������ � �����?(�/�) ";
	//		cin >> ch;
	//		cin.ignore(2, '\n');
	//	} while (ch == '�');
	//	newElem->saveToFile();
	//}
	////TODO: ��������� ��������� �������� ��������;
	//void deleteElementTS(IElementTS* root_) {
	//	cout << "��� ����� �������: " << endl;
	//	IElementTS* delElem = this->getCategory(root_);
	//}

	void editUser(SystemUser* s) override {
		system("cls");
		cout << "�������������� ������������ " <<s->getLogin()<< endl;
		cout << "----------------------------------------\n";
		char rpt = '�', ch;
		do {
			string st, login, password, name, lname, sname, address, phone;
			do {
				cout << "��� ����� ������?" << endl;
				cout << "1- �������;\n2- ���;\n3- ��������;\n4- �������� �����;\n5- �������;\n6- �����;\n0- �����\n";
				cin >> ch; cin.ignore(2, '\n');
				switch (ch)
				{
				case '1':
					cout << "������� ����� �������: ";
					getline(cin, st);
					s->setSurname(st);
					break;
				case '2':
					cout << "������� ����� ���: ";
					getline(cin, st);
					s->setName(st);
					break;
				case '3':
					cout << "������� ����� ��������: ";
					getline(cin, st);
					s->setLastName(st);
					break;
				case '4':
					cout << "������� ����� �������� �����: ";
					getline(cin, st);
					s->setAddress(st);
					break;
				case '5':
					cout << "������� ����� �������: ";
					getline(cin, st);
					s->setPhone(st);
					break;
				case '6':
					cout << "������� ����� �����: ";
					st = this->getLogin();
					s->setLogin(st);
					break;
				case '0':
					return;
				default:
					cout << "������! ��� ������ ������ ����" << endl;
					break;
					break;
				}
			} while (true);

			cout << "������ �������� ������ ������� ������������?(�/�): ";
			cin >> rpt; cin.ignore(2, '\n');
		} while (rpt == '�');


	}		

	/*void loadUsersFromFile(ObjectFactory<SystemUser>* factory_) {
		string login, role, name, lname, sname, address, phone;
		ifstream inp("Users.txt");
		if (!inp.is_open()) throw FileError("Users.txt", "�� ���� �������� ���������� � �������������!");
		do {
			getline(inp, login);
			getline(inp, role);
			getline(inp, sname);
			getline(inp, name);
			getline(inp, lname);
			getline(inp, address);
			getline(inp, phone);
			TODO: ����������, ����� ��������� ������������ ���������
			SystemUser* suser = factory_->create(role);
			suser->setParam(login, role, sname, name, lname, address, phone);
			users.push_back(suser);
		} while (!inp.eof());
		inp.close();
	}

	void saveUsersToFile() {
		ofstream out("Users.txt");
		for (auto s : users) {
			out << s->getLogin()<<endl;
			out << s->getRole() << endl;
			out << s->getSurname() << endl;
			out << s->getName() << endl;
			out << s->getLastName() << endl;
			out << s->getAddress() << endl;
			out << s->getPhone() << endl;
		}
		out.close();
	}*/


private:	

	/*IElementTS* createNewElement(ObjectFactory<IElementTS>* factory_, string creatorId) {
		string elname;
		cout << "������� ��������: " << endl;
		getline(cin, elname);
		try {
			IElementTS* newEl = factory_->create(creatorId);
		}
		catch (ObjectCreatorError err) {
			cout << err.getError();
		}
		
		newEl->setParam(elname);
	}

	IElementTS* createNewAnswer() {
		int answerNo; string answText;
		cout << "\n����� ������: ";
		answerNo = this->getValue();
		cout << "�����: " << endl;
		getline(cin, answText);
		IElementTS* newAnsw = new AnswerTS();
		newAnsw->setParam(answText, answerNo);
		return newAnsw;

	}
	IElementTS* createNewQuestion(string testName) {
		system("cls");
		cout << "������������ �������� ��� ����� " << testName << endl;
		cout << "-------------------------------------------------\n" << endl;
		int qwNo; string qwText;
		cout << "����� �������: ";
		qwNo = this->getValue();
		cout << "����� �������:" << endl;
		getline(cin, qwText);
		IElementTS* newQw = new QuestionTS();
		newQw->setParam(qwText, qwNo);
		char ch = '�';
		cout << "\n�������� �������� ������� � �������. ��������� ����� �� ����� \"-\", ���� ����� ������������, ��� � \"+ \" - � �������� ������. ��������, \"-������\" ��� \"+�����\"\n" << endl;
		do {
			IElementTS* answ = this->createNewAnswer();
			newQw->add(answ);
			cout << "�������� ��� ���� ����� � �������?(�/�) ";
			cin >> ch;
			cin.ignore(2, '\n');
		} while (ch == '�');
		return newQw;

	}*/


};