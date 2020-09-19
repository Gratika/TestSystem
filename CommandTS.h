#pragma once
#include "SystemUser.h"
#include"SystemLogin.h"
#include "StructureTS.h"
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

class AdminEditUser :public CommandTS<SystemLoginTS> {	
public:
	AdminEditUser(SystemLoginTS *sLgn) :CommandTS<SystemLoginTS>(sLgn){}
	void execute()override {
		string lgn = reseiver_->getLogin();
		SystemUser* s = reseiver_->findUser(lgn);
		if (s == nullptr)cout << "Пользователь не найден" << endl;
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
