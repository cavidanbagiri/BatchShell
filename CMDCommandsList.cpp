#include "CMDCommandsList.h"


void CMDCommandsList::startFilteringList(QComboBox * combo_box)
{
	//Add All Filtering Keyword in Filtering List
	combo_box->addItem("All");
	combo_box->addItem("Gather Information");
	combo_box->addItem("Networking");
}

void CMDCommandsList::addCommandsTOVectorGatherInform(vector<QString>& commands_list_key_commands_vec_gather_inform)
{
	//Adding Commands To The List For Reading By User for Gathering Inform
	commands_list_key_commands_vec_gather_inform.push_back("-");
	commands_list_key_commands_vec_gather_inform.push_back("whoami");
	commands_list_key_commands_vec_gather_inform.push_back("hostname");
}

void CMDCommandsList::addCommandsTOVectorNetworking(vector<QString>& commands_list_key_commands_vec_network)
{
	//Adding Commands To The List For Reading By User for Networking
	commands_list_key_commands_vec_network.push_back("-");
	commands_list_key_commands_vec_network.push_back("ipconfig");
	commands_list_key_commands_vec_network.push_back("arp -a");
	commands_list_key_commands_vec_network.push_back("netsh wlan show profile");
}
