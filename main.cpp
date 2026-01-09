// Fall 2025 - Dictionary/Spell Checker - Collaborative Project
#include "Dictionary.h"
#include <string_view>
#include <iostream>
using namespace std;

class Tester
{
};

int main()
{	
	Dictionary dict;
	
	dict.eraseAll();

	dict.addWord("had");
	dict.addWord("hath");
	
	cout << "--- After adding had and hath ---" << endl;
	dict.debug();
	dict.dump();

	cout << "--- Remove tress ---" << endl;
	dict.removeWord("tress");
	dict.debug();
	dict.dump();

	dict.removeWord("had");
	cout << "\n--- After removing had ---" << endl;
	dict.debug();
	dict.dump();

	dict.removeWord("hath");
	cout << "\n--- After removing hath ---" << endl;
	dict.debug();
	dict.dump();

	
    return 0;
};
