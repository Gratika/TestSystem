#pragma once
//#include <iostream>
//#include <fstream>
#include<string>
#include<Windows.h>
#include <vector>
#include "ObjectFactory.h"
#include"IElementTS.h"
//#include<iomanip>
using namespace std;
class StructureTS {
	ObjectFactory<IElementTS>* efactory = nullptr;
	IElementTS* rootCategory = nullptr;
public:
	StructureTS() {
		efactory = new ObjectFactory<IElementTS>();
		efactory->add("TestCategoryTS", new ObjectCreator< TestCategoryTS, IElementTS>);
		efactory->add("TestTS", new ObjectCreator< TestTS, IElementTS>);
		efactory->add("QuestionTS", new ObjectCreator< QuestionTS, IElementTS>);
		efactory->add("AnswerTS", new ObjectCreator< AnswerTS, IElementTS>);
		rootCategory = new TestCategoryTS();
		rootCategory->setParam("rootCategory");
		rootCategory->loadFromFile(efactory);
	}
	void showSrtucture() {
		system("cls");
		cout << "��������� �������" << endl;
		cout << "-------------------------------------\n" << endl;
		rootCategory->show();
		system("pause");
	}

	void saveToFile() {
		rootCategory->saveToFile();
	}

	void createCategory() {
		system("cls");
		cout << "�������� ����� ���������" << endl;
		cout << "-------------------------------------\n" << endl;
		string creatorId = "TestCategoryTS";
		IElementTS* newElem = this->createNewElement(creatorId);
		//cout << "� ����� ��������� ���������: " << endl;
		IElementTS* category_ = this->getCategory();
		category_->add(newElem);
		category_->saveToFile();
		cout << "�������� �������" << endl;
		system("pause");
	}

	void createTest() {
		system("cls");
		cout << "�������� ������ �����" << endl;
		cout << "-------------------------------------\n" << endl;
		string creatorId = "TestTS";
		IElementTS* newElem = this->createNewElement(creatorId);
		//cout << "� ����� ��������� ���������: " << endl;
		IElementTS* category_ = this->getCategory();
		category_->add(newElem);
		category_->saveToFile();
		char ch = '�';
		do {
			IElementTS* question_ = this->createNewQuestion(newElem->getName());
			newElem->add(question_);
			cout << "-------------------------------------" << endl;
			cout << "�������� ��� ���� ������ � �����?(�/�) ";
			cin >> ch;
			cin.ignore(2, '\n');
		} while (ch == '�');
		newElem->saveToFile();
		cout << "�������� �������" << endl;
		system("pause");
	}
	void showTest() {
		system("cls");
		cout << "�������� ����������� �����" << endl;
		cout << "-------------------------------------\n" << endl;
		IElementTS* test_ = this->getCategory();
		if (test_->getType() != "TestTS")
			cout << "��������� ���� ������� �� �������� ������" << endl;
		else {
			try {
				test_->loadFromFile(efactory);
				cout << "-------------------------------------------\n" << endl;
				cout << "���� \"" << test_->getName() << "\"" << endl;
				test_->show();
				char actn = '�';
				cout << "������ ������ ��������� � ����?(�/�): ";
				cin >> actn; 
				cin.ignore(2, '\n');
				if (actn == '�') {
					editTest(test_);
					test_->saveToFile();
					//system("pause");
					//test clear
				}
			}
			catch (ErrorTS err) { 
				cout << err.getError() << endl; 
			}
		}
		system("pause");
	}
	void editTest(IElementTS* test_) {
		system("cls");
		cout << "�������������� ����� " <<"\""<< test_->getName() << "\"" << endl;
		cout << "-------------------------------------\n" << endl;
		char actn = '�';
		do {
			char ch;
			cout << "��� ����� ������?\n1-�������� ������;\n2-�������� ������\n3-������� ������" << endl;
			cin >> ch; cin.ignore(32000, '\n');
			int No;
			IElementTS* newQw = nullptr, *elQw = nullptr;
			switch (ch)
			{
			case '1':
				newQw = createNewQuestion(test_->getName());
				test_->add(newQw);
				break;
			case '2':
				cout << "������� ����� �������: ";
				No = getValue();
				try {
					elQw = test_->getElement(No - 1);
					this->editQuestion(elQw);
				}
				catch (ErrorTS err) { cout << err.getError() << endl; }
				break;
			case '3':
				cout << "������� ����� �������: ";
				No = getValue();
				test_->remove(No - 1);
				break;
			default:
				cout << "��������� ����..." << endl;
				break;
			}
			cout << "������ ��� ���-�� �������� � ����� \"" << test_->getName() << "\"?(�/�)";
			cin >> actn; cin.ignore(32000, '\n');
		} while (actn == '�');

	}

	//TODO: ��������� ��������� �������� ��������;
	void deleteElementTS(IElementTS* root_) {
		cout << "��� ����� �������: " << endl;
		IElementTS* delElem = this->getCategory();
	}

	IElementTS* getCategory() {
		IElementTS* elm = rootCategory;
		int ch;
		do {
			system("cls");
			cout << "����� ���������/�����:\n" << endl;
			cout << "0 ������� ��������� (" << elm->getName() << ");" << endl;
			elm->show();
			ch = getValue();
			if (ch != 0)
				try { elm = elm->getElement(ch - 1); }
			catch (OutOfRangeError err) {
				cout << "������! " << err.getError() << endl;
			}

		} while (ch != 0 && elm->getType() != "TestTS");
		return elm;
	}

	IElementTS* createNewElement(string creatorId) {
		cout << "��� ���������� ������ ������������ �������� ������� ���������� ���� ��� ���, � ����� ������� ����� ��� ������������ (���������)" << endl;
		system("pause");
		string elname;
		cout << "������� ��������: " << endl;
		getline(cin, elname);
		try {
			IElementTS* newEl = efactory->create(creatorId);
			newEl->setParam(elname);
			return newEl;
		}
		catch (ObjectCreatorError err) {
			cout << err.getError();
		}

	}

	IElementTS* createNewAnswer() {
		int answerNo; string answText;
		cout << "����������� �����: ";
		getline(cin, answText);
		IElementTS* newAnsw = new AnswerTS();
		newAnsw->setParam(answText);
		return newAnsw;

	}
	IElementTS* createNewQuestion(string testName) {
		system("cls");
		cout << "������������ �������� ��� ����� " << testName << endl;
		cout << "-------------------------------------------------\n" << endl;
		int qwCost; string qwText;
		cout << "��� �������: ";
		qwCost = this->getValue();
		cout << "����� �������: ";
		getline(cin, qwText);
		IElementTS* newQw = new QuestionTS();
		newQw->setParam(qwText, qwCost);
		char ch = '�';
		cout << "�������� �������� ������� � �������. ��������� ����� �� ����� \"-\", ���� ����� ������������, ��� � \"+ \" - � �������� ������. ��������, \"-������\" ��� \"+�����\"\n" << endl;
		do {
			IElementTS* answ = this->createNewAnswer();
			newQw->add(answ);
			cout << "�������� ��� ���� ����� � �������?(�/�) ";
			cin >> ch;
			cin.ignore(2, '\n');
		} while (ch == '�');
		return newQw;

	}
	void editQuestion(IElementTS* el) {
		system("cls");
		cout << "�������������� �������:" << endl;
		//cout << el->getName() << "(" << el->getCost() << ")" << endl;
		el->print();
		cout << "��������� �������: " << el->getCost() << endl;
		cout << "---------------------------------\n" << endl;
		char actn = '�';
		do {
			char ch;
			cout << "��� ����� ������?\n1-����� �������;\n2-��������� �������\n3-������" << endl;
			cin >> ch; cin.ignore(32000, '\n');
			switch (ch)
			{
			case '1':
				this->editTextQw(el);
				break;
			case '2':
				this->editCostQw(el);
				break;
			case '3':
				this->editAnswer(el);
				break;
			default:
				cout << "��������� ����..." << endl;
				break;
			}
			cout << "������ ��� ���-�� �������� � �������: \""<<el->getName()<<"\"?(�/�)";
			cin >> actn; cin.ignore(32000, '\n');
		} while (actn == '�');
	}
	void editTextQw(IElementTS* el) {
		string newName;
		cout << "�������� " << el->getName() << " ��: ";
		getline(cin, newName);
		el->setParam(newName, el->getCost());
	}
	void editCostQw(IElementTS* el) {
		int newCost;
		cout << "�������� " << el->getCost() << " ��: ";
		newCost = getValue();
		el->setParam(el->getName(), newCost);
	}
	void editAnswer(IElementTS* el) {
		system("cls");
		cout << "�������������� ������� �� ������:" << endl;
		//cout << el->getName() << "(" << el->getCost() << ")" << endl;
		el->print();
		cout << "---------------------------------\n" << endl;
		char actn = '�', ch;
		IElementTS* answEl = nullptr, *newAnsw = nullptr;
		do {
			cout << "��� ����� ������?\n1-�������� ������; \n2-��������� ������" << endl;
			cin >> ch; cin.ignore(32000, '\n');
			switch (ch)
			{
			case '1':
				int answ;
				cout << "����� ����� ����� ������?" << endl;
				answ = getValue();
				try {
					answEl = el->getElement(answ - 1);
					editTextAnsw(answEl);
				}
				catch (ErrorTS err) {
					cout << err.getError() << endl;
				}
				break;
			case '2':
				newAnsw = createNewAnswer();
				el->add(newAnsw);
				break;
			default:
				cout << "��������� ����..." << endl;
				break;
			}
			cout << "������ ������� ��� �����-���� ������ ������� �� ������: \"" << el->getName() << "\"?(�/�)";
			cin >> actn; cin.ignore(32000, '\n');
		} while (actn == '�');
	}
	void editTextAnsw(IElementTS* answEl) {
		system("cls");
		string name = answEl->getName(), isCorrect;
		char c = name[0];
		if (c == '+') isCorrect = "����������";
		else isCorrect = "������������";
		if (c == '+' || c == '-') name.erase(0, 1);
		cout << "�������������� ������:" << endl;
		cout << name << " (" << isCorrect << ")" << endl;
		cout << "---------------------------------\n" << endl;
		char actn;
		cout << "���� ����� ���������� (����������)?(�/�): ";
		cin >> actn; cin.ignore(32000, '\n');
		if (actn == '�') c = '+';
		else c = '-';

		cout << "������ �������� ������������ ������?(�/�): ";
		cin >> actn; cin.ignore(32000, '\n');
		if (actn == '�') {
			cout << "�������� " << name << " ��: ";
			getline(cin, name);
		};
		name = c + name;
		answEl->setParam(name);
	}
private:
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
};