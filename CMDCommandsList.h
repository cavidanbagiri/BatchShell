#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <qstring.h>
#include <qcombobox.h>

using namespace std;

class CMDCommandsList
{
public:
	void addCommandsTOVectorGatherInform(vector<QString>&commands_list_key_commands_vec_gather_inform);//Addind CMD Commands Into The List					    //******
	void addCommandsTOVectorNetworking(vector<QString>& commands_list_key_commands_vec_network);//Addind CMD Commands Into The List					    //******
	void startFilteringList(QComboBox * combo_box);
};
