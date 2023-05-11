#include <iostream>
#include <string>
#include "strutils.h"


// to check whether is search string is appropriate or not, returns true if appropriate
bool searchCheck(string s)
{
	int k = s.length();
	string substring;
	string s2 = LowerString(s);

	if (s2 == "quit")
		return true;
	if (k == 0) // if length of the search string is 0 return false
	{
		return false;
	}
	else
	{
		if (s[k - 1] != '*' && s[k - 1] != '+' && s[k - 1] != '.') // check if they end with appropriate character or not
		{
			return false;
		}
		else
		{
			if (s[k - 1] == '*' && s[k - 2] == '*') //if search string ends with '*' check whether second last char is '*' or not
				substring = s.substr(0, k - 2);
			else
				substring = s.substr(0, k - 1);
		}
	}

	if (substring.length() == 0)// if length of the substring is 0 return false
		return false;
	for (unsigned int i = 0; i < substring.length(); i++)
	{
		if (!isalpha(substring.at(i))) // if any of the characters in substring is not alphabtic return false
			return false;
	}

	return true;

}

// to check whether string including only aplha, digit and space
bool sourceCheck(string s)
{
	int len = s.length() - 3; //ignore end because we 
	int i = 0;

	while (i < len)
	{
		if (!isalpha(s[i]) && !isdigit(s[i]) && s[i] != ' ') // to check every char in the source string is digit, alpha or space
			return false;
		i++;
	}
	return true;
}

// operation functions while loop do not work properly maybe use continue
void firstOperation(string source, string search)
{
	int ind = 0, start_ind, end_ind;
	string word;
	search = search.substr(0, search.length() - 1);
	ind = source.find(search, ind);
	while (ind != string::npos)
	{
		start_ind = source.rfind(' ', ind);
		
		if (start_ind + 1 == ind)
		{
			end_ind = source.find(' ', ind);
			word = source.substr(ind, (end_ind - ind));
			cout << "index: " << ind << " word: " << word << endl;
		}
		ind = source.find(search, ind + 1);
	}
}

void secondOperation(string source, string search)
{
	int ind = 0, start_ind, end_ind;
	string word;
	search = search.substr(0, search.length() - 1);
	ind = source.find(search, ind);
	while (ind != string::npos)
	{
		
		end_ind = source.find(' ', ind);
		if (end_ind == ind + search.length())
		{
			start_ind = source.rfind(' ', ind);
			int len = end_ind - (start_ind + 1);
			word = source.substr(start_ind + 1, len);
			cout << "index: " << ind << " word: " << word << endl;
		}
		ind = source.find(search, ind + 1);
	}
}

void thirdOperation(string source, string search)
{
	int ind = 0, start_ind, end_ind;
	string word;
	search = search.substr(0, search.length() - 1);
	ind = source.find(search, ind);
	while (ind != string::npos)
	{
		start_ind = source.rfind(' ', ind);
		end_ind = source.find(' ', ind);
		if ((source.substr(start_ind + 1, search.length()) != search) && (source.substr(end_ind - search.length(), search.length()) != search) && (start_ind + 1 != ind) && (ind + search.length() != end_ind))
		{
			int len = end_ind - (start_ind + 1);
			word = source.substr(start_ind + 1, len);
			cout << "index: " << ind << " word: " << word << endl;
		}
		ind = source.find(search, ind + 1);
	}
}

void fourthOperation(string source, string search) 
{
	int ind = 0, start_ind, end_ind;
	string word;
	search = search.substr(0, search.length() - 2);
	ind = source.find(search, ind);
	while (ind != string::npos)
	{
		start_ind = source.rfind(' ', ind);
		end_ind = source.find(' ', ind);

		int len = end_ind - (start_ind + 1);
		word = source.substr(start_ind + 1, len);
		cout << "index: " << ind << " word: " << word << endl;

		ind = source.find(search, ind + 1);
	}
}

// to determine which type of process will be followed and display it
void operationDisplayer(string source, string search)
{
	if (search.at(search.length() - 1) == '+') {// means that search string must be beginning of the word
		firstOperation(source, search);
	}
	else if (search.at(search.length() - 1) == '.') { // means that search string must be end of the word
		secondOperation(source, search);
	}
	else if (search.at(search.length() - 1) == '*')
	{
		if (search.at(search.length() - 2) == '*') {
			fourthOperation(source, search);
		}
		else {
			thirdOperation(source, search);
		}
	}
}

void inputSource(string& source) {
	cout << "Enter source string: ";
	bool check = true;
	string word = "";
	source = "";
	while (check) {
		cin >> word;
		source += word + ' ';
		if (LowerString(word) == "end")
			check = false;
	}
	
}

int main() {
	string source = "", search = "";
	do {
		inputSource(source);
	} while (!sourceCheck(source));


	bool end = true;
	while (end)
	{
		do {
			cout << "Enter search string: ";
			cin >> search;
			if (LowerString(search) == "quit") {
				end = false;
			}
		} while (!searchCheck(search));

		operationDisplayer(source, search);
	}
	return 0;
}
