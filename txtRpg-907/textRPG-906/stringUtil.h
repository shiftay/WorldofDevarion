// 
//	String Utilities
//Used to convert for output
//As well as convert to case.
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>


using namespace std;
// Once you have implemented each method, ensure you create a main.cpp and test each function is working.
// You will need to submit both this file and the main.cpp. 

class StringUtil
{
public:
	// Param # 1
	//
	// Returns an integer representing the total number of indivudal 'words'
	// present within the string passed into it. 
	static int GetNumWords(const string& strVal)
	{
		// Implement here..
		int count = 1;

		for (int i = 0; i < strVal.length(); i++)
		{
			if (strVal[i] == ' ')
			{
				count++;
			}
		}

		return count;
	}

	// Param #1 is the string data containing words you wish to pull out
	//
	// This method returns a vector<string> where each element is populated by
	// an individual word from the string passed in (Param #1). Words are placed 
	// into the vector<string> in the same order they are encountered within the
	// string (Param #1) (assuming reading left to right)
	//
	// i.e. If I pass a string with the value of "Hello World!" a vector<string> 
	// with two elements ("Hello", "World!") is returned by this method. 
	static vector<string> GetWords(const string& strVal)
	{
		// Implement here..
		stringstream ss;
		vector<string> words;
		string holder;
		ss << strVal;
		while (getline(ss, holder, ' '))
		{
			words.push_back(holder);
		}
		return words;

	}
	// Hint: Odds are high that you will need to use 'GetNumWords' within this method to get it working


	// Param #1 is the string data to be formatted by the method
	// Param #2 is positive whole number representing the max number of characters per line.
	//
	// This functions formats string data based on a max char per line value - making it 
	// much simplier to ensure text output is formatted correctly for the console window.
	static vector<string> FormatForOutput(const string& strVal, const int intVal)
	{
		vector<string> holder = GetWords(strVal);
		int count = GetNumWords(strVal);

		for (int i = 0; i < holder.size(); i++)
		{
			if ((i + 1) % intVal == 0)
			{
				holder[i] += "\n";
			}
		}

		return holder;
	}
	// Hint: Odds are high that you will need to use 'GetNumWords' within this method  to get it working


	// ToString Conversion Methods
	static string ToString_i(int originalVal) // Takes an int value, converts to string and returns it
	{
		stringstream ss;  // Create stringstream
		ss << originalVal;	  // add value of originalVal to stringstream

		return ss.str();  // return the contents as a string stream
	}

	static string ToString_l(long originalVal)
	{
		stringstream ss;  // Create stringstream
		ss << originalVal;	  // add value of originalVal to stringstream

		return ss.str();  // return the contents as a string stream
	}

	static string ToString_f(float originalVal)
	{
		stringstream ss;  // Create stringstream
		ss << originalVal;	  // add value of originalVal to stringstream

		return ss.str();  // return the contents as a string stream
	}

	static string ToString_d(double originalVal)
	{
		stringstream ss;  // Create stringstream
		ss << originalVal;	  // add value of originalVal to stringstream

		return ss.str();  // return the contents as a string stream
	}

	static string ToString_b(bool val)
	{
		if (val == true)
			return "true";
		else
			return "false";
	}

	// StringTo Conversion Methods
	static int StringToInteger(string& strVal) // Takes an string value, converts to int and returns it
	{
		int x = 0;

		stringstream convert(strVal);
		convert >> x;

		return x;
	}

	static long StringToLong(string& strVal)
	{
		long x = 0;

		stringstream convert(strVal);
		convert >> x;

		return x;
	}

	static float StringToFloat(string& strVal)
	{
		float x = 0;

		stringstream convert(strVal);
		convert >> x;

		return x;
	}

	static double StringToDouble(string& strVal)
	{
		double x = 0;

		stringstream convert(strVal);
		convert >> x;

		return x;
	}

	static bool StringToBool(string& val)
	{
		if (val == "true")
			return true;
		else
			return false;
	}


	// Param #1 is the relative file path location of the text file
	//
	// This method attempts to load data from an external text file, store it within a string
	// and then return the string out. 
	//
	// i.e. if the text file I was trying to load was inside a folder called '_resources'
	// which itself sat within the project root directory (where the src code is saved to) 
	// and the text file itself was named 'test.txt'. You would pass in the following as a
	// const char* "_resources\\text.txt".
	static string StringFromFile(const char* fileName)
	{
		fstream strFile;
		string holder;

		strFile.open(fileName);
		while (!strFile.eof())
		{
			getline(strFile, holder);
		}
		strFile.close();

		return holder;
	}
	// Hint: Create a directory called "_resources" with your project's root directory (the location 
	// where the .h'snd .cpp's are saved). Place your test text files within. 

	static string stringToUpper(string &s)
	{
		string holder = s;

		for (unsigned int l = 0; l < s.length(); l++)
		{
			holder[l] = toupper(s[l]);
		}

		return holder;
	}
};