#include "CMDMainClass.h"

CMDMainClass::CMDMainClass(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	CMDCommandsList_obj = new CMDCommandsList;
	startMainFunction();
}

CMDMainClass::~CMDMainClass(){}

//*********************************************************************Slot Defined Functions	**************************************

void CMDMainClass::on_CommandsLists_currentIndexChanged(const QString& arg1)
{
	//For Choosing coommand from list
	startCommandsListCurrentIndex(arg1);
}

void CMDMainClass::on_chooseCommandListFor_currentIndexChanged(const QString& arg1)
{
	//For Filtering Commands List Arguments
	startCurrentCommandsFilter(arg1.toStdString());
}

bool CMDMainClass::eventFilter(QObject* object, QEvent* event)
{//click enter button and execute commands
	if (object == ui.plainTextEdit && event->type() == QEvent::KeyPress)
	{
		QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
		if (keyEvent->key() == Qt::Key_Return){
			returnCurrentCommandBool(); 
			ui.plainTextEdit->insertPlainText("\n");
			returnBackCursor();
		}
		else return false;}else return false;
}

void CMDMainClass::on_execute_btn_clicked(){
	returnCurrentCommandBool();
	ui.plainTextEdit->insertPlainText("\n");
	returnBackCursor();
}

void CMDMainClass::closeTab(const int& index)
{
	ui.tabWidget->removeTab(index);
}

//	*********************************************************************User Defined Functions	**************************************

void CMDMainClass::writeCommandToFile(void)
{
	//this functions create a temp.txt file and writes there the current command;
	string temp = commands_list_key_commands_for_writing + ">" + STDTEXTFILE;
	system(temp.c_str());
}

void CMDMainClass::returnBackCursor(void)
{
	QTextCursor tmpCursor = ui.plainTextEdit->textCursor();
	tmpCursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, CURSORONE);
	ui.plainTextEdit->setTextCursor(tmpCursor);
}

string CMDMainClass::returnCurrentCommand(void)
{
	//return back current command from plaintext
	//take current cursor position
	uint_fast32_t nums = ui.plainTextEdit->textCursor().blockNumber();
	QTextDocument * doc = ui.plainTextEdit->document();//take with document
	QTextBlock  tb = doc->findBlockByLineNumber(nums);//text block cast QString
	QString current_line = tb.text();//cast from qtextblock to string
	string __temp = current_line.toStdString();
	uint_least16_t i = 0;
	if (__temp.size() > 2) {
		for (; i < __temp.size(); i++)
		{
			if (__temp[i] == '>')
				break;
		}
		__current_command.resize(__temp.size() - ++i);
		for (uint_least16_t j = 0; i < __temp.size(); i++, j++)
			__current_command[j] = __temp[i];
	}
	else writeInitially();
	return __current_command;
}

bool CMDMainClass::returnCurrentCommandBool(void)
{
	string __temp = returnCurrentCommand() + ">";
	__temp += STDTEXTFILE;
	system(__temp.c_str());
	string line = "null";
	ifstream temp_file(STDTEXTFILE);
	if (temp_file.is_open())
	{
		while (getline(temp_file, line)) {
			if (line == "\n")
				continue;
			ui.plainTextEdit->insertPlainText("\n" + QString::fromStdString(line) + "\n");
		}
		writeInitially();
		temp_file.close();
		string for_deleting = "DEL "; for_deleting += +STDTEXTFILE;
		system(for_deleting.c_str());
		ui.CommandsLists->setCurrentIndex(0);
	}
	else {
		ui.plainTextEdit->insertPlainText("\n");
		writeInitially();
	}
	return false;
}

void CMDMainClass::delayWorkingOneSecond(void){//For Delay Current Thread for one seconds
	this_thread::sleep_for(chrono::milliseconds(STDDELAYSEC));}

void CMDMainClass::addCommandsTOListForGatheringInform(void)
{
	//clear CommandsList for adding true Filtering Commands
	if(!current_index_zero) 
		ui.CommandsLists->clear();
	//Addind CMD Commands Into The List for Gathering Inform
	CMDCommandsList_obj->addCommandsTOVectorGatherInform(commands_list_key_commands_vec_gather_inform);
	//ui.CommandsLists->addItem("-");
	for (uint_least16_t i = 0; i < commands_list_key_commands_vec_gather_inform.size(); i++)
		ui.CommandsLists->addItem(commands_list_key_commands_vec_gather_inform [ i ] );
	commands_list_key_commands_vec_gather_inform.clear();
}

void CMDMainClass::addCommandsTOListForNetworking(void)
{
	//clear CommandsList for adding true Filtering Commands
	if (!current_index_zero) 
		ui.CommandsLists->clear();
	//Addind CMD Commands Into The List for Networking
	CMDCommandsList_obj->addCommandsTOVectorNetworking(commands_list_key_commands_vec_network);
	for (uint_least16_t i = 0; i < commands_list_key_commands_vec_network.size(); i++)
		ui.CommandsLists->addItem(commands_list_key_commands_vec_network[ i ] );
	commands_list_key_commands_vec_network.clear();
}

void CMDMainClass::addMapAllCommands()
{
	filter_current_commands_map.insert(std::pair<string, uint_least16_t>("All", 
		0));
	filter_current_commands_map.insert(std::pair<string, uint_least16_t>("Gather Information",
		1));
	filter_current_commands_map.insert(std::pair<string, uint_least16_t>("Networking",
		2));

}

map<string, uint_least16_t> CMDMainClass::startCurrentCommandsFilter(string args)
{
	addMapAllCommands();//First Time for activating on_click event in filtering list this func will work
	if (args == "All") addAllCommandsInCommandsList();//first filtering list commands is All which call every commands 
	else
	{
		uint_least16_t check_for_index = 0;
		map<string, uint_least16_t>::iterator it = filter_current_commands_map.begin();
		while (it != filter_current_commands_map.end())
		{
			if (it->first == args)
			{
				current_index_zero = false;
				chooseFilteringIndex(check_for_index);
			}
			it++;
			++check_for_index;
		}
	}
	return map<string, uint_least16_t>();
}

void CMDMainClass::startMainFunction(void)
{
	startFilteringList();							//For activating FilterList
	ui.plainTextEdit->installEventFilter(this);		//For activating enter button inside plaintext	
	
	//***********************************		Tab Widget   **********************************************      
	ui.tabWidget->setTabsClosable(true);									//Can Close TabWidget		***
	ui.tabWidget->setMovable(true);											//Can Move Tab Icon			***				
	ui.tabWidget->setMouseTracking(true);									//Set Highlightes for mouse ***
	connect(ui.tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));//Closing Icon     ***
	//*****************************************************************************************************
}

void CMDMainClass::startFilteringList()
{
	//Add All Filtering Keyword in Filtering List
	ui.chooseCommandListFor->addItem("All");
	ui.chooseCommandListFor->addItem("Gather Information");
	ui.chooseCommandListFor->addItem("Networking");
}

void CMDMainClass::addAllCommandsInCommandsList()
{
	//Filtering keyword if equals ALL this func call
	ui.CommandsLists->clear();
	current_index_zero = true;
	addCommandsTOListForNetworking();
	addCommandsTOListForGatheringInform();
}

void CMDMainClass::startCommandsListCurrentIndex(QString args)
{
	//take current path and add to text file with > operator;
	getCurrentPath();//dont touch it
	//take commands from commands list
	commands_list_key_commands = args.toStdString();
	commands_list_key_commands_for_writing = commands_list_key_commands;
	if (commands_list_key_commands_for_writing == "-")
		commands_list_key_commands_for_writing = "";
	//For delay standart time current thread;
	delayWorkingOneSecond();
	//after clicking commands from list calling this func for first time
	if (check_for_taking_list_command == 0)writeInitially();
	else
	{
		taking_list_command = QString::fromStdString(commands_list_key_commands_for_writing);
		ui.plainTextEdit->insertPlainText(taking_list_command);
		check_for_taking_list_commandfor_else++;
		ui.CommandsLists->setCurrentIndex(0);
	}
	check_for_taking_list_command++;
}

void CMDMainClass::chooseFilteringIndex(uint_least16_t index)
{
	switch (index) 
	{
	case 1:addCommandsTOListForGatheringInform();			break;
	case 2:addCommandsTOListForNetworking();				break;
	default:"THIS IS IMPOSSIBLE";							break;
	}
}

QString CMDMainClass::getCurrentPath()
{
	//for Taking current path from batch
	string temp = "echo %CD% >" ;
	temp += STDCURRENTFILE;
	system(temp.c_str());
	string line = "null";
	ifstream temp_file(STDCURRENTFILE);
	if (temp_file.is_open())
	{
		while (getline(temp_file, line))
			take_current_path = QString::fromStdString(line);
		temp_file.close();
	}
	return take_current_path;
}

void CMDMainClass::writeInitially()
{
	//when selected commands from list, this function will work 
	ui.plainTextEdit->insertPlainText(take_current_path + "> " + QString::fromStdString(
		commands_list_key_commands_for_writing));
}


//********************************************************************************************************