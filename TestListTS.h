#pragma once
#include <iostream>
#include<fstream>
#include <vector>
#include<string>
#include"QuestionTS.h"
#include"MyFunction.h"
#include"ErrorTS.h"
#include"StatisticsElem.h"
using namespace std;

class TestListTS {
	string name;
	string fileName;
	vector<QuestionTS*> questions;
public:
	TestListTS(string name) {
		this->name = name;
		fileName = this->name + ".txt";
	}

	void loadFromFile() {
		int cntQw;
		ifstream inp(fileName);
		if (!inp.is_open()) throw FileError(fileName, "Похоже теста больше нет!");
		inp >> cntQw; inp.ignore(2, '\n');
		for (int j = 0; j < cntQw; j++) {
			QuestionTS* qwst = new QuestionTS();
			qwst->loadFromFile(inp);
			questions.push_back(qwst);
		}
		inp.close();
	}

	void saveToFile() {
		ofstream out(fileName);
		out << questions.size() << endl;
		for (auto i : this->questions) {
			i->saveToFile(out);
		}
		out.close();
	}

	void print(bool withCorrect = false) {
		for (int i = 0; i < this->questions.size(); i++) {
			cout << i + 1 << " ";
			questions[i]->print(withCorrect);
		}
	}

	void addQuestion() {
		QuestionTS* newQw = new QuestionTS();
		cin >> newQw;
		questions.push_back(newQw);
	}

	void deleteQw(int id) {
		questions.erase(questions.begin() + id);
	}

	//Просмотр выбраного теста
	void showTest() {
		loadFromFile();
		system("cls");
		cout << "Просмотр содержимого теста" << endl;
		cout << "-------------------------------------\n" << endl;
		cout << "Тест \"" << name << "\"" << endl;
		print(true);
		char actn = 'н';
		cout << "Хотите внести изменения в тест?(д/н): ";
		cin >> actn;
		cin.ignore(2, '\n');
		if (actn == 'д') {
			try {
				editTest();
				cout << "Сохранить внесенные изменения?(д/н): ";
				cin >> actn; cin.ignore(2, '\n');
				if (actn == 'д') saveToFile();
			}
			catch (ErrorTS err) {
				cout << "Ошибка! " << err.getError() << endl;
			}
		}
		system("pause");
	}

	//Редактирование конкретного теста
	void editTest() {
		char actn = 'н';
		do {
			system("cls");
			cout << "Редактирование теста " << "\"" << name << "\"" << endl;
			cout << "-------------------------------------\n" << endl;
			char ch;
			cout << "Что будем делать?\n1-Добавить вопрос;\n2-Изменить вопрос\n3-Удалить вопрос" << endl;
			cin >> ch; cin.ignore(32000, '\n');
			int No;
			switch (ch)
			{
			case '1':
				addQuestion();
				break;
			case '2':
				cout << "Какой вопрос будем менять? ";
				No = getValue();
				if (No - 1 < 0 || No - 1 >= questions.size()) throw OutOfRangeError("Вопроса с таким номером не существует!");
				questions[No - 1]->edit();
				break;
			case '3':
				cout << "Какой вопрос будем удалять? ";
				No = getValue();
				if (No - 1 < 0 || No - 1 >= questions.size()) throw OutOfRangeError("Вопроса с таким номером не существует!");
				deleteQw(No - 1);
				break;
			default:
				cout << "Ошибочный ввод..." << endl;
				break;
			}
			cout << "Хотите продолжить редактирование теста?(д/н): ";
			cin >> actn; cin.ignore(32000, '\n');
		} while (actn == 'д');		
	}

	//Процес тестирования
	StatisticsElem* beginTesting(StatisticsElem* bgnStEl, string ctgrName) {
		loadFromFile();
		int beginNo = 0; int id = -1;
		if (bgnStEl != nullptr && !bgnStEl->isFinished()) {
			cout << "Вы остановились на вопросе №" << (bgnStEl->getNoLast()) + 1 << ". Продолжить проходжение теста(д) или начать сначала(н)?" << endl;
			char ch;
			cin >> ch;
			cin.ignore(3200, '\n');
			if (ch == 'д') beginNo = bgnStEl->getNoLast();
			else {
				id = bgnStEl->getId();
				bgnStEl = nullptr;
			}
		}
		StatisticsElem* rezTest = doTesting(beginNo, ctgrName);
		if (bgnStEl == nullptr) {
			if (id != -1) rezTest->setId(id);
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


	StatisticsElem* doTesting(int beginNo, string ctgrName) {

		double getMark = 0, maxMark = getMaxCost();//переменные для статистики
		int cntCrtQw = 0, cntIncrtQw = 0, cntMsnQw = 0, NoLast;
		int NoAnsw;
		for (int NoQw = beginNo; NoQw < questions.size(); NoQw++) { //перебираем вопросы теста
			system("cls");
			cout << "Тест \"" << name << "\" (кол-во вопросов: " << questions.size() << ")" << endl;
			cout << "--------------------------------------------------------\n" << endl;
			NoLast = NoQw;
			QuestionTS* qw = questions[NoQw]; //получаю вопрос по номеру
			int costQw = qw->getCost();//стоимость вопроса
			double tmpCostQw = 0;//стоимость ответа, которую получил пользователь
			cout << "Вопрос № " << NoQw + 1 << " (вес вопроса - " << costQw << " б.)" << endl;
			qw->print();
			int cntCrctAnsw = qw->getCountCorrectAnswer();//количество правильных ответов
			int allAnsw = 0, getCntCrctAnsw = 0;
			char ch = 'н';
			do {
				cout << "Укажите правильный, на ваш взгляд, вариант ответа(0 - пропустить вопрос, -1 - прервать тестирование):";
				do {
					NoAnsw = getValue();
					if (NoAnsw < 0 || NoAnsw > qw->getSize())
						cout << "Ошибочный ввод. Еще попытка: ";
				} while ((NoAnsw < 0 || NoAnsw > qw->getSize()) && (NoAnsw != -1));
				if (NoAnsw != -1) {//если пользователь не прерівает тестирование
					if (NoAnsw != 0) {//если пользователь не пропускает вопрос
						allAnsw++;
						if (qw->isCorrect(NoAnsw-1))
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
					if (cntCrctAnsw == getCntCrctAnsw && cntCrctAnsw == allAnsw)cntCrtQw++;
					else cntIncrtQw++;
				}
			}
			else {
				cout << " \nТестирование прервано по запросу пользователя" << endl;
				break;
			}
		}
		StatisticsElem* newStEl = new StatisticsElem(ctgrName, name, questions.size(), maxMark, getMark, cntCrtQw, cntIncrtQw, cntMsnQw, NoLast);
		return newStEl;
	}

	int getMaxCost() {
		int mCost = 0;
		for (auto el : questions)
			mCost += el->getCost();
		return mCost;
	}

	//Создание теста (с выбором категории размещения)
	void createTest() {
		char ch = 'н';
		do {
			system("cls");
			cout << "Создание нового теста" << endl;
			cout << "-------------------------------------\n" << endl;
			addQuestion();
			cout << "-------------------------------------" << endl;
			cout << "Добавить еще один вопрос к тесту?(д/н) ";
			cin >> ch;
			cin.ignore(2, '\n');
		} while (ch == 'д');
		cout << "Сохранить внесенные изменения?(д/н): ";
		cin >> ch;cin.ignore(2, '\n');
		if(ch == 'д') saveToFile();
		cout << "Операция успешна" << endl;
		system("pause");
	}
};
