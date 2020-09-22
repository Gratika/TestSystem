#pragma once
#include"CommandTS.h"
#include"StructureTS.h"
#include"SystemLogin.h"
#include <map>

class InvokerTS {
	StructureTS* strcTS = nullptr;
	SystemLoginTS* sLgn = nullptr;
	StatisticsTS* statTS = nullptr;
	ShowMainMenu* showMainMenu = nullptr;
	ShowUserMenu* showUserMenu = nullptr;
	map<string, CommandTS <StructureTS>*> cmdStrcTs;
	map<string, CommandTS <SystemLoginTS>*> cmdSlgnTs;
public:
	InvokerTS(StructureTS* strcTS_, SystemLoginTS* sLgn_, StatisticsTS *statTs_) :strcTS(strcTS_), sLgn(sLgn_), statTS(statTs_) {
		showMainMenu = new ShowMainMenu(sLgn);
		showUserMenu = new ShowUserMenu(sLgn);
		/*commands["showMainMenu"] = new ShowMainMenu(sLgn);
		commands["showUserMenu"] = new ShowUserMenu(sLgn);*/
		cmdSlgnTs["exit"] = new ExitTS(sLgn);
		cmdSlgnTs["showAllUser"] = new ShowAllUser(sLgn);
		cmdStrcTs["createCategory"] = new CreateCategory(strcTS);
		cmdStrcTs["createTest"] = new CreateTest(strcTS);
		cmdStrcTs["showStructure"] = new ShowStructure(strcTS);
		cmdStrcTs["showTest"] = new ShowTest(strcTS);
		cmdSlgnTs["adminEditUser"] = new AdminEditUser(sLgn);
		cmdSlgnTs["adminDeleteUser"] = new AdminDeleteUser(sLgn);
		cmdSlgnTs["adminCreateUser"] = new AdminCreateUser(sLgn);
		cmdSlgnTs["userSingUp"] = new UserSinglUp(sLgn);
		cmdSlgnTs["userLogin"] = new UserLogin(sLgn);		
		cmdStrcTs["beginTesting"] = new BeginTest(strcTS,statTS, sLgn);
		cmdSlgnTs["userGetStatistics"] = new UserGetStatistics(sLgn, statTS);
		cmdSlgnTs["adminGetStatistics"] = new AdminGetStatistics(sLgn,statTS,strcTS);
	}
	~InvokerTS() {
		if(strcTS != nullptr) delete strcTS;
		if(sLgn != nullptr) delete sLgn;
		if(showMainMenu != nullptr) delete showMainMenu;
		if(showUserMenu != nullptr) delete showUserMenu;
	}
	void mainScript(){
		do {
			showMainMenu->execute();
			string resMmenu = showMainMenu->getResultMenu();
			if (resMmenu == "userLogin") {
				try {
					this->doCommand(resMmenu);
					do {
						showUserMenu->execute();
						string resUmenu = showUserMenu->getResultMenu();
						this->doCommand(resUmenu);
					} while (true);

				}
				catch (ErrorTS err) {
					cout << err.getError() << endl;
				}
			}else this->doCommand(resMmenu);
		} while (true);
	}
	void doCommand(string cmd_) {
		auto rezLgn = cmdSlgnTs.find(cmd_);
		auto rezStrc = cmdStrcTs.find(cmd_);
		if (rezLgn != cmdSlgnTs.end()) (rezLgn->second)->execute();
		else (rezStrc->second)->execute();
	}
};