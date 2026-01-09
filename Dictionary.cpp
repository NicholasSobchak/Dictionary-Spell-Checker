#include "Dictionary.h"
#include <filesystem>
#include <fstream>

// TRIE CLASS //
Trie::Trie() : m_root(new TrieNode()) {}

Trie::~Trie() { deleteTrie(m_root); }

bool Trie::insert(string_view word)
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

bool Trie::contains(string_view word) const
{
	TrieNode *node {m_root};

	// traverse to the last node in the word
	for (char c : word)
	{
        int index {c - 'a'};
		if (!node->m_children[index]) return false; // not found 		
	    node = node->m_children[index];	// CHECK LOGIC FOR CRASH
	}

	return node->m_isEndOfWord; // word not found
}

bool Trie::remove(string &word) { return remove(m_root, word); }

void Trie::writeAll(std::ostream &out) const
{
	if (!out)
	{
		std::cerr << "output stream is invalid\n";
		return;
	}

	string currentWord;
	rewrite(m_root, currentWord, out);
}

void Trie::dumpDebug() const
{
	std::cout << "(root)\n";
    dumpNode(m_root, "");
}

void Trie::print() const { writeAll(cout); } // same as writeAll logic

void Trie::clear()
{
	deleteTrie(m_root);
	m_root = new TrieNode();
}

/*********************************
// Trie Helper Functions
*********************************/
void Trie::deleteTrie(TrieNode *node)
{
	if (!node)
		return;
	
	// BFS
	for (int i{0}; i < dct::g_alpha; ++i)
	{
		deleteTrie(node->m_children[i]);
	}
	
	delete node;
}

void Trie::rewrite(const TrieNode *node, string &currentWord, std::ostream &out) const
{ // general algorithm
	if (!node) return;
	if (node->m_isEndOfWord) out << currentWord << '\n';
	
	// BFS
	for (int i{0}; i < dct::g_alpha; ++i)
	{
		if (node->m_children[i])
		{
			char letter {static_cast<char>('a' + i)};
			currentWord.push_back(letter); // build word that will be written to the file
			rewrite(node->m_children[i], currentWord, out);
			currentWord.pop_back(); // backtrack
		}
	}
}

void Trie::dumpNode(const TrieNode *node, const string &prefix) const
{ // gerneral algorithm
	if (!node) return; 

	for (int i{0}; i < dct::g_alpha; ++i)
	{
		char letter {static_cast<char>('a' + i)};
		const TrieNode *child = node->m_children[i];
		if (!child) continue;
		bool isLast = true;
		
		for (int j{i+1}; j < dct::g_alpha; ++j)
		{
			if (node->m_children[j])
			{
				isLast = false;
				break;
			}
		}
		std::cout << prefix << (isLast ? "└── " : "├── ") << letter;
		if (node->m_isEndOfWord) cout << " *"; // This was the original line without the fix
		cout << '\n';

		dumpNode(node->m_children[i], prefix + (isLast ? "    " : "│   "));	
	}
}

bool Trie::remove(TrieNode *&node, string_view word)
{
	if (!node) return false;
	
	if (word.empty())
	{
		if (!node->m_isEndOfWord) return false;
		
		node->m_isEndOfWord = false;
		for (int i{0}; i < dct::g_alpha; ++i)
		{
			if (node->m_children[i]) return true;
		}

		delete node;
		node = nullptr;
		return true;
	}

	int index {word[0] - 'a'};
	if (remove(node->m_children[index], word.substr(1)))
	{
		if (node->m_isEndOfWord) return true;

		for (int i{0}; i < dct::g_alpha; ++i)
		{
			if (node->m_children[i]) return true;
		}

		delete node;
		node = nullptr;
		return true;
	}
	
	return false;
}

// DICTIONARY CLASS //
Dictionary::Dictionary() { load(dct::g_dict); }

Dictionary::~Dictionary() { save(dct::g_dict); }

bool Dictionary::addWord(string_view word)
{
	// correct word and add it to trie
	string cleanWord {normalize(word)};
	if (cleanWord.empty()) return false;
	
	if (!m_trie.insert(cleanWord)) return false;

	return true;	
}

bool Dictionary::removeWord(string_view word)
{
	string cleanWord {normalize(word)};
	if (cleanWord.empty()) return false;

	if (!m_trie.remove(cleanWord)) return false;

	return true;
}

void Dictionary::dump() const { m_trie.print(); } 

void Dictionary::debug() const { m_trie.dumpDebug(); }

void Dictionary::loadTxt(const string &filename) { load(filename); }

void Dictionary::eraseAll() { m_trie.clear(); }

#if 0
void Dictionary::loadInfo(const string &filename)
{
	/*
	   compatible file type:
        .csv
        .tsv
        .json
        .xml
	*/
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
#endif

/*********************************
// Dictionary Helper Functions
**********************************/
string Dictionary::normalize(string_view word) const 
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
#if 0
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
#endif

