#include "Dictionary.h"
#include <fstream>
#include <filesystem>

// TRIE CLASS //
Trie::Trie() : m_root(new TrieNode()) {}

Trie::~Trie() { deleteTrie(m_root); }

bool Trie::insert(const string &word)
{
    TrieNode *node {m_root};

	// traverse to the last node in the word
    for (char c : word)
    {
        int index {c - 'a'}; // general online formula to get the numeric index - (uses ASCII value),(0-based indexing)
        
	 	// check if there is an existing child node
        if (!node->m_children[index]) { node->m_children[index] = new TrieNode(); }	
	    node = node->m_children[index];
    }

	// check if word is already in Trie (node is last letter of the word)
	if (node->m_isEndOfWord) return false;

	node->m_isEndOfWord = true;
    return true;
}

bool Trie::contains(const string &word) const
{
	bool found {false};
	TrieNode *node {m_root};

	// traverse to the last node in the word
	for (char letter : word)
	{
        int index {letter - 'a'};	    
	    node = node->m_children[index];	// CHECK LOGIC FOR CRASH
	}

	if (node->m_isEndOfWord) return found = true;
	return found; // word not found
}

void Trie::writeAll(std::ostream &out) const
{
	if (!out)
	{
		std::cerr << "output stream is invalid\n";
		return;
	}

	string currentWord;
	write(m_root, currentWord, out);
}

void Trie::dumpDebug() const
{
	// implement
}

void Trie::print() const { writeAll(cout); } // same as writeAll logic

/*********************************
// Trie Helper Functions
*********************************/
void Trie::deleteTrie(TrieNode *node)
{
	if (!node)
		return;
	
	// BFS
	for (int i{0}; i < 26; ++i)
	{
		deleteTrie(node->m_children[i]);
	}
	
	delete node;
}

void Trie::write(TrieNode *node, string &currentWord, std::ostream &out) const
{
	if (!node) return;

	if (node->m_isEndOfWord) out << currentWord << '\n';

	for (int i{0}; i < 26; ++i)
	{
		if (node->m_children[i])
		{
			currentWord.push_back(static_cast<char>('a' + i)); // build word that will be written to the file
			write(node->m_children[i], currentWord, out);
			currentWord.pop_back(); // backtrack
		}
	}
}

void Trie::clear()
{
	deleteTrie(m_root);
	m_root = new TrieNode();
}

// DICTIONARY CLASS //
Dictionary::Dictionary() { load(DICT); }

Dictionary::~Dictionary() 
{ 
	save(DICT); 
}

bool Dictionary::addWord(const string &word)
{
	// correct word and add it to trie
	string cleanWord {normalize(word)};
	if(cleanWord.empty()) return false;
	
	if (!m_trie.insert(cleanWord)) return false;

	return true;	
}

void Dictionary::dump() const { m_trie.print(); } 

void Dictionary::debug() const { m_trie.dumpDebug(); }

void Dictionary::loadTxt(const string &filename) { load(filename); }

/*
void Dictionary::loadInfo(const string &filename)
{

	   compatible file type:
        .csv
        .tsv
        .json
        .xml

	// parse filename
	size_t p {filename.find_last_of('.')};
	string extension {""};

	if (p == string::npos) cout << "Error: file has no extension!" << endl;
	else extension = filename.substr(p);

	// control file calls
	if (extension == ".csv") 
		opencsv(filename); // .csv
	
	else if (extension == ".tsv") 
		opentsv(filename); // .tsv
	
	else if (extension == ".json") 
		openjson(filename); // .json
	
	else if (extension == ".xml") 
		openxml(filename); // .xml
	
	else cout << "Error: file extension not recognized." << endl;
}
*/

/*********************************
// Dictionary Helper Functions
**********************************/
string Dictionary::normalize(const string &word) const 
{
	string cleanWord {""};
	for (char c : word)
	{
		if (!isalpha(static_cast<unsigned char>(c))) continue;
		{
		// tolower() return int, passing a negative value = undefined behavior
		cleanWord.push_back(tolower(static_cast<unsigned char>(c))); 
		}	
	}
	return cleanWord;
}

void Dictionary::load(const string &filename)
{
	std::ifstream file(filename);

	if (!file) throw std::runtime_error("Error: Cannot open dictionary.\n");

	string word;
	while (file >> word)
	{
		addWord(word);
	}
}

void Dictionary::save(const string &filename) const 
{
	// treat dicitonary.txt as a snapshot, not a log
	// overwrite dictionary.txt with all words from trie
	std::ofstream file(filename);
	
	if (!file) throw std::runtime_error("Error: Cannot open dictionary.\n");
	
	// "snapshot" trie in file
	m_trie.writeAll(file);		
}
/*
bool Dictionary::opencsv(const string &filename)
{
    // open file
    std::ifstream file(filename);
	if (!file) throw std::runtime_error("Error: Cannot open file.");

    // load information

	return true;
}

bool Dictionary::opentsv(const string &filename)                                
{
	// open file
	std::ifstream file(filename);
	if (!file) throw std::runtime_error("Error: Cannot open file.");
	
	// load information

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
*/
