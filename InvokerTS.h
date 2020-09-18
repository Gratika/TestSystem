#pragma once
#include"CommandTS.h"
#include"StructureTS.h"
#include"SystemLogin.h"
#include <map>
template<class... Types>
class InvokerTS {
	StructureTS* strcTS = nullptr;
	SystemLoginTS* sLgn = nullptr;
	ShowMainMenu* showMainMenu = nullptr;
	ShowUserMenu* showUserMenu = nullptr;
	map<string, CommandTS <Types>*> commands;
public:
	InvokerTS(StructureTS* strcTS_, SystemLoginTS* sLgn_) :strcTS(strcTS_), sLgn(sLgn_) {
		showMainMenu = new ShowMainMenu(sLgn);
		showUserMenu = new ShowUserMenu(sLgn);
		/*commands["showMainMenu"] = new ShowMainMenu(sLgn);
		commands["showUserMenu"] = new ShowUserMenu(sLgn);*/
		commands["exit"] = new ExitTS(sLgn);
		commands["createCategory"] = new CreateCategory(strcTS);
		commands["createTest"] = new CreateTest(strcTS);
		commands["adminEditUser"] = new AdminEditUser(sLgn);
		commands["adminDeleteUser"] = new AdminDeleteUser(sLgn);
		commands["adminCreateUser"] = new AdminCreateUser(sLgn);
		commands["userSingUp"] = new UserSinglUp(sLgn);
		commands["userLogin"] = new UserLogin(sLgn);
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
		auto rez = commands.find(cmd_);		
		//(rez.second)->execute();
	}
};