#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <unordered_map>
using namespace std;

string name_of_dict = "dict";

//checking if the word is in the dictionary
bool check_dict(string word, string current_word, unordered_map<string,int>& dict)
{
	dict.erase(current_word);		//temporarily delete word from dict to search for other words.
	std::unordered_map<std::string,int>::const_iterator got = dict.find (word);
	if ( got == dict.end() )		//word not found
	{
		dict.insert ( std::pair<string,int>(current_word, 0) );
		return false;
	}
	else					//word found
	{
		dict.insert ( std::pair<string,int>(current_word, 0) );
		return true;
	}
}

//breaking the word into pieces and checking
bool break_word(string &current_word, unordered_map<string,int>& dict)
{
	int size = current_word.size();			//store size of word as it will chance later on
	if (size == 0)					//base case
		return true;

	/* structure to maintian prefixes */
	bool dptable[size+1];
	for (int i = 1; i <= size; i++)			//initialize all to false
		dptable[i] = false;

	for (int i = 1; i < size; i++)
	{
		if (dptable[i] == false)
			if (check_dict(current_word.substr(0, i), current_word, dict))
				dptable[i] = true;

		if (dptable[i] == true)
		{
			if (i == size)			//reached the last prefix
				return true;

			for (int j = i+1; j <= size; j++)
			{
				if (dptable[j] == false)
					if (check_dict(current_word.substr(i, j-1), current_word, dict))
						dptable[j] = true;

				if (j == size)
					if (dptable[j] == true)
						return true;
			}
		}
	}

	return false;
}

int main(int argc, char* argv[])
{
	/* file input */
	name_of_dict = (string) argv[1];
	ifstream inFile;
	inFile.open(name_of_dict.c_str());

	/* variable declaration */
	string current_word;				//current word in dict being checked
	string final_word;				//answer
	int longest_word_length = 0;			//length of word to check the biggest length
	int i = 0;

	/* filling in the hash map s*/
	unordered_map<string,int> dict;
	while (!inFile.eof())
	{
		getline(inFile, current_word);		//take current_word from dict
		dict.insert ( std::pair<string,int>(current_word,i++) );
	}
	inFile.close();

	/* searching though all words through file */
	inFile.open(name_of_dict.c_str());
	while (!inFile.eof())
	{
		getline(inFile, current_word);			//take current_word from dict
		bool flag = break_word(current_word, dict);	//check if it is compound word
		if (flag == 1)					//if it is then check for length and decide answer
		{
			if (current_word.length() > longest_word_length)
				final_word = current_word;
				longest_word_length = final_word.length();	
		}
	}

	/* final answer */
	cout << "final_word is: " << final_word << "   and length is :" << longest_word_length << endl;
	inFile.close();

	/* print out contents of hash map */
//	for ( auto& x: dict )
//		std::cout << x.first << ": " << x.second << std::endl;
	
	return 0;
}
