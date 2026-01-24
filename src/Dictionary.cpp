#include "Dictionary.h"

// TRIE CLASS //
Trie::Trie() : m_root{new TrieNode()} {}

Trie::~Trie() { deleteTrie(m_root); }

bool Trie::insert(string_view word, int word_id)
{
    TrieNode *node {m_root};

    // traverse to the last node in the word
    for (char c : word)
    {
        int index {c - 'a'}; 

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
	node->m_word_id = word_id;
    return true;
}

bool Trie::remove(string &word) { return remove(m_root, word); }

bool Trie::contains(string_view word) const
{
    TrieNode *node {m_root};

    // traverse to the last node in the word (DFS)
    for (char c : word)
    {
        int index {c - 'a'};
        if (!node->m_children[index]) return false; // not found
        node = node->m_children[index];
    }

    return node->m_isEndOfWord; // word not found
}

bool Trie::startsWith(string_view prefix) const
{
	const TrieNode *node {m_root};

	// DFS
	for (char c : prefix)
	{
		int index {c - 'a'};
		if (!node || !node->m_children[index]) return false;
		node = node->m_children[index];
	}

	return true;
}

string Trie::getPrefix(string_view word) const
{
	const TrieNode *node {m_root};
	string prefix;

	// DFS
	for (char c : word)
	{
		int index {c - 'a'};
		if (!node || !node->m_children[index]) break;
		
		prefix.push_back(c);
		node = node->m_children[index];
	}

	return prefix;
}

void Trie::collectWithPrefix(string_view prefix, std::vector<string> &out, std::size_t limit) const
{
	const TrieNode *node {m_root};
	string currentWord;

	// DFS
	for (char c : prefix)
	{
		int index {c - 'a'};
		if (!node || !node->m_children[index]) return; // prefix not found

		currentWord.push_back(c);
		node = node->m_children[index];
	}
	
	// build words
	collectFromNode(node, currentWord, out, limit);
}

void Trie::writeAll(std::ostream &out) const
{
	// write words to given output
	if (!out)
	{
		std::cerr << "output stream is invalid\n";
		return;
	}

	string currentWord;
	rewrite(m_root, currentWord, out); // call recursive write function
}

void Trie::print() const { writeAll(cout); } // same as writeAll logic

void Trie::dump() const
{
	cout << "(root)\n";
    dumpNode(m_root, ""); // call recursive dump node function
}

void Trie::dumpWord(string_view word) const
{
	if (!contains(word)) return;
	const TrieNode *node {m_root};
	if (!node) return;

	cout << "(root)\n";
	size_t depth {0};

	for (char c : word) 
	{
		int index {c - 'a'};

		// print graphics
		if (!node->m_children[index])
		{
			cout << string(depth * 4, ' ') 
				<< "└── " << c << "(missing)\n";
			return;
		}

		node = node->m_children[index];

		cout << string(depth * 4, ' ') 
			<< "└── " << c; 
		if (node->m_isEndOfWord) cout << " *";

		cout << '\n';
		++depth;
	}
}

void Trie::clear()
{
	deleteTrie(m_root);
	m_root = new TrieNode(); // initalize new root
}

bool Trie::isEmpty() const
{
	if (!m_root) return true;
	if (m_root->m_isEndOfWord) return false;

	for (int i{0}; i < dct::g_alpha; ++i)
	{
		if (m_root->m_children[i]) return false;
	}

	return true;
}

/*********************************
// Trie Helper Functions
*********************************/
void Trie::deleteTrie(TrieNode *node)
{
	if (!node) return;
	
	// DFS
	for (int i{0}; i < dct::g_alpha; ++i)
	{
		deleteTrie(node->m_children[i]);
	}
	
	delete node;
}

void Trie::rewrite(const TrieNode *node, string &currentWord, std::ostream &out) const
{ // similar to collectFromNode 
	if (!node) return;
	if (node->m_isEndOfWord) out << currentWord << '\n'; // write complete word
	
	// DFS
	for (int i{0}; i < dct::g_alpha; ++i)
	{
		if (node->m_children[i])
		{
			char letter {static_cast<char>('a' + i)};
			currentWord.push_back(letter); // build word 
			rewrite(node->m_children[i], currentWord, out);
			currentWord.pop_back(); // backtrack (undo complete word) works because of recursive rewrite
		}
	}
}

void Trie::dumpNode(const TrieNode *node, const string &prefix) const
{ 
	if (!node) return; 
	
	// DFS
	for (int i{0}; i < dct::g_alpha; ++i)
	{
		char letter {static_cast<char>('a' + i)};
		const TrieNode *child = node->m_children[i];
		if (!child) continue;
		bool isLast = true;
		
		// check for another sibling
		for (int j{i+1}; j < dct::g_alpha; ++j)
		{
			// check for later children
			if (node->m_children[j])
			{
				// current child is not the last sibling
				isLast = false;
				break; 
			}
		}

		// print graphics
		cout << prefix << (isLast ? "└── " : "├── ") << letter;
		if (child->m_isEndOfWord) cout << " *"; 
		cout << '\n';

		dumpNode(node->m_children[i], prefix + (isLast ? "    " : "│   "));	
	}
}

bool Trie::remove(TrieNode *&node, string_view word)
{
	if (!node) return false;

	// check if end of word	
	if (word.empty())
	{
		if (!node->m_isEndOfWord) return false; // word is not stored
	
		node->m_isEndOfWord = false;

		// check if the node has children
		for (int i{0}; i < dct::g_alpha; ++i)
		{
			// if the node has children it's still needed for another word
			if (node->m_children[i]) return true;
		}

		// if it has no children we can safely remove the node
		delete node;
		node = nullptr;
		return true;
	}
	
	// find child index
	int index {word[0] - 'a'};
	if (remove(node->m_children[index], word.substr(1))) // recursively remove the rest of the word
	{
		if (node->m_isEndOfWord) return true; // if the current node marks the end of another word, preserve it

		// check if node has any children and is still needed
		for (int i{0}; i < dct::g_alpha; ++i)
		{
			if (node->m_children[i]) return true;
		}
		
		// if the node is not the end of a word and has no children
		delete node;
		node = nullptr;
		return true;
	}
	
	return false;
}

void Trie::collectFromNode(const TrieNode *node, string &currentWord, std::vector<string> &out, std::size_t limit) const
{ // similar to rewrite
	if (!node || out.size() >= limit) return;
	if (node->m_isEndOfWord) out.push_back(currentWord); // add complete word to results vector

	for (int i{0}; i < dct::g_alpha && out.size() < limit; ++i)
	{
		if (node->m_children[i])
		{
			char letter {static_cast<char>('a' + i)};
			currentWord.push_back(letter); // build word
			collectFromNode(node->m_children[i], currentWord, out, limit);
			currentWord.pop_back(); // backtrack (undo complete word) works because of recursive collectFromNode 
		}
	}	
}

// DICTIONARY CLASS //
Dictionary::Dictionary() : m_db{dct::g_dictDb}
{
	m_db.createTables();	
	loadDb(m_db); 
}

Dictionary::~Dictionary() {}

bool Dictionary::addWord(string_view word)
{
	string cleanWord {normalize(word)};
	if (cleanWord.empty()) return false;

	int word_id = m_db.insertWord(cleanWord);
	if (word_id <= 0) return false;

	if (!m_trie.insert(cleanWord, word_id)) return false;

	return true;	
}

bool Dictionary::removeWord(string_view word)
{ // implement remove from db
	if (m_trie.isEmpty()) return false;

	string cleanWord {normalize(word)};
	if (cleanWord.empty()) return false;

	if (!m_trie.remove(cleanWord)) return false;

	return true;
}

bool Dictionary::search(string_view word) const
{
	if (m_trie.isEmpty()) return false;

	string cleanWord {normalize(word)};
	if (cleanWord.empty()) return false;
	return m_trie.contains(cleanWord);
}

void Dictionary::suggestFromPrefix(string_view prefix, std::vector<string> &results, std::size_t limit) const 
{
	string cleanPrefix {normalize(prefix)};
	if (cleanPrefix.empty()) return;
	m_trie.collectWithPrefix(cleanPrefix, results, limit+1); // LOGIC ERROR: (off by 1) - balance the prefix being removed from the results

	// remove the prefix from the results vector
	results.erase(std::remove(results.begin(), results.end(), prefix), results.end());
}

// void Dictionary::loadTxt(const string &filename) { load(filename); } // expendable

void Dictionary::print() const { m_trie.print(); } 

void Dictionary::dump() const { m_trie.dump(); }

void Dictionary::dumpWord(string_view word) const { m_trie.dumpWord(word); }

void Dictionary::eraseAll() { m_trie.clear(); }

bool Dictionary::isEmpty() const { return m_trie.isEmpty(); }

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
		// tolower() returns int, passing a negative value = undefined behavior
		cleanWord.push_back(tolower(static_cast<unsigned char>(c))); 
		}	
	}
	return cleanWord;
}

void Dictionary::loadDb(Database &db) 
{
    sqlite3* sqlDB = m_db.getDB();
    sqlite3_stmt* stmt;
    const char* query = "SELECT lemma FROM words;";
    sqlite3_prepare_v2(sqlDB, query, -1, &stmt, nullptr);
    while (sqlite3_step(stmt) == SQLITE_ROW) 
	{
        const unsigned char* text = sqlite3_column_text(stmt, 0);
        m_trie.insert(reinterpret_cast<const char*>(text));
    }
    sqlite3_finalize(stmt);
}

bool Dictionary::openjson(const string &filename)
{	
	std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot open " << filename << "\n";
        return false;
    }

    string line;

    while (std::getline(file, line))
    {
        try
        {
            nlohmann::json j = nlohmann::json::parse(line);

            if (!j.contains("word")) continue;

            string lemma = j["word"];
            int word_id = db.insertWord(lemma);

            // add to trie
            addWord(lemma, word_id);

            // definitions
            if (j.contains("senses"))
            {
                for (auto& sense : j["senses"])
                {
                    if (sense.contains("glosses"))
                    {
                        for (auto& g : sense["glosses"])
                        {
                            db.insertSense(word_id,
                                           j.value("pos", ""),
                                           g.get<string>());
                        }
                    }
                }
            }

            // etymology
            if (j.contains("etymology_text"))
            {
                db.insertEtymology(word_id, j["etymology_text"]);
            }

            // forms (plural & alt spellings)
            if (j.contains("forms"))
            {
                for (auto& f : j["forms"])
                {
                    std::string form = f["form"];
                    std::string tag = f["tags"][0];
                    db.insertForm(word_id, form, tag);
                }
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "Skipping bad line: " << e.what() << "\n";
        }
    }

    return true;
}

#if 0
void Dictionary::load(const string &filename)
{
	std::ifstream file(filename);
	if (!file) throw std::runtime_error("Error: Cannot open external dictionary.\n");

	string word;
	while (file >> word)
	{
		addWord(word);
	}
}

void Dictionary::save(const string &filename) const 
{
	// overwrite dictionary.txt with all words from trie
	std::ofstream file(filename);	
	if (!file) throw std::runtime_error("Error: Cannot open internal dictionary.\n");
	
	// "snapshot" trie in file
	m_trie.writeAll(file);		
}

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



// SPELLCHECKER CLASS //
SpellChecker::SpellChecker(const Dictionary &dict) : m_dict{dict} {}

SpellChecker::~SpellChecker() {}

bool SpellChecker::check(string_view word) const
{
	// returns false if word is mispelled or not found in dictionary
	return (!m_dict.search(word) ? false : true);
}

std::vector<string> SpellChecker::suggest(string_view prefix) const 
{ 
	std::vector<string> results;

	if (m_dict.isEmpty()) return results;	
	
	if (!prefix.empty()) m_dict.suggestFromPrefix(prefix, results, dct::g_maxSuggest);

	return results; 
}

std::vector<string> SpellChecker::correct(string_view word) const 
{
	std::vector<string> results;
	return results;
}

string SpellChecker::autofill(string_view word) const 
{
	string result {word};
	return result;
}

void SpellChecker::printSuggest(const std::vector<string> &out) const
{
	if (out.empty()) 
	{
		return;
	} else
	{
		for (const auto &word : out)
		{
			cout << "→ " << word << '\n'; 
		}
	}
}
