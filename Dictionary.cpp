#include "Dictionary.h"
#include <fstream>
#include <filesystem>
// implement Trie class here
Trie::Trie() : m_root(new TrieNode()) {}

Trie::~Trie() { deleteTrie(m_root); }

bool Trie::insert(const string &word)
{
    TrieNode *node {m_root};

	// traverse to the last node in the word
    for (int i{0}; i < int(word.length()); ++i)
    {
     	char letter {word[i]};
        int index {letter - 'a'}; // general online formula to get the numeric index - (uses ASCII value),(0-based indexing)
        
	 	// check if there is an existing child node
        if (!node->m_children[index]) 
     	{ 
     		node->m_children[index] = new TrieNode();
     	}
     		
	    node = node->m_children[index];
    }

	// check if word is already in Trie (node is last letter of the word)
	if (node->m_isEndOfWord) return false;

	node->m_isEndOfWord = true;
    return node->m_isEndOfWord;
}

bool Trie::contains(const string &word)
{
	bool found {false};
	TrieNode *node {m_root};

	// traverse to the last node in the word
	for (char letter : word)
	{
        int index {letter - 'a'};	    
	    node = node->m_children[index];	
	}

	if (node->m_isEndOfWord) return found = true;
	return found; // word not found
}

void Trie::clear()
{
	deleteTrie(m_root);
	m_root = new TrieNode;
}

void Trie::dumpDebug()
{
	// implement
}

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
	size_t p {filename.find_last_of('.')};
	string extension {""};

	if (p == string::npos) cout << "file has no extension!" << endl;
	else extension = filename.substr(p);

	// control file calls
	if (extension == ".txt") 
		opentxt(filename); // .txt
	
	else if (extension == ".csv") 
		opencsv(filename); // .csv
	
	else if (extension == ".tsv") 
		opentsv(filename); // .tsv
	
	else if (extension == ".json") 
		openjson(filename); // .json
	
	else if (extension == ".xml") 
		openxml(filename); // .xml
	
	else cout << "file extension not recognized!" << endl;
}

bool Dictionary::addWord(const string &word)
{
	// add normalized word to dictionary.txt and trie structure
	string cleanWord {normalize(word)};
	if(cleanWord.empty()) return false;
	
	if (!m_trie.insert(cleanWord)) return false;

	// add to dictionary.txt
	std::ofstream file("dictionary.txt", std::ios::app);

	if (!file)
	{
		throw std::runtime_error("Error: cannot open dictionary!");
	}

	file << cleanWord << '\n';			
	return true;	
}

void Dictionary::dump() const
{
	std::ifstream file("dictionary.txt"); 

	if (!file)
	{
		throw std::runtime_error("Error: cannot open dictionary!");	
	}

	if (std::filesystem::file_size("dictionary.txt") == 0)
	{
		cout << "Dictionary is empty!" << endl;
		return;
	}

	string word;
	// std::vector<string> words;
	while (file >> word) 
	{
		cout << word << '\n';	
		// words.push_back(word); 
	}

	// printTerminal(words);
}

void Dictionary::eraseAll()
{
	// "erase" the dictionary by overwriting it
	std::ofstream file("dictionary.txt");

	if (!file.is_open())
	{
		throw std::runtime_error("Error: cannot open dictionary!");
		return;
	}
	// overwrite with "" (empty)
	file << "";
	file.close();

	m_trie.clear();
}

void Dictionary::debug()
{
	m_trie.dumpDebug();
}

/*********************************
// Dictionary Helper Functions
**********************************/
string Dictionary::normalize(const string &word) const 
{
	string cleanWord {word};
	for (int i{0}; i < int(cleanWord.length()); ++i)
	{
		if (!isalpha(cleanWord[i])) continue;

		// tolower() return int, passing a negative value = undefined behavior
		char letter = tolower(static_cast<unsigned char>(cleanWord[i])); 
		cleanWord += letter;
	}
	return cleanWord;
}

void Dictionary::printTerminal(const std::vector<string> &words) const 
{
	if (words.empty())
	{
		cout << "Dictionary empty!";
		return;
	}

	size_t maxLen {0};
	for (const auto& w : words)
	{
		maxLen = std::max(maxLen, w.length());
	}

	// use size_t (unsigned) to avoid signed/unsigned comparisons i.e. words.size() returns size_t
	size_t width {maxLen + 2};
	int termWidth {terminalWidth()};
	size_t cols = std::max<size_t>(1, termWidth / width);
	size_t rows {(words.size() + cols - 1) / cols};	
	
	for (size_t i{0}; i < rows; ++i)
	{
		for (size_t j{0}; j < cols; ++j)
		{
			size_t index {j * rows + i};
			if (index < words.size())
				cout << std::left << std::setw(20) << words[index];
		}
		cout << '\n';
	}
}

int Dictionary::terminalWidth() const
{
	winsize w {};
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	return w.ws_col;
}

bool Dictionary::opentxt(const string &filename) // open .txt file
{
	// open file
	std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Error: Cannot open file!");
        return false;
    }

	// parse words
    string word;
    while (file >> word)
    {	
        addWord(word); // add word to dictionary.txt and trie data structure
    }

    file.close();
    return true;
}

bool Dictionary::opencsv(const string &filename)
{
    // open file
    std::ifstream file(filename);
	if (!file.is_open())
    {
       	throw std::runtime_error("Error: Cannot open file!");
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
	std::ifstream file(filename);
	if (!file.is_open())
	{
		throw std::runtime_error("Error: Cannot open file!");
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
