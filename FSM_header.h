#ifndef FSM_HEADER_H
#define FSM_HEADER_H
#include"LList.h"


enum state {
	Match, NotMatch, Star, Dot
};

class Finite_state_machine
{
private:
	string pattern;
	fstream myfile;
	string filename;
	SLL wordlist;
	int count;

public:


	void get_filename(string file_name)
	{
		this->filename = file_name;
		filename = filename + ".txt";
	}

	//main function for solving expression matching
	void regex(string pattern1)
	{
		string word_from_file;
		this->pattern = pattern1;
		count = 0;

		//FILING WORK

		myfile.open(filename.c_str(), ios::in);

		if (myfile.is_open() == 0)
		{
			cout << "FILE COULD NOT BE OPPENED\n";
			exit(1);
		}

		clock_t time_req;
		time_req = clock();

		while (!myfile.eof())
		{
			getline(myfile, word_from_file);
			int result = stringmatch(word_from_file, pattern);
			if (result == 1)		//pattern founc
			{
				count++;
				wordlist.add_to_tail(word_from_file);
			}
		}
		myfile.close();
		cout << endl << "Results Found: " << count << endl;
		time_req = clock() - time_req;
		cout << "All wwords Loaded in " << (float)time_req / CLOCKS_PER_SEC << " seconds" << endl << endl;
		wordlist.print();		//print all words that matches the expression
	}

	//function to match the string taken from file and pattern entered by user	
	int stringmatch(string a, string b) {

		state currentState = Match;				//initialise finite state machiene using enums
		int i = 0, j = 0;

		while (1)
		{
			switch (currentState)
			{


			case Match:													//if both the strings have same character
				if (i == a.length() && j == b.length()) { return 1; }
				if (a[i] == b[j]) { i++; j++; currentState = Match; }
				else if (b[j] == '*') { j++; currentState = Star; }
				else if (b[j] == '.') { i++; j++; currentState = Dot; }
				else { currentState = NotMatch; }
				break;


			case NotMatch:												//if characters dont match
				return 0;												// match not found, move to another string
				break;


			case Star:													//if pattern has star


				while (1)
				{
					if (j > b.length() - 1 && i <= a.length()) { return 1; }			//if both the strings have reached end point

					while (b[j] != a[i] && i <= a.length() - 1)						//Till string's character matches the pattern's character after *
					{
						i++;
					}

					if (i == a.length() - 1 || b[j + 1] == '*' || b[j + 1] == '.') { break; }			//if string has reached its end, or next character of pattern is * or .

					while (a[i + 1] != b[j + 1] && i <= a.length())					//till next character of string and pattern matches
					{
						i++;
					}

					if (i > a.length()) { break; }								//if string has reached its endpoint

					int  starflag = 0, lenb = 0, x;

					for (x = j; x < b.length(); x++)								//to check if pattern has any other *'s
					{
						if (b[x] == '*') { starflag = 1; break; }
						else { lenb++; }
					}
					int lena = a.length() - i - 1;

					//if pattern has star and pattern and string match and next characters of pattern and string matches
					//OR
					//if pattern has no star and length of string is greater than pattern length

					if ((starflag == 1 && a[x] == b[j] && a[x + 1] == b[j + 1]) || (starflag == 0 && lena > lenb)) { i++; continue; }
					else
					{
						break;
					}
				}

				if (i == a.length() && j == b.length()) { return 1; }
				if (a[i] == b[j]) { i++; j++; currentState = Match; }
				else { currentState = NotMatch; }
				break;



			case Dot:														//if pattern has . as its character
				if (i == a.length() && j == b.length()) { return 1; }
				if (a[i] == b[j]) { i++; j++; currentState = Match; }
				else if (b[j] == '*') { j++; currentState = Star; }
				else if (b[j] == '.') { i++; j++; currentState = Dot; }
				else { currentState = NotMatch; }
				break;

			default:
				break;
			}

		}
	}
};


void welcome_screen()
{
	int num, flag = 1;
	string pattern;
	string answer;
	cout << "\nWelcome!\n";
	while (flag == 1)
	{

		cout << "\nPlease enter the option no. ('1','2' or '3') you want to search the pattern from:\n";
		cout << "1. Names\n2. English Dictionary\n3. Custom\n";

		Finite_state_machine fsm;
		cin >> num;

		if (num == 1)
		{
			fsm.get_filename("names");
		}

		else if (num == 2)
		{
			fsm.get_filename("english");
		}

		else if (num == 3)
		{
			fsm.get_filename("sample");
		}
		else
		{
			std::cout << "Error! Please enter valid option!";
			flag = 1;
			continue;
		}
		cout << "\nPlease enter the string pattern:\n'*' Indicates String Of Any Length\n'.' Indicates A Single Character\n";
		cin >> pattern;
		fsm.regex(pattern);

		cout << endl << endl << "\nDo you want to search again ? (yes/no)\n";
		cin >> answer;
		if (answer == "yes")
		{
			flag = 1;
			system("CLS");
		}
		else if (answer == "no")
		{
			flag = 0;
		}
	}
}

#endif
