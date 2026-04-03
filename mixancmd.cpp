// DEPENDENCIES AND STUFF
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <thread>
#include <chrono>
#include <map>
#include <cctype>
#ifdef _WIN32
#include <Windows.h>
#endif
using namespace std;
map<string, string> variables;

// FUNCTIONS
void sleepMs(int ms)
{
#ifdef _WIN32
    Sleep(ms);
#else
    this_thread::sleep_for(chrono::milliseconds(ms));
#endif
}

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void typeLine(const string& text)
{
    for (char c : text)
    {
        cout << c;
        sleepMs(30);
    }
    cout << endl;
}

string getRestOfLine(stringstream& ss)
{
    string msg;
    getline(ss, msg);

    if (!msg.empty() && msg[0] == ' ')
        msg.erase(0, 1);

    return msg;
}

string expandVariables(const string& input)
{
    string result;
    for (size_t i = 0; i < input.size(); i++)
    {
        if (input[i] == '%' && i + 1 < input.size())
        {
            string name;
            i++;

            while (i < input.size() && (isalnum(input[i]) || input[i] == '_'))
            {
                name += input[i];
                i++;
            }
            i--;

            if (variables.count(name))
                result += variables[name];
            else
                result += "%" + name;
        }
        else
        {
            result += input[i];
        }
    }
    return result;
}

// COMMANDS
void cmd_add(stringstream& ss)
{
    float a, b;
    if (ss >> a >> b)
        cout << a + b << endl;
    else
        cout << "Syntax error (err_01)" << endl;
}

void cmd_sub(stringstream& ss)
{
    float a, b;
    if (ss >> a >> b)
        cout << a - b << endl;
    else
        cout << "Syntax error (err_01)" << endl;
}

void cmd_mul(stringstream& ss)
{
    float a, b;
    if (ss >> a >> b)
        cout << a * b << endl;
    else
        cout << "Syntax error (err_01)" << endl;
}

void cmd_div(stringstream& ss)
{
    float a, b;
    if (ss >> a >> b)
    {
        if (b == 0)
            cout << "Division by zero error (err_00)" << endl;
        else
            cout << a / b << endl;
    }
    else
        cout << "Syntax error (err_01)" << endl;
}

void cmd_pow(stringstream& ss)
{
    float a, b;
    if (ss >> a >> b)
        cout << pow(a, b) << endl;
    else
        cout << "Syntax error (err_01)" << endl;
}

void cmd_sqrt(stringstream& ss)
{
    float a;
    if (ss >> a)
    {
        if (a < 0)
            cout << "Negative square root (err_03)" << endl;
        else
            cout << sqrt(a) << endl;
    }
    else
        cout << "Syntax error (err_01)" << endl;
}

void cmd_echo(stringstream& ss)
{
    cout << getRestOfLine(ss) << endl;
}

void cmd_type(stringstream& ss)
{
    typeLine(getRestOfLine(ss));
}

void cmd_set(stringstream& ss)
{
    string type, name, value;

    if (ss >> type >> name)
    {
        getline(ss, value);
        if (!value.empty() && value[0] == ' ')
            value.erase(0, 1);

        variables[name] = value;
    }
    else
        cout << "Syntax error (err_01)" << endl;
}

void cmd_get(stringstream& ss)
{
    string name;
    if (ss >> name)
    {
        if (variables.count(name))
            cout << variables[name] << endl;
        else
            cout << "Variable not found (err_04)" << endl;
    }
    else
        cout << "Syntax error (err_01)" << endl;
}

void cmd_list()
{
    if (variables.empty())
    {
        cout << "No variables stored." << endl;
        return;
    }

    for (const auto& v : variables)
    {
        cout << v.first << " = " << v.second << endl;
    }
}

void cmd_forget(stringstream& ss)
{
    string name;
    if (ss >> name)
    {
        if (variables.erase(name))
            cout << "Forgot: " << name << endl;
        else
            cout << "Variable not found (err_04)" << endl;
    }
    else
        cout << "Syntax error (err_01)" << endl;
}

void cmd_rickroll()
{
    typeLine("Never gonna give you up");
    sleepMs(1000);
    typeLine("Never gonna let you down");
    sleepMs(1000);
    typeLine("Never gonna run around and desert you");
    sleepMs(1000);
    typeLine("Never gonna make you cry");
    sleepMs(1000);
    typeLine("Never gonna say goodbye");
    sleepMs(1000);
    typeLine("Never gonna tell a lie...");
    sleepMs(1000);
    typeLine("...and hurt you");
    sleepMs(1000);
}

// MAIN
int main()
{
    string fullcmd;
    bool running = true;

    cout << "MixanCMD (1.0)" << endl;

    // For mod makers its recommended not to delete the line above.
    // To make your mod distinguishable you can use the template line below.
    // cout << "MyMod (ModVersion)" << endl;
    // Anyways happy modding!

    cout << endl;

    while (running)
    {
        cout << "> ";
        getline(cin, fullcmd);
        fullcmd = expandVariables(fullcmd);
        stringstream ss(fullcmd);

        string cmd;
        ss >> cmd;

        if (cmd.empty())
            continue;

        if (cmd == "help")
        {
            string cmdname;
            if (ss >> cmdname)
            {
                if (cmdname == "help")
                {
                    cout << "Tells you more about what the functions do." << endl;
                    cout << "Can also tell you more about 1 command of your choice (e.g. help add)." << endl;
                }
                else if (cmdname == "exit")
                {
                    cout << "Exits the console." << endl;
                }
                else if (cmdname == "clear")
                {
                    cout << "Clears the text from the console." << endl;
                }
                else if (cmdname == "add")
                {
                    cout << "Simple addition (+) command, used like so:" << endl;
                    cout << "add 10 2" << endl;
                    cout << "That command executes 10 + 2 = 12, so the output should be 12." << endl;
                }
                else if (cmdname == "sub")
                {
                    cout << "Simple subtraction (-) command, used like so:" << endl;
                    cout << "sub 10 2" << endl;
                    cout << "That command executes 10 - 2 = 8, so the output should be 8." << endl;
                }
                else if (cmdname == "mul")
                {
                    cout << "Simple multiplication (*) command, used like so:" << endl;
                    cout << "mul 10 2" << endl;
                    cout << "That command executes 10 * 2 = 20, so the output should be 20." << endl;
                }
                else if (cmdname == "div")
                {
                    cout << "Simple division (/) command, used like so:" << endl;
                    cout << "div 10 2" << endl;
                    cout << "That command executes 10 / 2 = 5, so the output should be 5." << endl;
                    cout << "Division by zero sends an error message." << endl;
                }
                else if (cmdname == "pow")
                {
                    cout << "Simple power (^) command, used like so:" << endl;
                    cout << "pow 10 2" << endl;
                    cout << "That command executes 10 ^ 2 = 100, so the output should be 100." << endl;
                }
                else if (cmdname == "sqrt")
                {
                    cout << "Simple square root command, used like so:" << endl;
                    cout << "sqrt 9" << endl;
                    cout << "That command executes sqrt(9) = 3, so the output should be 3." << endl;
                    cout << "Putting negative numbers in the square root sends an error message." << endl;
                }
                else if (cmdname == "echo")
                {
                    cout << "This command repeats the message that you wrote with it." << endl;
                    cout << "(e.g. echo Hello world!, the output should be 'Hello world!'." << endl;
                    cout << "This command supports multi-word sentences." << endl;
                }
                else if (cmdname == "type")
                {
                    cout << "This command works almost the same as echo." << endl;
                    cout << "(For more info about echo type 'help echo')" << endl;
                    cout << "It just adds a delay between the letters appearing" << endl;
                }
                else if (cmdname == "set")
                {
                    cout << "Assings a value to a specific name." << endl;
                    cout << "The value can be an int, float, double, string or char." << endl;
                    cout << "set [type] [name] [value]" << endl;
                    cout << "For variable usage you need to put a % infront of the variable's name." << endl;
                    cout << "e.g. echo %message" << endl;
                }
                else if (cmdname == "get")
                {
                    cout << "get [name]" << endl;
                    cout << "Prints the value of a variable." << endl;
                }
                else if (cmdname == "list")
                {
                    cout << "list" << endl;
                    cout << "Shows all stored variables." << endl;
                }
                else if (cmdname == "forget")
                {
                    cout << "forget [name]" << endl;
                    cout << "Deletes a variable from memory." << endl;
                }
                else
                {
                    cout << "Invalid argument (err_02)" << endl;
                }
            }
            else
            {
                cout << "Use help [cmd name] for more information about a specific function." << endl;
                cout << "Here's a list of available functions:" << endl;
                cout << "help, exit, clear, add, sub, mul, div, pow, sqrt, echo, type, set, get, list, forget" << endl;
            }
        }
        else if (cmd == "exit")
        {
            running = false;
        }
        else if (cmd == "clear")
        {
            clearScreen();
        }
        else if (cmd == "add") cmd_add(ss);
        else if (cmd == "sub") cmd_sub(ss);
        else if (cmd == "mul") cmd_mul(ss);
        else if (cmd == "div") cmd_div(ss);
        else if (cmd == "pow") cmd_pow(ss);
        else if (cmd == "sqrt") cmd_sqrt(ss);
        else if (cmd == "echo") cmd_echo(ss);
        else if (cmd == "type") cmd_type(ss);
        else if (cmd == "set") cmd_set(ss);
        else if (cmd == "get") cmd_get(ss);
        else if (cmd == "list") cmd_list();
        else if (cmd == "forget") cmd_forget(ss);
        else if (cmd == "rickroll") cmd_rickroll();
        else
        {
            cout << "Syntax error! (err_01)" << endl;
        }
    }

    clearScreen();
    cout << "Shutting down..." << endl;
    sleepMs(1000);

    return 0;
}