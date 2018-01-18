#pragma once
#include<iostream>
#include<vector>
#include<string>
using std::vector;
using std::string;
class ParseString
{
public:
	ParseString() {}
	vector<string> parse(string str) {
		vector<string> v;
		string s;
		char c = ' ';
		for (auto it : str) {
			if (it != ' ')
			{
				s.push_back(it);
			}
			else if (it == '\0') {
				v.push_back(s);
			}
			else if(it == ' ' && c != ' '){
				v.push_back(s);
				s.clear();
			}
			c = it;
		}
		v.push_back(s);
		return v;
	}
};

