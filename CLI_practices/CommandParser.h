#pragma once
#include <string>
#include <vector>
using namespace std;



struct lexeme {
	enum type { error = -1 , command, command_value, message };
	type  lexeme_type;
	string value;
};



class CommandParser
{
public:

	
	vector<lexeme> parse(string command);

	

};

