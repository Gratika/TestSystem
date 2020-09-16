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

protected:
	virtual IElementTS* getCategory(IElementTS* root_) {
		IElementTS* elm = root_;		
		int ch;
		do {
			cout << "0 - ������� ���������;" << endl;
			elm->show();
			ch=getValue();			
			if (ch != 0)
				try { elm = elm->getElement(ch); }
			catch (OutOfRangeError err) {
				cout << "������! "<<err.getError() << endl;
			}

		} while (ch != '0');
	}

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
	void createCategory(IElementTS* root_, ObjectFactory<IElementTS>* factory_) {
		string creatorId = "TestCategoryTS";
		IElementTS* newElem = this->createNewElement(factory_, creatorId);
		cout << "� ����� ��������� ���������: " << endl;
		IElementTS* category_ = this->getCategory(root_);
		category_->add(newElem);
	}

	void createTest(IElementTS* root_, ObjectFactory<IElementTS>* factory_) {
		string creatorId = "TestTS";
		IElementTS* newElem = this->createNewElement(factory_, creatorId);
		cout << "� ����� ��������� ���������: " << endl;
		IElementTS* category_ = this->getCategory(root_);
		category_->add(newElem);
		char ch = '�';
		do {
			IElementTS* question_ = this->createNewQuestion(newElem->getName());
			newElem->add(question_);
			cout << "�������� ��� ���� ������ � �����?(�/�) ";
			cin >> ch;
			cin.ignore(2, '\n');
		} while (ch == '�');
		newElem->saveToFile();
	}
	void deleteElementTS(IElementTS* root_){
		cout << "��� ����� �������: " << endl;
		IElementTS* delElem = this->getCategory(root_);
	}


private:	
	IElementTS* createNewElement(ObjectFactory<IElementTS>* factory_, string creatorId){
		string elname;
		cout << "������� ��������: " << endl;
		getline(cin, elname);
		try {
			IElementTS* newEl = factory_->create(creatorId);
		}
		catch (ObjectCreatorError err) {
			cout << err.getError();
		}
		IElementTS* newEl = factory_->create(creatorId);
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
		cout << "������������ �������� ��� ����� "<<testName << endl;
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

	}
	

};