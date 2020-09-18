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
			cout << "0 - Текущая категория;" << endl;
			elm->show();
			ch = getValue();
			if (ch != 0)
				try { elm = elm->getElement(ch); }
			catch (OutOfRangeError err) {
				cout << "Ошибка! " << err.getError() << endl;
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
				cout << "Ошибка ввода. Ожидается ввод числового значения" << endl;
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
			cout << "Пользователь " << login << "( " << getUserFio() << ")\n" << endl;
			cout << "--------------------------------------------------------\n" << endl;
			cout << "Какое действие Вы хотите выполнить?" << endl;			
			cout << "\n0- Выход \n1- Пройти тестирование\n2- Посмотреть результаты\n3- Продолжить тестирование\n4" << endl;
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
				cout << "Ошибка ввода. Нет такого пункта меню" << endl;
				break;
			}
		} while (m>='0' && m<'4');
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
	SystemAdmin() :SystemUser() {}
	string showMenu() override {
		char m;
		do {
			system("cls");
			cout << "Пользователь " << login << "( " << getUserFio() << ")\n" << endl;
			cout << "--------------------------------------------------------\n" << endl;
			cout << "Какое действие Вы хотите выполнить?" << endl;
			cout << "\n0- Выход \n1- Создать новую категорию\n2- Создать новый тест\n3- Изменить данные пользователя" << endl;
			cout << "4- Зарегистрировать нового пользователя\n5- Удалить пользователя " << endl;

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
				cout << "Ошибка ввода. Нет такого пункта меню" << endl;
				break;
			}
		} while (m >= '0' && m < '6');
	}
	//void createCategory(IElementTS* root_, ObjectFactory<IElementTS>* factory_)override {
	//	string creatorId = "TestCategoryTS";
	//	IElementTS* newElem = this->createNewElement(factory_, creatorId);
	//	cout << "В какую категорию поместить: " << endl;
	//	IElementTS* category_ = this->getCategory(root_);
	//	category_->add(newElem);
	//}

	//void createTest(IElementTS* root_, ObjectFactory<IElementTS>* factory_) override {
	//	string creatorId = "TestTS";
	//	IElementTS* newElem = this->createNewElement(factory_, creatorId);
	//	cout << "В какую категорию поместить: " << endl;
	//	IElementTS* category_ = this->getCategory(root_);
	//	category_->add(newElem);
	//	char ch = 'н';
	//	do {
	//		IElementTS* question_ = this->createNewQuestion(newElem->getName());
	//		newElem->add(question_);
	//		cout << "Добавить еще один вопрос к тесту?(д/н) ";
	//		cin >> ch;
	//		cin.ignore(2, '\n');
	//	} while (ch == 'д');
	//	newElem->saveToFile();
	//}
	////TODO: закончить процедуру удаления объектов;
	//void deleteElementTS(IElementTS* root_) {
	//	cout << "Что будем удалять: " << endl;
	//	IElementTS* delElem = this->getCategory(root_);
	//}

	void editUser(SystemUser* s) override {
		system("cls");
		cout << "Редактирование пользователя " <<s->getLogin()<< endl;
		cout << "----------------------------------------\n";
		char rpt = 'н', ch;
		do {
			string st, login, password, name, lname, sname, address, phone;
			do {
				cout << "Что будем менять?" << endl;
				cout << "1- Фамилию;\n2- Имя;\n3- Отчество;\n4- Домашний адрес;\n5- Телефон;\n6- Логин;\n0- Выход\n";
				cin >> ch; cin.ignore(2, '\n');
				switch (ch)
				{
				case '1':
					cout << "Укажите новую фамилию: ";
					getline(cin, st);
					s->setSurname(st);
					break;
				case '2':
					cout << "Укажите новое имя: ";
					getline(cin, st);
					s->setName(st);
					break;
				case '3':
					cout << "Укажите новое отчество: ";
					getline(cin, st);
					s->setLastName(st);
					break;
				case '4':
					cout << "Укажите новый домашний адрес: ";
					getline(cin, st);
					s->setAddress(st);
					break;
				case '5':
					cout << "Укажите новый телефон: ";
					getline(cin, st);
					s->setPhone(st);
					break;
				case '6':
					cout << "Укажите новый логин: ";
					st = this->getLogin();
					s->setLogin(st);
					break;
				case '0':
					return;
				default:
					cout << "Ошибка! Нет такого пункта меню" << endl;
					break;
					break;
				}
			} while (true);

			cout << "Хотите изменить данные другого пользователя?(д/н): ";
			cin >> rpt; cin.ignore(2, '\n');
		} while (rpt == 'д');


	}		

	/*void loadUsersFromFile(ObjectFactory<SystemUser>* factory_) {
		string login, role, name, lname, sname, address, phone;
		ifstream inp("Users.txt");
		if (!inp.is_open()) throw FileError("Users.txt", "Не могу получить информацию о пользователях!");
		do {
			getline(inp, login);
			getline(inp, role);
			getline(inp, sname);
			getline(inp, name);
			getline(inp, lname);
			getline(inp, address);
			getline(inp, phone);
			TODO: посмотреть, какой последний пользователь создастся
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
		cout << "Укажите название: " << endl;
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
		cout << "Формирование вопросов для теста " << testName << endl;
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

	}*/


};