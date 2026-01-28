// Fall 2025 - Dictionary/Spell Checker - Collaborative Project
#include "Dictionary.h"
#include "SpellChecker.h"

class Tester
{
};

int main()
{
    Dictionary dict;
#if 1 // implement dictionary into database
	dict.eraseAll(); // for testing purposes
	std::cout << (dict.isEmpty() ? "Dictionary empty" : "Dictionary not empty") << '\n' << std::endl;

#if 0 
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
	std::string input;
	std::cout << "\nPlease enter a word: ";
	std::cin >> input;

	std::cout << "\n--- suggestions for " << "'" << input << "'" << " ---" << std::endl;
	checker.printSuggest(checker.suggest(input));
	dict.dumpWord(input);
#endif

	std::cout << '\n' << (dict.isEmpty() ? "Dictionary empty" : "Dictionary not empty") << std::endl;
	// dict.debug();
	// dict.dump();

#endif // implement database into dictionary	
    return 0;
}
