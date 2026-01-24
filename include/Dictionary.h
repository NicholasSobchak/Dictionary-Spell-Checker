#ifndef DICTIONARY_H
#define DICTIONARY_H
#include "Database.h"
#include "../nlohmann/json.hpp"
#include <string_view>
#include <fstream>
#include <filesystem>
#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::string;
using std::string_view; // more efficient than "const string &word" for read-only scenarios (non-owning) 
class Tester;

namespace dct {
        inline constexpr const char *g_dictTxt {"dictionary.txt"}; // inline to avoid linker errors
        inline constexpr const char *g_dictDb {"dictionary.db"}; // inline to avoid linker errors
        inline constexpr const int g_alpha {26};
		inline constexpr const int g_maxSuggest {10};
}

class Trie
{
public:
    Trie();
    ~Trie();

    bool insert(string_view word, int word_id);
    bool remove(string &word);
    bool contains(string_view word) const;
	bool startsWith(string_view prefix) const;
	bool isEmpty() const;

	void collectWithPrefix(string_view prefix, std::vector<string> &out, std::size_t limit) const;
    void writeAll(std::ostream &out) const;
    void print() const;
    void dump() const;
	void dumpWord(string_view word) const;
    void clear();

	string getPrefix(string_view word) const;

private:
    struct TrieNode {
        TrieNode *m_children[26];
        bool m_isEndOfWord {false};
		int m_word_id {0};

        TrieNode()
        {
            for (int i = 0; i < 26; ++i)
            {
                m_children[i] = nullptr;
            }
        }
    };

    TrieNode *m_root;

    /*********************************
    // Helper declarations go here
    **********************************/
    bool remove(TrieNode *&node, string_view word);

    void deleteTrie(TrieNode *node);
    void rewrite(const TrieNode *node, string &currentWord, std::ostream &out) const;
    void dumpNode(const TrieNode *node, const string &prefix) const;
	void collectFromNode(const TrieNode *node, string &currentWord, std::vector<string> &out, std::size_t limit) const;
};

class Dictionary
{
public:
    friend class Tester;
    // implement Dictionary class here
    Dictionary();
    ~Dictionary();
	// IMPLEMENT DATABASE INTO DICTIONARY CLASS
    bool addWord(string_view word);
    bool removeWord(string_view word); // implement databse logic
	bool search(string_view word) const; 
	bool isEmpty() const;

	void suggestFromPrefix(string_view prefix, std::vector<string> &results, std::size_t limit) const;
    void print() const; 
    void dump() const;
	void dumpWord(string_view word) const;
    void eraseAll();
   
    // expendable	
	// void loadInfo(const string &filename);
    bool openjson(const string &filename); // make public for now (load into db)
	void loadTxt(const string &filename); 

private:
	struct WordInfo
	{
		string lemma;
		std::vector<string> senses;
	};

    Trie m_trie;
	Database m_db;

    /*********************************
    // Helper declarations go here
    **********************************/
	// bool openjson(const string &filename);
    /*
    bool opencsv(const string &filename);
    bool opentsv(const string &filename);
    bool openxml(const string &filename);
    */

	void loadDb(Database &db);

	// expendable
    void load(const string &filename);
    void save(const string &filename) const;

    string normalize(string_view word) const;
    
};

class SpellChecker
{
public:
	explicit SpellChecker(const Dictionary &dict);
	~SpellChecker();

	bool check(string_view word) const;

	std::vector<string> suggest(string_view prefix) const;
	std::vector<string> correct(string_view word) const;

	void printSuggest(const std::vector<string> &out) const; // placeholder to print suggestions
	
	string autofill(string_view word) const;
private:
	const Dictionary &m_dict;

    /*********************************
    // Helper declarations go here
    **********************************/

};

#endif
