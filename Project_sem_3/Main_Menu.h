#pragma once
#include <string>
#include "Log_in_menu.h"
#include "New_account_menu.h"

class Main_Menu
{
public:

	void run_program();
	int print_menu();
	void log_in_the_user();
	void go_to_create_new_user();
	void go_to_options();
	void exit_program();

	

	Main_Menu();
	~Main_Menu();
};