#pragma once
#include "SystemUser.h"
class CommandTS {
protected:
	SystemUser* user_;
public:
	CommandTS(SystemUser* sUser):user_(sUser){}
	virtual void execute() = 0;
	~CommandTS(){}
};

class ShowUserMenu : public CommandTS {
	string resultMenu;
public:
	ShowUserMenu(SystemUser* sUser) :CommandTS(sUser) {}
	void execute()override {
		this->resultMenu = user_->showMenu();
	}
	string getResultMenu() { return this->resultMenu; }
};

class CreateCategory :public CommandTS {
	IElementTS* root_;
	ObjectFactory<IElementTS>* factory_;
public:
	CreateCategory(SystemUser *sUser, IElementTS* root, ObjectFactory<IElementTS>* factory):CommandTS(sUser), factory_(factory), root_(root){}
	void execute()override {
		user_->createCategory(root_, factory_);
	}
};

class CreateTest :public CommandTS {
	IElementTS* root_;
	ObjectFactory<IElementTS>* factory_;
public:
	CreateTest(SystemUser* sUser, IElementTS* root, ObjectFactory<IElementTS>* factory) :CommandTS(sUser), factory_(factory), root_(root) {}
	void execute()override {
		user_->createTest(root_, factory_);
	}
};

class AdminEditUser:public CommandTS{
}

