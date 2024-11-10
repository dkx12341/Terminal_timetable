#include "New_account_menu.h"

#include <memory>  // for allocator, __shared_ptr_access
#include <string>  // for char_traits, operator+, string, basic_string
#include <iostream>
#include <fstream>
#include <filesystem>

#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"       // for Input, Renderer, Vertical
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/component/component_options.hpp"  // for InputOption
#include "ftxui/component/screen_interactive.hpp"  // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for text, hbox, separator, Element, operator|, vbox, border
#include "ftxui/util/ref.hpp"  // for Ref

using namespace std;

New_account_menu::New_account_menu()
{
	while (print_new_account_menu() == false)
	{

	}
    create_new_file();

}


bool New_account_menu::print_new_account_menu()
{
    system("CLS");
    using namespace ftxui;

    // The data:
    string temp_user_login;
    string temp_user_password;
    string repeated_password;

    


    // The basic input components:
    Component input_login = Input(&temp_user_login, "login");


    // The password input component:
    InputOption password_option;
    password_option.password = true;
    Component input_password = Input(&temp_user_password, "password", password_option);

    Component input_repeated_password = Input(&repeated_password, "password", password_option);

    // The phone number input component:
    // We are using `CatchEvent` to filter out non-digit characters
   // auto on_click = [&] {screen.ExitLoopClosure(); };
   // auto style = ButtonOption::Animated(Color::Default, Color::GrayDark,
      //  Color::Default, Color::White);

    //auto button = Button("Login", on_click, style);

    // The component tree:
    auto component = Container::Vertical({
        input_login,
        input_password,
        input_repeated_password,
        });

    // Tweak how the component tree is rendered:
    auto renderer = Renderer(component, [&] {
        return vbox({
                   hbox(text(" New Login : "), input_login->Render()),
                   hbox(text(" New Password : "), input_password->Render()),
                   hbox(text(" Repeat Password : "), input_repeated_password->Render()),
            }) |
            border;
        });

    auto screen = ScreenInteractive::TerminalOutput();
    renderer |= CatchEvent([&](Event event) {
        if (event == Event::Return)
        {
            screen.ExitLoopClosure()();
            return true;
        }
        return false;
        });

    screen.Loop(renderer);

    string file_path = "accounts\\" + temp_user_login + ".txt";

    if (filesystem::exists(file_path) == true)
    {
        cout << "\n\nlogin already in use\n\n";
        return false;
    }
    else if (repeated_password != temp_user_password)
    {
        cout << "\n\n" << "inputed different passwords" << "\n\n";
        return false;
    }
    else
    {
        
        user_login = temp_user_login;
        user_password = temp_user_password;
        return true;

    }
}

void New_account_menu::create_new_file()
{
    ofstream new_account_file("accounts\\" + user_login + ".txt");
    new_account_file << user_password << "\n\n@\n";
    new_account_file.close();
    cout << "\n\n New account has been created\n\n";
}

New_account_menu::~New_account_menu()
{

}