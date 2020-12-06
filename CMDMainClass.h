#pragma once
#include <QWidget>
#include <thread>
#include <QDebug>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <qpushbutton.h>
#include <qstring.h>
#include <qobject.h>
#include <qtextdocument.h>
#include <qtextblock>
#include <qcombobox.h>
#include <qkeyevent>
#include <map>
#include <iterator>
#include <qlistwidget.h>
#include "ui_CMDMainClass.h"
#include "MACROS.h"
#include "CMDCommandsList.h"

using namespace std;
using namespace chrono_literals;

class CMDMainClass : public QWidget
{
	Q_OBJECT

public:
	CMDMainClass(QWidget *parent = Q_NULLPTR);
	~CMDMainClass();

private:
	Ui::CMDMainClass ui;

	//*************     take commands from commands list and return string   ***********************************
	CMDCommandsList* CMDCommandsList_obj;//Take All Batch Commands										//******
	QString taking_list_command = "NONE";	//take current commands from cmd list						//******
	string commands_list_key_commands = "null";//take commands     										//******
	string commands_list_key_commands_for_writing = "null";//take commands								//******
	string __current_command;//take current command														//******
	QString take_current_path = "null";//for taking current path	     								//******
	vector<QString>commands_list_key_commands_vec_gather_inform;//all commands	for gather inf			//******
	vector<QString>commands_list_key_commands_vec_network;//all commands for network   					//******
	map<string, uint_least16_t> filter_current_commands_map;//for filtering current commands		    //******
	fstream temp_file;//all comands write in file and read from txt										//******
	uint_least16_t check_for_taking_list_command=0;//check for taking first time						//******
	uint_least16_t check_for_taking_list_commandfor_else = 0;//check first time opening cmd text		//******
	bool current_index_zero = true;//check if filtering index is 0 as default this will true			//******
	bool checking_current_list_command = false;//check if filtering index is 0 as default this will true //******indi yazdim
	//**********************************************************************************************************

	//***************************	User Defined FUnctions	****************************************************
	void startMainFunction(void);//All Functions first start from this function							//******
	void addAllCommandsInCommandsList();//If Filtering commnds is All									//******
	void startCommandsListCurrentIndex(QString args);//Choosing index from CmdList this start		    //******
	void chooseFilteringIndex(uint_least16_t index);//Call True commands for adding cmd lists			//******
	void addCommandsTOListForGatheringInform(void);//Addind CMD Commands Into The List				    //******
	void addCommandsTOListForNetworking(void);//Addind CMD Commands Into The List				        //******
	void delayWorkingOneSecond(void);//For Stopping Current Thread For User Gather Inform 			    //******	
	void writeCommandToFile(void);//Execute current Command and writing to STDTEXTFILE				    //******
	void returnBackCursor(void);//enter key for execute batch commands								    //******
	void addMapAllCommands();//add all commands and vectors to the map									//******
	bool returnCurrentCommandBool(void);//check true command for returning true or false   			    //******
	bool eventFilter(QObject* object, QEvent* event);//enter key for execute batch commands			    //******
	string returnCurrentCommand(void);//read from textedit and check command is in list	   			    //******
	map<string, uint_least16_t> startCurrentCommandsFilter(string arg);//filter commands			    //******
	//*********************************************************s************************************************

	//*********************   User Defining For Slot Function   ************************************************
	QString getCurrentPath();//Taking current Directory using cmd commands							     //*****
	void writeInitially();//Adding current Directory to the Plain Text Edit						         //*****
	//**********************************************************************************************************
	
private slots:

	//*********************************************************	User Defining Slot Function		****************
	void on_CommandsLists_currentIndexChanged(const QString& arg1);//Item Selected and Write Text File   //*****
	void on_chooseCommandListFor_currentIndexChanged(const QString& arg1);//Item Selected and Filtering  //*****
	void on_execute_btn_clicked();//run button from cli shell class										 //*****
	void closeTab(const int &index);//for closing tab widget											 //*****
	void on_listWidget_itemClicked(QListWidgetItem* item);												 //*****
	//**********************************************************************************************************

	
};
