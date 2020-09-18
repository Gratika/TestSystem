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
	IElementTS *rootCategory=nullptr;
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
	void print() {
		rootCategory->print();
	}

	void saveToFile() {
		rootCategory->saveToFile();
	}

	void createCategory(){
		string creatorId = "TestCategoryTS";
		IElementTS* newElem = this->createNewElement(creatorId);
		cout << "� ����� ��������� ���������: " << endl;
		IElementTS* category_ = this->getCategory();
		category_->add(newElem);
	}

	void createTest() {
		string creatorId = "TestTS";
		IElementTS* newElem = this->createNewElement(creatorId);
		cout << "� ����� ��������� ���������: " << endl;
		IElementTS* category_ = this->getCategory();
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
	//TODO: ��������� ��������� �������� ��������;
	void deleteElementTS(IElementTS* root_) {
		cout << "��� ����� �������: " << endl;
		IElementTS* delElem = this->getCategory();
	}

	virtual IElementTS* getCategory() {
		IElementTS* elm = rootCategory;
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
	}

	IElementTS* createNewElement(string creatorId) {
		string elname;
		cout << "������� ��������: " << endl;
		getline(cin, elname);
		try {
			IElementTS* newEl = efactory->create(creatorId);
			newEl->setParam(elname);
		}
		catch (ObjectCreatorError err) {
			cout << err.getError();
		}		
		
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