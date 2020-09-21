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
			cout << "\n¬ыполните вход в систему, чтобы начать работу\n" << endl;
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

class BeginTest :public CommandTS<StructureTS> {	
	GetSystemUser *getUser = nullptr;
	FindTestStatisticsForUser* getStst = nullptr;
	StatisticsAddElem* addStat = nullptr;

	
	StatisticsElem* findStat = nullptr;
	SystemUser* sUser = nullptr;
	IElementTS* test_ = nullptr;
	StatisticsElem *rezStat = nullptr;
public:
	BeginTest(StructureTS* strcTS, GetSystemUser* getUser, FindTestStatisticsForUser* getStst, StatisticsAddElem *addStat)
		:CommandTS<StructureTS>(strcTS) {		
		this->getUser = getUser;
		this->getStst = getStst;
		this->addStat = addStat;
	}
	void execute()override {
		system("cls");
		cout << "ѕроцесс тестировани€" << endl;
		cout << "-------------------------------------\n" << endl;
		//получить пользовател€
		getUser->execute();
		try {
			sUser = getUser->getFindUser();
			//получить тест
			test_ = reseiver_->getTest();			
			//получить результаты статистики по тесту дл€ пользовател€
			getStst->setParam(sUser->getLogin(), test_->getName(), (test_->getParent())->getName());
			getStst->execute();
			findStat = getStst->getFindStat();
			//запустить тестирование и получить результаты
			rezStat = reseiver_->beginTesting(test_, findStat);
			rezStat->print();
			addStat->setParam(rezStat);
			addStat->execute();

		}
		catch (ErrorTS err) { cout << err.getError() << endl; }		
	}	

	~BeginTest() {
		if(getUser != nullptr) delete getUser;
		if (getStst != nullptr) delete getStst;
		if (addStat != nullptr) delete addStat;
	}
};

class UserGetStatistics :public CommandTS<SystemLoginTS> {	
	SystemUser* sUser = nullptr;
	FindUserStatistics* findUserStat=nullptr;
public:
	UserGetStatistics(SystemLoginTS* sLgn, FindUserStatistics* fus) :CommandTS<SystemLoginTS>(sLgn), findUserStat(fus) {}
	void execute()override {
		sUser = reseiver_->getSystemUser();
		findUserStat->setLogin(sUser->getLogin());
		findUserStat->execute;
	}
	


};
//просмотреть статистику пользовател€
class FindUserStatistics :public CommandTS<StatisticsTS> {
	string login;
public:
	FindUserStatistics(StatisticsTS* ststcTS) :CommandTS<StatisticsTS>(ststcTS) {}
	void execute()override {
		reseiver_->findUserStatistic(login);
	}
	void setLogin(string login) { this->login = login; }

};

class FindTestStatisticsForUser :public CommandTS<StatisticsTS> {
	string login;
	string testName;
	string testCategory;
	StatisticsElem* findStat = nullptr;
	
public:
	FindTestStatisticsForUser(StatisticsTS* ststcTS):CommandTS<StatisticsTS>(ststcTS) {}
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
	StatisticsAddElem (StatisticsTS *ststcTS) :CommandTS<StatisticsTS>(ststcTS) {}
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

class AdminEditUser :public CommandTS<SystemLoginTS> {	
public:
	AdminEditUser(SystemLoginTS *sLgn) :CommandTS<SystemLoginTS>(sLgn){}
	void execute()override {
		string lgn = reseiver_->getLogin();
		SystemUser* s = reseiver_->findUser(lgn);
		if (s == nullptr)cout << "ѕользователь не найден" << endl;
		else reseiver_->getSystemUser()->editUser(s);
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
