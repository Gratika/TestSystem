#pragma once
//#include <iostream>
//#include <fstream>
#include<string>
#include<Windows.h>
#include <vector>
#include "ObjectFactory.h"
#include"IElementTS.h"
#include"StatisticsElem.h"
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
	//Создание новой категории (с выбором категории размещения)
	void createCategory() {
		system("cls");
		cout << "Создание новой категории" << endl;
		cout << "-------------------------------------\n" << endl;
		string creatorId = "TestCategoryTS";
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
			}
		}
		catch (ErrorTS err) {
			cout << err.getError() << endl;
			if (newElem != nullptr) delete newElem;
		}
		system("pause");
	}
	//Создание теста (с выбором категории размещения)
	void createTest() {
		system("cls");
		cout << "Создание нового теста" << endl;
		cout << "-------------------------------------\n" << endl;
		string creatorId = "TestTS";
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
			}
		}
		catch (ErrorTS err) {
			cout << "Ошибка! " << err.getError() << endl;
			if (newElem != nullptr) delete newElem;
		}

		system("pause");
	}

	/*Выбор и загрузка теста из файла
	return IElementTS* (загруженный тест)*/
	IElementTS* getTest() {
		IElementTS* test_ = this->getCategory();
		if (test_->getType() != "TestTS") throw ObjectInfoNotFound("Выбранный Вами элемент не является тестом");
		if(test_->getSize() ==0) test_->loadFromFile(efactory);
		return test_;
	}
	
	//Процес тестирования
	StatisticsElem* beginTesting(IElementTS* test_, StatisticsElem *bgnStEl) {
		int beginNo = 0; int id = 0;
		if (bgnStEl != nullptr && !bgnStEl->isFinished()) {
			cout << "Вы остановились на вопросе №" << (bgnStEl->getNoLast())+1 << ". Продолжить проходжение теста(д) или начать сначала(н)?" << endl;
			char ch;
			cin >> ch;
			cin.ignore(3200, '\n');
			if (ch == 'д') beginNo = bgnStEl->getNoLast();
			else {
				id = bgnStEl->getId();
				bgnStEl = nullptr;
			}
		}		
		StatisticsElem* rezTest = doTesting(test_, beginNo);
		if (bgnStEl == nullptr) {
			if (id != 0) rezTest->setId(id);
			return rezTest;		
		}
		else {
			if (bgnStEl->isFinished()) {
				
				if (rezTest->getGetingMark() > bgnStEl->getGetingMark()) return rezTest;
				else { 
					if (rezTest != nullptr)delete rezTest;
					return bgnStEl; 
				}
			}
			else {
				StatisticsElem* rez = bgnStEl->operator+(rezTest);
				if (rezTest != nullptr)delete rezTest;
				return (rez);			
				
			}
		}		
	}


	StatisticsElem* doTesting(IElementTS* test_, int beginNo) {
		
		double getMark = 0, maxMark=test_->getMaxCost();//переменные для статистики
		int cntCrtQw = 0, cntIncrtQw = 0, cntMsnQw = 0, NoLast;		
		int NoAnsw;
		for ( int NoQw= beginNo; NoQw < test_->getSize(); NoQw++) { //перебираем вопросы теста
			system("cls");
			cout << "Тест \"" << test_->getName() << "\" (кол-во вопросов: " << test_->getSize() << ")" << endl;
			cout << "--------------------------------------------------------\n" << endl;
			NoLast = NoQw;
			IElementTS* qw = test_->getElement(NoQw); //получаю вопрос по номеру
			int costQw = qw->getCost();//стоимость вопроса
			double tmpCostQw = 0;//стоимость ответа, которую получил пользователь
			cout << "Вопрос № " << NoQw +1<<" (вес вопроса - "<<costQw<<" б.)"<< endl;
			qw->print();
			int cntCrctAnsw = getCountCorrectAnswer(qw);//количество правильных ответов
			int allAnsw = 0, getCntCrctAnsw = 0;
			char ch = 'н';
			do {				
				cout << "Укажите правильный, на ваш взгляд, вариант ответа(0 - пропустить вопрос, -1 - прервать тестирование):";
				do {
					NoAnsw = getValue();
					if (NoAnsw < 0 || NoAnsw > qw->getSize())
						cout << "Ошибочный ввод. Еще попытка: ";
				} while ((NoAnsw < 0 || NoAnsw > qw->getSize()) && (NoAnsw!=-1) );
				if (NoAnsw != -1) {//если пользователь не прерівает тестирование
					if (NoAnsw != 0) {//если пользователь не пропускает вопрос
						allAnsw++;
						if ((qw->getElement(NoAnsw - 1))->getCorrect())
							getCntCrctAnsw++;//считаем полученую стоимость
						cout << "Может есть еще правильные ответы?(д/н): ";
						cin >> ch;
					}
					else cntMsnQw++;//иначе - увеличиваем число пропущенных вопросов
				}			

			} while (ch == 'д');
			if (NoAnsw != -1) {
				if (NoAnsw != 0)
				{
					getMark += (getCntCrctAnsw * costQw) / cntCrctAnsw / allAnsw;//считаем полученный бал
				  //определяем, куда отнести вопрос: правильный или нет
					if (cntCrctAnsw==getCntCrctAnsw && cntCrctAnsw == allAnsw)cntCrtQw++;
					else cntIncrtQw++;
				}
			}
			else {
				cout << " \nТестирование прервано по запросу пользователя" << endl;
				break;
			}			
		}
		StatisticsElem* newStEl = new StatisticsElem((test_->getParent())->getName(), test_->getName(), test_->getSize(), maxMark, getMark, cntCrtQw, cntIncrtQw, cntMsnQw, NoLast);
		return newStEl;
	}
	
	double getCountCorrectAnswer(IElementTS* question) {
		int cntCrtQw = 0;
		for (int i = 0; i < question->getSize(); i++)
			if ((question->getElement(i))->getCorrect())cntCrtQw++;
		
		return cntCrtQw;
	}

	//Просмотр выбраного теста
	void showTest() {
		system("cls");
		cout << "Просмотр содержимого теста" << endl;
		cout << "-------------------------------------\n" << endl;
		try {
			IElementTS* test_ = this->getTest();
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
			cout << "Ошибка! " << err.getError() << endl;
		}
		system("pause");
	}

	//Редактирование конкретного теста
	void editTest(IElementTS* test_) {
		system("cls");
		cout << "Редактирование теста " << "\"" << test_->getName() << "\"" << endl;
		cout << "-------------------------------------\n" << endl;
		char actn = 'н';
		do {
			char ch;
			cout << "Что будем делать?\n1-Добавить вопрос;\n2-Изменить вопрос\n3-Удалить вопрос" << endl;
			cin >> ch; cin.ignore(32000, '\n');
			int No;
			IElementTS* newQw = nullptr, * elQw = nullptr;
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
				try {
					test_->remove(No - 1);
				}
				catch (ErrorTS err) { cout << err.getError() << endl; }
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


	/*создать новый ответ
	return IElementTS* (созданный ответ)*/
	IElementTS* createNewAnswer() {
		string answText;
		cout << "Сформируйте ответ: ";
		getline(cin, answText);
		IElementTS* newAnsw = new AnswerTS();
		newAnsw->setParam(answText);
		return newAnsw;

	}

	/*создать новый вопрос
	return IElementTS* (созданный вопрос)*/
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
	//редактирование конкретного вопроса(меню действий)
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
			cout << "Хотите еще что-то изменить в вопросе: \"" << el->getName() << "\"?(д/н)";
			cin >> actn; cin.ignore(32000, '\n');
		} while (actn == 'д');
	}
	//редактирование формулировки конкретного вопроса
	void editTextQw(IElementTS* el) {
		string newName;
		cout << "Заменить " << el->getName() << " на: ";
		getline(cin, newName);
		el->setParam(newName, el->getCost());
	}
	//редактирование стоимости конкретного вопроса 
	void editCostQw(IElementTS* el) {
		int newCost;
		cout << "Заменить " << el->getCost() << " на: ";
		newCost = getValue();
		el->setParam(el->getName(), newCost);
	}
	//редактирование ответов (варианты выбора действий и их реализация)
	void editAnswer(IElementTS* el) {
		system("cls");
		cout << "Редактирование ответов на вопрос:" << endl;
		//cout << el->getName() << "(" << el->getCost() << ")" << endl;
		el->print();
		cout << "---------------------------------\n" << endl;
		char actn = 'н', ch;
		IElementTS* answEl = nullptr, * newAnsw = nullptr;
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
	//редактирование конкретного ответа в вопросе
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
	//Для считывания числовых значений из консоли
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