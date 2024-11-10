#include "Log_in_menu.h"

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

Log_in_menu::Log_in_menu()
{
    bool good_login = false;
    while (good_login==false)
    {
        good_login = check_user_data(print_log_in_menu());
    }
    User_timetable* timetable = new User_timetable(user_filepath, user_password);
    delete timetable;
}

bool Log_in_menu::check_user_data(pair<string,string> data)
{
    string login = data.first;
    string password = data.second;
    login.append(".txt");
    ifstream user_file;
    string file_path = "accounts\\";
    file_path.append(login);
    if (filesystem::exists(file_path)==false)
    {
        cout << "\n\n\nbad login\n\n\n";
        return false;
    }
    else
    {
        user_file.open(file_path, std::fstream::app);
        string password_to_check;
        getline(user_file, password_to_check);
        
        if (password == password_to_check)
        {
            cout << "\n\n\nsuccesful login\n\n\n";
            user_filepath = file_path;
            user_file.close();
            user_password = password;
            return true;
        }
        else
        {
            cout << "\n\n\nbad password\n\n\n";
            return false;
        }
       
    }

}

pair<string, string> Log_in_menu::print_log_in_menu()
{
    system("CLS");
        using namespace ftxui;

        // The data:
        std::string login;

        std::string password;


        // The basic input components:
        Component input_login = Input(&login, "login");


        // The password input component:
        InputOption password_option;
        password_option.password = true;
        Component input_password = Input(&password, "password", password_option);

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
            });

        // Tweak how the component tree is rendered:
        auto renderer = Renderer(component, [&] {
            return vbox({
                       hbox(text(" Login : "), input_login->Render()),
                       hbox(text(" Password : "), input_password->Render()),
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
        
      

        pair<string, string> login_data;
        login_data.first = login;
        login_data.second = password;
        return login_data;
}

string Log_in_menu::get_user_filepath()
{
    return user_filepath;
}

Log_in_menu::~Log_in_menu()
{

}