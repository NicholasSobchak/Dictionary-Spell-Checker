#include "Dictionary.h"
#include <fstream>
// implement Trie class here
Trie::Trie() : m_root(new TrieNode()) {}

Trie::~Trie() { deleteTrie(m_root); }

bool Trie::insert(const string &word)
{
    TrieNode *current = m_root;
    for (int i = 0; i < int(word.length()); ++i)
    {
		char letter = word[i];
        int index = letter - 'a'; // general online formula to get the numeric index - (uses ASCII value),(0-based indexing)
        // check if there is an existing child node
        if (!current->m_children[index])
        {
            current->m_children[index] = new TrieNode(); // create new child node

            // check if the current letter is the end of the word
            if (i == int(word.length() - 1))
            {
                current->m_isEndOfWord = true;
                current->m_word = word;
            }
        }

        current = current->m_children[index];
    }
    return current->m_isEndOfWord;
}

bool Trie::contains(const string &word)
{
	return false; // implement
}

/*********************************
// Trie Helper Functions
*********************************/
void Trie::deleteTrie(TrieNode *node)
{
	if (!node)
		return;

	for (int i = 0; i < 26; ++i)
	{
		deleteTrie(node->m_children[i]);
	}
	
	delete node;
}

// implement dictionary class here
Dictionary::Dictionary() {}

Dictionary::~Dictionary() {}

void Dictionary::loadFromFile(const string &filename)
{
	/*
	   compatible file type:
        .txt
        .csv
        .tsv
        .json
        .xml
    */
	// parse filename
	size_t p = filename.find_last_of('.');
	string extension = "";

	if (p == string::npos) cout << "file has no extension!" << endl;
	else extension = filename.substr(p);

	// control file calls
	if (extension == ".txt") 
		opentxt(filename); // .txt
	
	if (extension == ".csv") 
		opencsv(filename); // .csv
	
	if (extension == ".tsv") 
		opentsv(filename); // .tsv
	
	if (extension == ".json") 
		openjson(filename); // .json
	
	if (extension == ".xml") 
		openxml(filename); // .xml
	
	else cout << "file extension not recognized!" << endl;
}

bool Dictionary::addWord(const string &word)
{
	string cleanWord = normalize(word);
	if(!cleanWord.empty())
	   return false;

	if(m_trie.contains(cleanWord))
		return false;

	m_trie.insert(cleanWord);
	

	return true;	
}

void printDictionary()
{
    // implement DFS traversal
}

void deleteDictionary()
{
}

/*********************************
// Dictionary Helper Functions
**********************************/
string Dictionary::normalize(const string &word) const {
	string cleanWord = word;
	for (int i = 0; i < int(cleanWord.length()); ++i)
	{
		if (!isalpha(cleanWord[i]))
			continue;

		char letter = tolower(cleanWord[i]);
		cleanWord += letter;
	}
	return cleanWord;
}

bool Dictionary::opentxt(const string &filename) // open .txt file
{
    // open file
    ifstream file(filename);
    if (!file.is_open())
    {
        throw runtime_error("Error: Cannot open file!");
        return false;
    }

    // parse basic .txt using lambda
    string word;
    while (file >> word)
    {
        /*
        lambda always has the following structure in C++:

            [capture-clause] (parameters) mutable/noexcept -> return-type { function body }

        The first lambda returns a boolean that will determine if the character will be removed from the word using remove_if & erase()
        The second lambda returns the lowercase version of the character c and uses the transform method that assigns the returns lambda value back into the string
        */

        // remove non char (uses lambda function)
        word.erase(remove_if(word.begin(), word.end(), [](unsigned char c)
                             { return !isalpha(c); }),
                   word.end());

        // make lowercase (uses lambda function) (see C++ documentation for transform())
        transform(word.begin(), word.end(), word.begin(), [](unsigned char c)
                  { return tolower(c); });

        // is word empty after processing?
        if (word.empty())
            continue;

        addWord(word); // add word to trie data structure
    }

    file.close();
    return true;
}

bool Dictionary::opencsv(const string &filename)
{
    // open file
    ifstream file(filename);
	if (!file.is_open())
    {
       	throw runtime_error("Error: Cannot open file!");
		return false;
    }

    // parse using stringstream??
   	string key, value;	

	// if key == word

	return true;
}

bool Dictionary::opentsv(const string &filename)                                
{
	// open file
	ifstream file(filename);
	if (!file.is_open())
	{
		throw runtime_error("Error: Cannot open file!");
		return false;
	}
	
	// parse
	string key, value;
	
	// if key == word

	return true;
}

bool Dictionary::openjson(const string &filename)
{
	return true;
}

bool Dictionary::openxml(const string &filename)
{
	return true;
}
