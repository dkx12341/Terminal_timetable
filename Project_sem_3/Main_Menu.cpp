#include "Main_Menu.h"
#include <functional>  // for function
#include <iostream>  // for basic_ostream::operator<<, operator<<, endl, basic_ostream, basic_ostream<>::__ostream_type, cout, ostream
#include <string>    // for string, basic_string, allocator
#include <vector>    // for vector
#include <conio.h>


#include "ftxui/component/captured_mouse.hpp"      // for ftxui
#include "ftxui/component/component.hpp"           // for Menu
#include "ftxui/component/component_options.hpp"   // for MenuOption
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive


Main_Menu::Main_Menu()
{
    run_program();

}

void Main_Menu::run_program()
{
    while (true)
    {
        int next_scene = print_menu();
        if (next_scene == 0)
        {
            Log_in_menu* log_menu = new Log_in_menu;
            delete log_menu;
        }
        else if (next_scene == 1)
        {
            New_account_menu* new_acc_menu = new New_account_menu;
            delete new_acc_menu;
        }
    }
}

int Main_Menu::print_menu()
{
    system("CLS");
        
        using namespace ftxui;
        auto screen = ScreenInteractive::TerminalOutput();

        std::vector<std::string> entries = {
            "Log in",
            "Create New Account",
            "Exit",
        };
        int selected = 0;

        MenuOption option;
        option.on_enter = screen.ExitLoopClosure();
        auto menu = Menu(&entries, &selected, option);
       
        screen.Loop(menu);
       
       
        return selected;

}

void Main_Menu::exit_program()
{


}


Main_Menu::~Main_Menu()
{

}