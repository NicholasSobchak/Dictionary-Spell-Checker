#ifndef DICTIONARY_H
#define DICTIONARY_H
#include "nlohmann/json.hpp"
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
        inline constexpr const char *g_dict {"dictionary.txt"}; // inline to avoid linker errors
        inline constexpr const int g_alpha {26};
		inline constexpr const int g_maxSuggest {10};
}

class Trie
{
public:
    Trie();
    ~Trie();
    bool insert(string_view word);
    bool remove(string &word);
    bool contains(string_view word) const;
	bool startsWith(string_view prefix) const;
	string getPrefix(string_view word) const;
	void collectWithPrefix(string_view prefix, std::vector<string> &out, std::size_t limit) const;
    void writeAll(std::ostream &out) const;
    void print() const;
    void dump() const;
    void clear();
	bool empty() const;

private:
    struct TrieNode {
        TrieNode *m_children[26];
        bool m_isEndOfWord{false};

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

    void deleteTrie(TrieNode *node);
    void rewrite(const TrieNode *node, string &currentWord, std::ostream &out) const;
    void dumpNode(const TrieNode *node, const string &prefix) const;
    bool remove(TrieNode *&node, string_view word);
	void collectFromNode(const TrieNode *node, string &currentWord, std::vector<string> &out, std::size_t limit) const;
};

class Dictionary
{
public:
    friend class Tester;
    // implement Dictionary class here
    Dictionary();
    ~Dictionary();
    bool addWord(string_view word);
    bool removeWord(string_view word);
	bool search(string_view word) const; 
	std::vector<string> prefixSuggest(string_view word) const;
	void loadTxt(const string &filename);
    void print() const; 
    void dump() const;
    void eraseAll();
    
	// void loadInfo(const string &filename);
    bool openjson(const string &filename); // make public for now

private:
    Trie m_trie;

    /*********************************
    // Helper declarations go here
    **********************************/

    string normalize(string_view word) const;
    void load(const string &filename);
    void save(const string &filename) const;
    // bool openjson(const string &filename);
    /*
    bool opencsv(const string &filename);
    bool opentsv(const string &filename);
    bool openxml(const string &filename);
    */
};

class SpellChecker
{
public:
	explicit SpellChecker(const Dictionary &dict);
	~SpellChecker();
	bool check(string_view word);
	std::vector<string> suggest(string_view word) const;
	void printSuggest(const std::vector<string> &out) const; // placeholder to print suggestions

private:
	const Dictionary &m_dict;

    /*********************************
    // Helper declarations go here
    **********************************/

};

#endif
