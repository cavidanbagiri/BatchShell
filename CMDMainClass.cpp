#include "CMDMainClass.h"

CMDMainClass::CMDMainClass(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	addCommandsTOList();							//Function Calls FUNC(addCommandsTOVector) inside. Dont Touch IT
	addCommandsTOChooseList();						//Function Calls FUNC(addCommandsTOChooseVector) inside. Dont Touch IT
	ui.plainTextEdit->installEventFilter(this);		//for activating enter button inside plaintext

}

CMDMainClass::~CMDMainClass(){}

//*********************************************************************Slot Defined Functions	**********
void CMDMainClass::on_CommandsLists_currentIndexChanged(const QString& arg1)
{
	//take current path and add to text file with > operator;
	getCurrentPath();//dont touch it
	//take commands from commands list
	commands_list_key_commands = arg1.toStdString();
	commands_list_key_commands_for_writing = commands_list_key_commands;
	if (commands_list_key_commands_for_writing == "-")
		commands_list_key_commands_for_writing = "";
	//For delay standart time current thread;
	delayWorkingOneSecond();
	//after clicking commands from list calling this func for first time
	if (check_for_taking_list_command == 0)
		writeInitially();
	else
	{
		//if (check_for_taking_list_commandfor_else == 0)
		//{
			taking_list_command = QString::fromStdString(commands_list_key_commands_for_writing);
			ui.plainTextEdit->insertPlainText(taking_list_command);
			check_for_taking_list_commandfor_else++;
			ui.CommandsLists->setCurrentIndex(0);
		//1	}
	}
	check_for_taking_list_command++;
}

void CMDMainClass::on_chooseCommandListFor_currentIndexChanged(const QString& arg1)
{
	//For Filtering Commands List Arguments

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

//********************************************************************************************************

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//	*********************************************************************User Defined Functions	**********

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

void CMDMainClass::addCommandsTOList(void)
{
	//Addind CMD Commands Into The List
	addCommandsTOVector();
	ui.CommandsLists->addItem("-");
	for (uint_least16_t i = 0; i < commands_list_key_commands_vec_all.size(); i++)
		ui.CommandsLists->addItem(commands_list_key_commands_vec_all [ i ]);
}

void CMDMainClass::addCommandsTOVector(void)
{
	//Adding Commands To The List For Reading By User
	commands_list_key_commands_vec_all.push_back("whoami");
	commands_list_key_commands_vec_all.push_back("hostname");
}

void CMDMainClass::addCommandsTOChooseList(void)
{
	//Add Filtering Commands to the List
	addCommandsTOChooseVector();
	for (uint_least16_t i = 0; i < choose_commands_list_key_commands_vec.size(); i++)
		ui.chooseCommandListFor->addItem(choose_commands_list_key_commands_vec [ i ] );
}

void CMDMainClass::addCommandsTOChooseVector(void)
{
	//Add Choosing List For Filtering Commands
	choose_commands_list_key_commands_vec.push_back("All");
	choose_commands_list_key_commands_vec.push_back("Network");
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

//when selected commands from list, this function will work 
void CMDMainClass::writeInitially()
{
	ui.plainTextEdit->insertPlainText(take_current_path + "> " + QString::fromStdString(
		commands_list_key_commands_for_writing));
}

//********************************************************************************************************


