#pragma once
#include <thread>
#include <QWidget>
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
#include "ui_CMDMainClass.h"
#include "MACROS.h"

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

	//****************take commands from commands list and return string********************************
	string commands_list_key_commands = "null";//take commands     								//******
	string commands_list_key_commands_for_writing = "null";//take commands						//******
	string __current_command;//take current command												//******
	QString take_current_path = "null";//for taking current path	     						//******
	vector<QString>commands_list_key_commands_vec_all;//all commands							//******
	vector<QString>choose_commands_list_key_commands_vec;//all commands							//******
	fstream temp_file;																			//******
	uint_least16_t check_for_taking_list_command=0;//check for taking first time				//******
	uint_least16_t check_for_taking_list_commandfor_else = 0;									//******
	QString taking_list_command="NONE";															//******
	//**************************************************************************************************

	//***************************	User Defined FUnctions	********************************************
	void addCommandsTOList(void);//Addind CMD Commands Into The List						   //*******
	void addCommandsTOChooseList(void);//Addind CMD Commands Into The List					   //*******
	void addCommandsTOVector(void);//Addind CMD Commands Into The List					       //*******
	void addCommandsTOChooseVector(void);//Addind CMD Commands Into The List				   //*******
	void delayWorkingOneSecond(void);//For Stopping Current Thread For User Gather Inform	   //*******	
	void writeCommandToFile(void);//Execute current Command and writing to STDTEXTFILE	   	   //*******
	void returnBackCursor(void);//enter key for execute batch commands						   //*******
	bool returnCurrentCommandBool(void);//check true command for returning true or false   	   //*******
	bool eventFilter(QObject* object, QEvent* event);//enter key for execute batch commands    //*******
	string returnCurrentCommand(void);//read from textedit and check command is in list	   	   //*******
	//*********************************************************s****************************************

	//*********************   User Defining For Slot Function   ****************************************
	QString getCurrentPath();//Taking current Directory using cmd commands 
	void writeInitially();//Adding current Directory to the Plain Text Edit

	//**************************************************************************************************
	
private slots:

	//*********************************************************	User Defining Slot Function ************

	void on_CommandsLists_currentIndexChanged(const QString& arg1);//Item Selected and Write   Text File
	void on_chooseCommandListFor_currentIndexChanged(const QString& arg1);//Item Selected and Filtering
	void on_execute_btn_clicked();//run button from cli shell class
	

	//**************************************************************************************************
};
