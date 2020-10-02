#pragma once
//#include <iostream>
//#include <fstream>
#include<string>
#include<Windows.h>
#include <vector>
#include "ObjectFactory.h"
#include"IElementTS.h"
#include "MyFunction.h"
#include"TestListTS.h"
//#include<iomanip>
using namespace std;
class StructureTS {
	ObjectFactory<IElementTS>* efactory = nullptr;
	IElementTS* rootCategory = nullptr;
public:
	//�����������. ��������� ������� ��� ��������� ��������� � �������� ���������
	StructureTS() {
		efactory = new ObjectFactory<IElementTS>();
		efactory->add("TestCategoryTS", new ObjectCreator< TestCategoryTS, IElementTS>);
		efactory->add("TestTS", new ObjectCreator< TestTS, IElementTS>);		
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

	//�������� ����� ��������� (� ������� ��������� ����������)
	void createCategory(string creatorId) {
		char ch = '�';
		system("cls");
		cout << "�������� ����� ���������" << endl;
		cout << "-------------------------------------\n" << endl;
		//string creatorId = "TestCategoryTS";
		IElementTS* newElem = nullptr;
		try {
			newElem = this->createNewElement(creatorId);
			//cout << "� ����� ��������� ���������: " << endl;
			IElementTS* category_ = this->getCategory();
			if (category_->getType() != "TestCategoryTS")
				cout << "��� ����� �� �������� ����������" << endl;
			else {
				category_->add(newElem);
				category_->saveToFile();
				cout << "�������� �������" << endl;

				if (creatorId == "TestTS") {
					cout << "������ �������� ������� � �����?(�/�): ";
					cin >> ch;
					if (ch == '�') createNewTest(newElem->getName());
				}
			}
		}
		catch (ErrorTS err) {
			cout << err.getError() << endl;
			if (newElem != nullptr) delete newElem;
		}		
		system("pause");
	}
	
	void createNewTest(string testName) {
		shared_ptr<TestListTS> newTest = make_shared<TestListTS>(TestListTS(testName));
		newTest->createTest();		
	}

	StatisticsElem* beginTesting(IElementTS* test_, StatisticsElem* bgnStEl) {
		shared_ptr<TestListTS> newTest = make_shared<TestListTS>(TestListTS(test_->getName()));
		newTest->beginTesting(bgnStEl, (test_->getParent())->getName());
	}

	/*����� � �������� ����� �� �����
	return IElementTS* (����������� ����)*/
	IElementTS* getTest() {
		IElementTS* test_ = this->getCategory();
		if (test_->getType() != "TestTS") throw ObjectInfoNotFound("��������� ���� ������� �� �������� ������");		
		return test_;
	}
	
	

	

	

	//TODO: ��������� ��������� �������� ��������;
	void deleteElementTS(IElementTS* root_) {
		cout << "��� ����� �������: " << endl;
		IElementTS* delElem = this->getCategory();
	}

	/*����� �������� ���������(��������� ��� �����) ��� ���������� �������� � ���
	return IElementTS* (��������� �������)*/
	IElementTS* getCategory() {
		IElementTS* elm = rootCategory;
		int ch;
		do {
			system("cls");
			cout << "����� ���������/�����:\n" << endl;
			cout << "0 ������� ��������� (" << elm->getName() << ");" << endl;
			elm->show();
			ch = getValue();
			if (ch != 0) elm = elm->getElement(ch - 1);
		} while (ch != 0 && elm->getType() != "TestTS");
		return elm;
	}
	/*������� ����� ������� ���������(��������� ��� ����)
	return IElementTS* (��������� �������)*/
	IElementTS* createNewElement(string creatorId) {
		cout << "��� ���������� ������ ������������ �������� ������� ���������� ���� ��� ���, � ����� ������� ����� ��� ������������ (���������)" << endl;
		system("pause");
		string elname;
		cout << "������� ��������: " << endl;
		getline(cin, elname);
		IElementTS* newEl = efactory->create(creatorId);
		newEl->setParam(elname);
		return newEl;
	}	
	
	
};