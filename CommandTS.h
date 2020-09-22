#pragma once
#include "SystemUser.h"
#include"SystemLogin.h"
#include "StructureTS.h"
#include "StatisticsTS.h"
#include "StatisticsElem.h"
template<class T>
class CommandTS {
protected:
	T *reseiver_;
public:
	CommandTS<T>(T  *rsvr):reseiver_(rsvr){}
	virtual void execute() = 0;
	~CommandTS(){}
};

class ShowMainMenu : public CommandTS<SystemLoginTS> {
	string resultMainMenu;
public:
	ShowMainMenu(SystemLoginTS* sLgn) :CommandTS<SystemLoginTS>(sLgn) {}
	void execute()override {
		this->resultMainMenu = reseiver_->showMainMenu();
	}
	string getResultMenu() { return this->resultMainMenu; }
};

class UserSinglUp :public CommandTS<SystemLoginTS> {
public:
	UserSinglUp(SystemLoginTS* sLgn) :CommandTS<SystemLoginTS>(sLgn) {}
	void execute()override {
		try {
			this-> reseiver_->registerUser(false);
			cout << "\nВыполните вход в систему, чтобы начать работу\n" << endl;
		}
		catch (ErrorTS err) {
			cout << err.getError() << endl;
		}
		system("pause");
		
	}
};

class UserLogin :public CommandTS<SystemLoginTS> {
public:
	UserLogin(SystemLoginTS* sLgn) :CommandTS<SystemLoginTS>(sLgn) {}
	void execute()override {		
		this->reseiver_->userLogin();		

	}
};

class ShowUserMenu : public CommandTS<SystemLoginTS> {
	string resultMenu;
public:
	ShowUserMenu(SystemLoginTS* sLgn) :CommandTS<SystemLoginTS>(sLgn) {}
	void execute()override {
		this->resultMenu = reseiver_->showUserMenu();
	}
	string getResultMenu() { return this->resultMenu; }
};

class CreateCategory :public CommandTS<StructureTS> {	
public:
	CreateCategory(StructureTS *strcTS):CommandTS<StructureTS>(strcTS){}
	void execute()override {
		reseiver_->createCategory();
	}
};

class CreateTest :public CommandTS<StructureTS> {
public:
	CreateTest(StructureTS* strcTS) :CommandTS<StructureTS>(strcTS) {}
	void execute()override {
		reseiver_->createTest();
	}
};

class ShowStructure :public CommandTS<StructureTS> {
public:
	ShowStructure(StructureTS* strcTS) :CommandTS<StructureTS>(strcTS) {}
	void execute()override {
		reseiver_->showSrtucture();
	}
};

class ShowTest :public CommandTS<StructureTS> {
public:
	ShowTest(StructureTS* strcTS) :CommandTS<StructureTS>(strcTS) {}
	void execute()override {
		reseiver_->showTest();
	}
};

class GetTest :public CommandTS<StructureTS> {
	IElementTS* fTest_ = nullptr;
public:
	GetTest(StructureTS* strcTS) :CommandTS<StructureTS>(strcTS) {}
	void execute()override {
		fTest_=reseiver_->getTest();
	}
	IElementTS* getFindTest() { return this->fTest_; }

};
//просмотреть статистику пользователя
class FindUserStatistics :public CommandTS<StatisticsTS> {
	string login;
public:
	FindUserStatistics(StatisticsTS* ststcTS) :CommandTS<StatisticsTS>(ststcTS) {}
	void execute()override {
		reseiver_->findUserStatistic(login);
	}
	void setLogin(string login) { this->login = login; }

};

class FindTestStatistics :public CommandTS<StatisticsTS> {
	string testName;
public:
	FindTestStatistics(StatisticsTS* ststcTS) :CommandTS<StatisticsTS>(ststcTS) {}
	void execute()override {
		reseiver_->findTestStatistic(this->testName);
	}
	void setTestName(string tName) { this->testName = tName; }
};

class FindCategoryStatistics :public CommandTS<StatisticsTS> {
	string categoryName;
public:
	FindCategoryStatistics(StatisticsTS* ststcTS) :CommandTS<StatisticsTS>(ststcTS) {}
	void execute()override {
		reseiver_->findTestCategoryStatistic(this->categoryName);
	}
	void setCategoryName(string cName) { this->categoryName = cName; }

};

class FindTestStatisticsForUser :public CommandTS<StatisticsTS> {
	string login;
	string testName;
	string testCategory;
	StatisticsElem* findStat = nullptr;

public:
	FindTestStatisticsForUser(StatisticsTS* ststcTS) :CommandTS<StatisticsTS>(ststcTS) {}
	void execute()override {
		findStat = reseiver_->findTestStatisticForUser(this->login, this->testName, this->testCategory);
	}
	void setParam(string login, string testName, string testCategory) {
		this->login = login;
		this->testName = testName;
		this->testCategory = testCategory;
	}
	StatisticsElem* getFindStat() {
		return this->findStat;
	}
};
class StatisticsAddElem :public CommandTS<StatisticsTS> {
	StatisticsElem* stEl = nullptr;
public:
	StatisticsAddElem(StatisticsTS* ststcTS) :CommandTS<StatisticsTS>(ststcTS) {}
	void execute()override {
		reseiver_->add(this->stEl);
	}

	void setParam(StatisticsElem* el) {
		this->stEl = el;
	}

};


class GetSystemUser :public CommandTS<SystemLoginTS> {
	SystemUser* sUser = nullptr;
public:
	GetSystemUser(SystemLoginTS* sLgn) :CommandTS<SystemLoginTS>(sLgn) {}
	void execute()override {
		sUser = reseiver_->getSystemUser();
	}
	SystemUser* getFindUser() { return this->sUser; }
};

class BeginTest :public CommandTS<StructureTS> {	
		
	SystemUser* sUser = nullptr;
	IElementTS* test_ = nullptr;
	StatisticsElem* rezStat = nullptr;
	StatisticsTS* stat = nullptr;
	SystemLoginTS* sLgn = nullptr;
	StatisticsElem* findStat = nullptr;	
public:
	BeginTest(StructureTS* strcTS, StatisticsTS* stat, SystemLoginTS* sLgn):CommandTS<StructureTS>(strcTS),stat(stat), sLgn(sLgn) {}
	void execute()override {
		system("cls");
		cout << "Процесс тестирования" << endl;
		cout << "-------------------------------------\n" << endl;
		//получить пользователя
		shared_ptr<GetSystemUser> getSUser = make_shared <GetSystemUser>(sLgn);
		getSUser->execute();
		try {
			sUser = getSUser->getFindUser();
			//получить тест
			test_ = reseiver_->getTest();			
			//получить результаты статистики по тесту для пользователя
			shared_ptr<FindTestStatisticsForUser> getStst = make_shared <FindTestStatisticsForUser>(stat);
			getStst->setParam(sUser->getLogin(), test_->getName(), (test_->getParent())->getName());
			getStst->execute();
			findStat = getStst->getFindStat();
			//запустить тестирование и получить результаты
			rezStat = reseiver_->beginTesting(test_, findStat);
			rezStat->print();
			shared_ptr<StatisticsAddElem> addStat = make_shared <StatisticsAddElem>(stat);
			addStat->setParam(rezStat);
			addStat->execute();					
		}
		catch (ErrorTS err) { 
			cout << err.getError() << endl;
		}	
		system("pause");
	}	
	~BeginTest() {}
};

class UserGetStatistics :public CommandTS<SystemLoginTS> {	
	SystemUser* sUser = nullptr;
	StatisticsTS  *stat;	
public:
	UserGetStatistics(SystemLoginTS* sLgn, StatisticsTS *stat) :CommandTS<SystemLoginTS>(sLgn),stat(stat) {}
	void execute()override {
		sUser = reseiver_->getSystemUser();	
		shared_ptr<FindUserStatistics> fus = make_shared<FindUserStatistics>(stat);
		fus->setLogin(sUser->getLogin());
		fus->execute();	
		system("pause");
	}
	~UserGetStatistics() {}
};

class GetStructureElem :public CommandTS<StructureTS> {
	IElementTS* elemST = nullptr;
public:
	GetStructureElem(StructureTS* strcTS) :CommandTS<StructureTS>(strcTS) {}
	void execute()override {
		elemST = reseiver_->getCategory();
	}
	IElementTS* getFindElem() { return this->elemST; }
};

class AdminGetStatistics :public CommandTS<SystemLoginTS> {
	SystemUser* sUser = nullptr;
	IElementTS* elemST = nullptr;
	StatisticsTS* stat = nullptr;
	StructureTS* strTS = nullptr;
	/*FindUserStatistics* findUserStat = nullptr;
	GetStructureElem* getElem = nullptr;
	FindTestStatistics* findTestStat = nullptr;
	FindCategoryStatistics* findCategStat = nullptr;*/
public:
	AdminGetStatistics(SystemLoginTS* sLgn, StatisticsTS* stat, StructureTS* strTS) :CommandTS<SystemLoginTS>(sLgn), stat(stat), strTS(strTS) {}
	void execute()override {
		system("cls");
		cout << "Раздел статистики" << endl;
		cout << "-------------------------------------\n" << endl;	
		char ch;
		do {
			cout << "Что желаете просмотреть?\n1- Статистика по пользователю\n2- Статистика по категории\n3- Статистика по тесту\n0- Выход" << endl;
			cin >> ch;
			cin.ignore(3200, '\n');
			string sLgn;
			switch (ch)
			{
			case '1':
				system("cls");
				cout << "Статистика пользователя" << endl;
				cout << "-------------------------------------\n" << endl;
				cout << "Введите логин пользователя: ";
				getline(cin, sLgn);
				sUser = reseiver_->findUser(sLgn);
				if (sUser == nullptr) cout << "Пользователь не найден" << endl;
				else {
					shared_ptr< FindUserStatistics> findUserStat = make_shared<FindUserStatistics>(stat);
					findUserStat->setLogin(sUser->getLogin());
					findUserStat->execute();
				}				
				break;
			case '2':
				try {
					shared_ptr<GetStructureElem> getElem = make_shared<GetStructureElem>(strTS);
					getElem->execute();
					elemST = getElem->getFindElem();
					if (elemST->getType() != "TestTS") cout << ("Выбранный Вами элемент не является тестом");
					else {
						shared_ptr< FindTestStatistics> findTestStat = make_shared<FindTestStatistics>(stat);
						findTestStat->setTestName(elemST->getName());
						findTestStat->execute();
					}
				}
				catch (ErrorTS err) { cout << err.getError() << endl; }				
				break;
			case '3':
				try {
					shared_ptr<GetStructureElem> getCElem = make_shared<GetStructureElem>(strTS);
					getCElem->execute();
					elemST = getCElem->getFindElem();
					if (elemST->getType() != "TestCategoryTS") cout << ("Выбранный Вами элемент не является категорией");
					else {
						shared_ptr<FindCategoryStatistics> findCategStat = make_shared<FindCategoryStatistics>(stat);
						findCategStat->setCategoryName((elemST->getParent())->getName());
						findCategStat->execute();
					}
				}
				catch (ErrorTS err) { cout << err.getError() << endl; }
				break;
			case '0':
				return;
			default:
				cout << "Ошибка ввода! Нет такого пункта меню..." << endl;
				break;
			}
			system("pause");
		} while (true);			
	}
	~AdminGetStatistics() {	}
};






class AdminEditUser :public CommandTS<SystemLoginTS> {	
public:
	AdminEditUser(SystemLoginTS *sLgn) :CommandTS<SystemLoginTS>(sLgn){}
	void execute()override {
		reseiver_->editUser();
		reseiver_->saveUsersToFile();
	}
};

class AdminDeleteUser :public CommandTS<SystemLoginTS> {	
public:
	AdminDeleteUser (SystemLoginTS *sLgn) :CommandTS<SystemLoginTS>(sLgn) {}
	void execute()override {
		reseiver_->deleteUser();
		reseiver_->saveUsersToFile();

	}
};
class AdminCreateUser :public CommandTS<SystemLoginTS> {	
public:
	AdminCreateUser(SystemLoginTS *sLgn) :CommandTS<SystemLoginTS>(sLgn) {}
	void execute()override {
		reseiver_->registerUser(false);
		reseiver_->saveUsersToFile();

	}
};
class ShowAllUser :public CommandTS<SystemLoginTS> {
public:
	ShowAllUser(SystemLoginTS* sLgn) :CommandTS<SystemLoginTS>(sLgn) {}
	void execute()override {
		reseiver_->showAllUser();
	}
};
class ExitTS :public CommandTS<SystemLoginTS> {
public:
	ExitTS(SystemLoginTS* sLgn) :CommandTS<SystemLoginTS>(sLgn) {}
	void execute()override {
		exit(0);
	}
};
