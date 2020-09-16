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
		cout << "Пользователь " << login << "( " << getUserFio() << ")\n" << endl;
		cout << "Какое действие Вы хотите выполнить?" << endl;
	}
	virtual ~SystemUser(){};

protected:
	virtual IElementTS* getCategory(IElementTS* root_) {
		IElementTS* elm = root_;		
		int ch;
		do {
			cout << "0 - Текущая категория;" << endl;
			elm->show();
			ch=getValue();			
			if (ch != 0)
				try { elm = elm->getElement(ch); }
			catch (OutOfRangeError err) {
				cout << "Ошибка! "<<err.getError() << endl;
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
				cout << "Ошибка ввода. Ожидается ввод числового значения" << endl;
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
			cout << "\n0- Вернуться в главное меню \n1- Пройти тестирование\n2- Посмотреть результаты\n3- Продолжить тестирование\n4" << endl;
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
				cout << "Ошибка ввода. Нет такого пункта меню" << endl;
				break;
			}
		} while (true);	    
	}
	void getResult() {
		//открыть файл с названием = логин
		//считать данные (класс ResultTest-??)
		//отобразить на экран
	}
	void doTesting() {
		//показать дерево тестов
		//загрузить тест из файла
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
		cout << "В какую категорию поместить: " << endl;
		IElementTS* category_ = this->getCategory(root_);
		category_->add(newElem);
	}

	void createTest(IElementTS* root_, ObjectFactory<IElementTS>* factory_) {
		string creatorId = "TestTS";
		IElementTS* newElem = this->createNewElement(factory_, creatorId);
		cout << "В какую категорию поместить: " << endl;
		IElementTS* category_ = this->getCategory(root_);
		category_->add(newElem);
		char ch = 'н';
		do {
			IElementTS* question_ = this->createNewQuestion(newElem->getName());
			newElem->add(question_);
			cout << "Добавить еще один вопрос к тесту?(д/н) ";
			cin >> ch;
			cin.ignore(2, '\n');
		} while (ch == 'д');
		newElem->saveToFile();
	}
	void deleteElementTS(IElementTS* root_){
		cout << "Что будем удалять: " << endl;
		IElementTS* delElem = this->getCategory(root_);
	}


private:	
	IElementTS* createNewElement(ObjectFactory<IElementTS>* factory_, string creatorId){
		string elname;
		cout << "Укажите название: " << endl;
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
		cout << "\nНомер ответа: ";
		answerNo = this->getValue();
		cout << "Ответ: " << endl;
		getline(cin, answText);
		IElementTS* newAnsw = new AnswerTS();
		newAnsw->setParam(answText, answerNo);
		return newAnsw;

	}
	IElementTS* createNewQuestion(string testName) {
		system("cls");
		cout << "Формирование вопросов для теста "<<testName << endl;
		cout << "-------------------------------------------------\n" << endl;
		int qwNo; string qwText;
		cout << "Номер вопроса: ";
		qwNo = this->getValue();
		cout << "Текст вопроса:" << endl;
		getline(cin, qwText);
		IElementTS* newQw = new QuestionTS();
		newQw->setParam(qwText, qwNo);	
		char ch = 'н';
		cout << "\nДобавьте варианты ответов к вопросу. Начинайте ответ со знака \"-\", если ответ некорректный, или с \"+ \" - в обратном случае. Например, \"-яблоко\" или \"+груша\"\n" << endl;
		do {
			IElementTS* answ = this->createNewAnswer();
			newQw->add(answ);
			cout << "Добавить еще один ответ к вопросу?(д/н) ";
			cin >> ch;
			cin.ignore(2, '\n');
		} while (ch == 'д');
		return newQw;

	}
	

};