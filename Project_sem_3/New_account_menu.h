#pragma once
#include<string>

using namespace std;
class New_account_menu
{

	string user_login;
	string user_password;

public:
	bool print_new_account_menu();
	void create_new_file();

	New_account_menu();
	~New_account_menu();

};