#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cctype>
using namespace std;

int main()
{
	ifstream readFile;
	vector<string> words;
	vector<string> nums;

	readFile.open("words.txt");

	if (readFile.is_open())
	{
		while (!readFile.eof())
		{
			string str;
			getline(readFile, str);
			cout << str << endl;

			char* str_buff = new char[1000];
			strcpy(str_buff, str.c_str());

			char* tok = strtok(str_buff, " ");
			while (tok != nullptr) {
				words.emplace_back(string(tok));
				tok = strtok(nullptr, " ");
			}
		}
	}
	readFile.close();

	for (int i = 0; i < words.size(); ++i)
	{
		char* word_buff = new char[1000];
		int wordLen;
		bool isDigit = false;
		strcpy(word_buff, words[i].c_str());

		wordLen = strlen(word_buff);
		
		for (int o = 0; o < wordLen; ++o)
		{
			if (isdigit(word_buff[o]) != 0)
				isDigit = true;
		}

		if (isDigit == true)
			nums.push_back(words[i]);
	}

	cout << "단어 숫자 = " << words.size() << endl;
	cout << "숫자 숫자 = " << nums.size() << endl;

	for (int i = 0; i < nums.size(); ++i)
	{
		cout << nums[i] << endl;
	}
	
}