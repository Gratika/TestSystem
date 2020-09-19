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
		cout << "Структура системы" << endl;
		cout << "-------------------------------------\n" << endl;
		rootCategory->show();
		system("pause");
	}

	void saveToFile() {
		rootCategory->saveToFile();
	}

	void createCategory() {
		system("cls");
		cout << "Создание новой категории" << endl;
		cout << "-------------------------------------\n" << endl;
		string creatorId = "TestCategoryTS";
		IElementTS* newElem = this->createNewElement(creatorId);
		//cout << "В какую категорию поместить: " << endl;
		IElementTS* category_ = this->getCategory();
		category_->add(newElem);
		category_->saveToFile();
		cout << "Операция успешна" << endl;
		system("pause");
	}

	void createTest() {
		system("cls");
		cout << "Создание нового теста" << endl;
		cout << "-------------------------------------\n" << endl;
		string creatorId = "TestTS";
		IElementTS* newElem = this->createNewElement(creatorId);
		//cout << "В какую категорию поместить: " << endl;
		IElementTS* category_ = this->getCategory();
		category_->add(newElem);
		category_->saveToFile();
		char ch = 'н';
		do {
			IElementTS* question_ = this->createNewQuestion(newElem->getName());
			newElem->add(question_);
			cout << "-------------------------------------" << endl;
			cout << "Добавить еще один вопрос к тесту?(д/н) ";
			cin >> ch;
			cin.ignore(2, '\n');
		} while (ch == 'д');
		newElem->saveToFile();
		cout << "Операция успешна" << endl;
		system("pause");
	}
	void showTest() {
		system("cls");
		cout << "Просмотр содержимого теста" << endl;
		cout << "-------------------------------------\n" << endl;
		IElementTS* test_ = this->getCategory();
		if (test_->getType() != "TestTS")
			cout << "Выбранный Вами элемент не является тестом" << endl;
		else {
			try {
				test_->loadFromFile(efactory);
				cout << "-------------------------------------------\n" << endl;
				cout << "Тест \"" << test_->getName() << "\"" << endl;
				test_->show();
				char actn = 'н';
				cout << "Хотите внести изменения в тест?(д/н): ";
				cin >> actn; 
				cin.ignore(2, '\n');
				if (actn == 'д') {
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
		cout << "Редактирование теста " <<"\""<< test_->getName() << "\"" << endl;
		cout << "-------------------------------------\n" << endl;
		char actn = 'н';
		do {
			char ch;
			cout << "Что будем делать?\n1-Добавить вопрос;\n2-Изменить вопрос\n3-Удалить вопрос" << endl;
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
				cout << "Укажите номер вопроса: ";
				No = getValue();
				try {
					elQw = test_->getElement(No - 1);
					this->editQuestion(elQw);
				}
				catch (ErrorTS err) { cout << err.getError() << endl; }
				break;
			case '3':
				cout << "Укажите номер вопроса: ";
				No = getValue();
				test_->remove(No - 1);
				break;
			default:
				cout << "Ошибочный ввод..." << endl;
				break;
			}
			cout << "Хотите еще что-то изменить в тесте \"" << test_->getName() << "\"?(д/н)";
			cin >> actn; cin.ignore(32000, '\n');
		} while (actn == 'д');

	}

	//TODO: закончить процедуру удаления объектов;
	void deleteElementTS(IElementTS* root_) {
		cout << "Что будем удалять: " << endl;
		IElementTS* delElem = this->getCategory();
	}

	IElementTS* getCategory() {
		IElementTS* elm = rootCategory;
		int ch;
		do {
			system("cls");
			cout << "Выбор категории/теста:\n" << endl;
			cout << "0 Текущая категория (" << elm->getName() << ");" << endl;
			elm->show();
			ch = getValue();
			if (ch != 0)
				try { elm = elm->getElement(ch - 1); }
			catch (OutOfRangeError err) {
				cout << "Ошибка! " << err.getError() << endl;
			}

		} while (ch != 0 && elm->getType() != "TestTS");
		return elm;
	}

	IElementTS* createNewElement(string creatorId) {
		cout << "Для добавления нового структурного элемента сначала необходимо дать ему имя, а потом указать место его расположения (категорию)" << endl;
		system("pause");
		string elname;
		cout << "Укажите название: " << endl;
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
		cout << "Сформируйте ответ: ";
		getline(cin, answText);
		IElementTS* newAnsw = new AnswerTS();
		newAnsw->setParam(answText);
		return newAnsw;

	}
	IElementTS* createNewQuestion(string testName) {
		system("cls");
		cout << "Формирование вопросов для теста " << testName << endl;
		cout << "-------------------------------------------------\n" << endl;
		int qwCost; string qwText;
		cout << "Вес вопроса: ";
		qwCost = this->getValue();
		cout << "Текст вопроса: ";
		getline(cin, qwText);
		IElementTS* newQw = new QuestionTS();
		newQw->setParam(qwText, qwCost);
		char ch = 'н';
		cout << "Добавьте варианты ответов к вопросу. Начинайте ответ со знака \"-\", если ответ некорректный, или с \"+ \" - в обратном случае. Например, \"-яблоко\" или \"+груша\"\n" << endl;
		do {
			IElementTS* answ = this->createNewAnswer();
			newQw->add(answ);
			cout << "Добавить еще один ответ к вопросу?(д/н) ";
			cin >> ch;
			cin.ignore(2, '\n');
		} while (ch == 'д');
		return newQw;

	}
	void editQuestion(IElementTS* el) {
		system("cls");
		cout << "Редактирование вопроса:" << endl;
		//cout << el->getName() << "(" << el->getCost() << ")" << endl;
		el->print();
		cout << "Стоимость вопроса: " << el->getCost() << endl;
		cout << "---------------------------------\n" << endl;
		char actn = 'н';
		do {
			char ch;
			cout << "Что будем менять?\n1-Текст вопроса;\n2-Стоимость вопроса\n3-Ответы" << endl;
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
				cout << "Ошибочный ввод..." << endl;
				break;
			}
			cout << "Хотите еще что-то изменить в вопросе: \""<<el->getName()<<"\"?(д/н)";
			cin >> actn; cin.ignore(32000, '\n');
		} while (actn == 'д');
	}
	void editTextQw(IElementTS* el) {
		string newName;
		cout << "Заменить " << el->getName() << " на: ";
		getline(cin, newName);
		el->setParam(newName, el->getCost());
	}
	void editCostQw(IElementTS* el) {
		int newCost;
		cout << "Заменить " << el->getCost() << " на: ";
		newCost = getValue();
		el->setParam(el->getName(), newCost);
	}
	void editAnswer(IElementTS* el) {
		system("cls");
		cout << "Редактирование ответов на вопрос:" << endl;
		//cout << el->getName() << "(" << el->getCost() << ")" << endl;
		el->print();
		cout << "---------------------------------\n" << endl;
		char actn = 'н', ch;
		IElementTS* answEl = nullptr, *newAnsw = nullptr;
		do {
			cout << "Что будем делать?\n1-изменять ответы; \n2-добавлять ответы" << endl;
			cin >> ch; cin.ignore(32000, '\n');
			switch (ch)
			{
			case '1':
				int answ;
				cout << "Какой ответ будем менять?" << endl;
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
				cout << "Ошибочный ввод..." << endl;
				break;
			}
			cout << "Хотите сделать еще какие-либо правки ответов на вопрос: \"" << el->getName() << "\"?(д/н)";
			cin >> actn; cin.ignore(32000, '\n');
		} while (actn == 'д');
	}
	void editTextAnsw(IElementTS* answEl) {
		system("cls");
		string name = answEl->getName(), isCorrect;
		char c = name[0];
		if (c == '+') isCorrect = "правильный";
		else isCorrect = "неправильный";
		if (c == '+' || c == '-') name.erase(0, 1);
		cout << "Редактирование ответа:" << endl;
		cout << name << " (" << isCorrect << ")" << endl;
		cout << "---------------------------------\n" << endl;
		char actn;
		cout << "Этот ответ правильный (корректный)?(д/н): ";
		cin >> actn; cin.ignore(32000, '\n');
		if (actn == 'д') c = '+';
		else c = '-';

		cout << "Будите изменять формулировку ответа?(д/н): ";
		cin >> actn; cin.ignore(32000, '\n');
		if (actn == 'д') {
			cout << "Заменить " << name << " на: ";
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
				cout << "Ошибка ввода. Ожидается ввод числового значения" << endl;
			}
			else {
				cin.ignore(32767, '\n');
				return a;
			}
		}

	}
};