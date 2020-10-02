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
	//конструктор. Создается фабрика для генерации элементов и корневая категория
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
		cout << "Структура системы" << endl;
		cout << "-------------------------------------\n" << endl;
		rootCategory->show();
		system("pause");
	}

	void saveToFile() {
		rootCategory->saveToFile();
	}

	//Создание новой категории (с выбором категории размещения)
	void createCategory(string creatorId) {
		char ch = 'н';
		system("cls");
		cout << "Создание новой категории" << endl;
		cout << "-------------------------------------\n" << endl;
		//string creatorId = "TestCategoryTS";
		IElementTS* newElem = nullptr;
		try {
			newElem = this->createNewElement(creatorId);
			//cout << "В какую категорию поместить: " << endl;
			IElementTS* category_ = this->getCategory();
			if (category_->getType() != "TestCategoryTS")
				cout << "Ваш выбор не является категорией" << endl;
			else {
				category_->add(newElem);
				category_->saveToFile();
				cout << "Операция успешна" << endl;

				if (creatorId == "TestTS") {
					cout << "Хотите добавить вопросы к тесту?(д/н): ";
					cin >> ch;
					if (ch == 'д') createNewTest(newElem->getName());
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

	/*Выбор и загрузка теста из файла
	return IElementTS* (загруженный тест)*/
	IElementTS* getTest() {
		IElementTS* test_ = this->getCategory();
		if (test_->getType() != "TestTS") throw ObjectInfoNotFound("Выбранный Вами элемент не является тестом");		
		return test_;
	}
	
	

	

	

	//TODO: закончить процедуру удаления объектов;
	void deleteElementTS(IElementTS* root_) {
		cout << "Что будем удалять: " << endl;
		IElementTS* delElem = this->getCategory();
	}

	/*Выбор элемента структуры(категории или теста) для дальнейших действий с ним
	return IElementTS* (выбранный элемент)*/
	IElementTS* getCategory() {
		IElementTS* elm = rootCategory;
		int ch;
		do {
			system("cls");
			cout << "Выбор категории/теста:\n" << endl;
			cout << "0 Текущая категория (" << elm->getName() << ");" << endl;
			elm->show();
			ch = getValue();
			if (ch != 0) elm = elm->getElement(ch - 1);
		} while (ch != 0 && elm->getType() != "TestTS");
		return elm;
	}
	/*создать новый элемент структуры(категорию или тест)
	return IElementTS* (созданный элемент)*/
	IElementTS* createNewElement(string creatorId) {
		cout << "Для добавления нового структурного элемента сначала необходимо дать ему имя, а потом указать место его расположения (категорию)" << endl;
		system("pause");
		string elname;
		cout << "Укажите название: " << endl;
		getline(cin, elname);
		IElementTS* newEl = efactory->create(creatorId);
		newEl->setParam(elname);
		return newEl;
	}	
	
	
};