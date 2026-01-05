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
	
	// clear dictionary.txt
	dict.eraseAll();

	// populate dictionary.txt
	dict.addWord("hath");
	dict.addWord("impaired");
	
	// print dictionary.txt
	dict.dump(); // 5:25 pm (dump didn't print)
    return 0;
};
