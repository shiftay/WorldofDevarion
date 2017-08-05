//-----------------------------------------------------------------------------
// MSConsole - Declaration and Implementation {Static Object}
//-----------------------------------------------------------------------------
// Created: 2016-08-30 : 1:35PM EST
// LastUpdate:
// Revision: 1
// Version 1.0.0
//-----------------------------------------------------------------------------
// Author: Stephen Roebuck
// Contact: @shiftay416 | shroebuck@gmail.com
//-----------------------------------------------------------------------------
// Provides usefull behaviors for dealing with the Windows console.
//-----------------------------------------------------------------------------
#pragma once
#define NOMINMAX
//-----------------------------------------------------------------------------
// Preferred order of Includes (Local to Global)
//-----------------------------------------------------------------------------
// 1. include corresponding h to this cpp (IF applicable)
// 2. include header files from current project
// 3. include header files from other non-standard, non-system libraries(SDL2)
// 4. Headers from "almost-standard" Libraries (Boost)
// 5. include standard C++ headers (eg. #include<iostream>)
// 6. include standard C headers (eg. #include<iostream>)
//-----------------------------------------------------------------------------
#include <Windows.h> // WinAPI header file
#include <iostream>
#include <sstream>
#include <string>
#include <limits>

// Using Directives
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::numeric_limits;
using std::streamsize;
using std::stringstream;

// NAMESPACE: ConsoleColor
// C++ Namespaces MSDN Article: http:///msdn.microsoft.com/en-CA/library/5cb46ksf.aspx
namespace ConsoleColor
{
	enum
	{
		BLACK = 0,
		DARKBLUE = FOREGROUND_BLUE,
		DARKGREEN = FOREGROUND_GREEN,
		DARKCYAN = FOREGROUND_GREEN | FOREGROUND_BLUE,
		DARKRED = FOREGROUND_RED,
		DARKMAGENTA = FOREGROUND_RED | FOREGROUND_BLUE,
		DARKYELLOW = FOREGROUND_RED | FOREGROUND_GREEN,
		DARKGRAY = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		GRAY = FOREGROUND_INTENSITY,
		BLUE = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
		GREEN = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
		CYAN = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
		RED = FOREGROUND_INTENSITY | FOREGROUND_RED,
		MAGENTA = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
		YELLOW = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
		WHITE = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	};
}

class MSConsole
{
public:
	static void Output(const string& outputValue)
	{
		cout << outputValue;
	}

	static void SetConsoleSizeMAX()
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		_CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(hConsole, &info);

		SMALL_RECT windowMaxSize = { 0, 0, info.dwMaximumWindowSize.X - 1, info.dwMaximumWindowSize.Y - 1 };
		SetConsoleWindowInfo(hConsole, TRUE, &windowMaxSize);
	}

	static void SetTextColor(int newValue)
	{
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, newValue);
	}

	static void GoTo(int x, int y)
	{
		COORD position = { x, y };
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		SetConsoleCursorPosition(hConsole, position);
	}

	static int GetKeyboardInput_int()
	{
		int user_input = -20160811;
		do
		{
			cin >> user_input;

			if (!cin)
			{
				MSConsole::Output("NaN Error @ ConsoleUtil::getIntInput() -- cin error");
				MSConsole::Output("\nOnly Numeric Value Allowed!");
				MSConsole::Output("Try again: ");

				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

		} while (user_input == -20160811);

		return user_input;
	}

	static string GetKeyboardInput_str()
	{
		string user_input;

		while (user_input.empty())
		{
			if (!getline(cin, user_input))
			{
				MSConsole::SetTextColor(ConsoleColor::GREEN);
				MSConsole::Output("DEBUG_INFO: Error @ ConsoleUtil::getStrInput() with cin obj");
				MSConsole::SetTextColor(ConsoleColor::WHITE);
			}
			else
			{
				return user_input;
			}
		}

		return user_input;
	}
};