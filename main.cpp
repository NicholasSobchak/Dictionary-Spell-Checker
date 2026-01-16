// Fall 2025 - Dictionary/Spell Checker - Collaborative Project
#include "Dictionary.h"
using namespace std;

class Tester
{
};

int main()
{
    Dictionary dict;

    dict.eraseAll();

    // Load dictionary from JSON file
    cout << "Loading dictionary from nlohmann/words_dictionary.json..." << endl;
    if (dict.openjson("nlohmann/words_dictionary.json")) { cout << "Dictionary loaded successfully!" << endl; }
    else { cout << "Failed to load dictionary from JSON." << endl; }
	
	// test dictionary
    cout << "\n--- Checking for some words from words_dictionary.json ---" << endl;
    if (dict.search("nameless")) { cout << "'nameless' found in dictionary." << endl; }
    else { cout << "'nameless' not found in dictionary." << endl; }

    if (dict.search("grace")) { cout << "'grace' found in dictionary." << endl; }
    else { cout << "'grace' not found in dictionary." << endl; }
    
    if (dict.search("impaired")) { cout << "'impaired' found in dictionary." << endl; }
    else { cout << "'impaired' not found in dictionary." << endl; }

#if 0 
    // Original test code below this point
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
#endif
    
    return 0;
}
