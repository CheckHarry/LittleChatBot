#include "CommandParser.h"
#include <iostream>








vector<lexeme> CommandParser::parse(string command) {
	char cur = 0;
	string temp = "";
	vector<lexeme> to_return;
	int state = 0;
	string::iterator tempit;
	for (string::iterator it = command.begin(); it != command.end();it++) {
		switch (state)
		{
		case 0:
			if (*it != ' ') {
				if (*it == '\\') state = 1;
				else { 
					state = 2; 
					temp += *it;
					string::iterator tempit = it;
					tempit++;
					if (tempit == command.end()){
					lexeme message;
					message.lexeme_type = message.message;
					message.value = temp;
					to_return.push_back(message);
					}
				}
			}
			break;
		case 1:
			if (97 <= *it && *it <= 122) temp += *it;
			else if (*it == ' ') {
				state = 3; 
				lexeme command;
				command.lexeme_type = command.command;
				command.value = temp;
				temp = "";
				to_return.push_back(command);
			}
			else {
				lexeme error;
				error.lexeme_type = error.error;
				cout << "Command including invalid character ! \n";
				return vector<lexeme>{error};
			}
			tempit = it;
			tempit++;
			if (tempit == command.end()) {
				lexeme command;
				command.lexeme_type = command.command;
				command.value = temp;
				temp = "";
				to_return.push_back(command);
			}
			break;
		case 2:
			temp += *it;
			tempit = it;
			tempit++;
			if (tempit == command.end()) {
				lexeme message;
				message.lexeme_type = message.message;
				message.value = temp;
				temp = "";
				to_return.push_back(message);
			}
			break;
		case 3:
			if (*it != ' ') {
				temp += *it;
				state = 4;
			}
			break;
		case 4:
			if (*it == ' ') {
				lexeme value;
				value.lexeme_type = value.command_value;
				value.value = temp;
				temp = "";
				to_return.push_back(value);
				state = 3;
				break;
			}
			temp += *it;
			tempit = it;
			tempit++;
			if (tempit == command.end()) {
				lexeme value;
				value.lexeme_type = value.command_value;
				value.value = temp;
				temp = "";
				to_return.push_back(value);
			}
			break;
		default:
			break;
		}
	}
	return to_return;
}