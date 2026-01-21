// Fall 2025 - Dictionary/Spell Checker - Collaborative Project
#include "Dictionary.h"
using namespace std;

class Tester
{
};

int main()
{
    Dictionary dict;

	dict.eraseAll(); // for testing purposes
	cout << (dict.isEmpty() ? "Dictionary empty" : "Dictionary not empty") << '\n' << endl;

#if 1 
    // Load dictionary from JSON file
    cout << "Loading dictionary from nlohmann/words_dictionary.json..." << endl;
    if (dict.openjson("nlohmann/words_dictionary.json")) { cout << "Dictionary loaded successfully!" << endl; }
    else { cout << "Failed to load dictionary from JSON." << endl; }	
#endif

#if 0 
    // Original test code below this point
    dict.addWord("had");
	dict.addWord("hath");

    cout << "--- After adding had and hath ---" << endl;
    dict.dump();
	dict.print();

    cout << "--- Remove tress ---" << endl;
    dict.removeWord("tress");
    dict.dump();
	dict.print();

    dict.removeWord("had");
    cout << "\n--- After removing had ---" << endl;
    dict.dump();
	dict.print();

    dict.removeWord("hath");
    cout << "\n--- After removing hath ---" << endl;
    dict.dump();
	dict.print();
#endif

#if 1
	// spell checking / autofill
	SpellChecker checker(dict);
	string input;
	cout << "\nPlease enter a word: ";
	cin >> input;

    cout << "\n--- suggestions for " << "'" << input << "'" << " ---" << endl;
	checker.printSuggest(checker.suggest(input));
	dict.dumpWord(input);
#endif

	cout << '\n' << (dict.isEmpty() ? "Dictionary empty" : "Dictionary not empty") << endl;
	// dict.debug();
	// dict.dump();
	
    return 0;
}
