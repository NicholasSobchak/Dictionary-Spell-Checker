// Fall 2025 - Dictionary/Spell Checker - Collaborative Project
#include <iostream>
#include "Dictionary.h"
using namespace std;

class Tester
{
};

int main()
{	
	Dictionary dict;
	
	dict.addWord("/.tes12t");

	// populate dictionary.txt
	dict.addWord("had");
	dict.addWord("hath");
	dict.addWord("impaired");
	dict.addWord("this");
	dict.addWord("nameless");
	dict.addWord("grace");

	
	// print dictionary.txt
	dict.dump(); // 5:25 pm (dump didn't print)
    return 0;
};
