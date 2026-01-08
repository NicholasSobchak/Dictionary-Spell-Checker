#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
class Tester;

namespace dct {
	inline constexpr const char *g_dict {"dictionary.txt"};
	inline constexpr const int g_alpha {26};
}


class Trie
{
public:
    Trie();
	~Trie();
	bool insert(const string &word);	
	bool contains(const string &word) const;
	bool remove(string &word);
	void writeAll(std::ostream &out) const;
	void dumpDebug() const;	
	void print() const;
	void clear();

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
	void reWrite(const TrieNode *node, string &currentWord, std::ostream &out) const;
	void dumpNode(const TrieNode *node, const string &prefix) const;
};

class Dictionary
{
public:
    friend class Tester;
    // implement Dictionary class here
    Dictionary();
    ~Dictionary();
	bool addWord(const string &word);
	bool removeWord(const string &word);
    void dump() const; // dumps trie.print()
	void debug() const; // dumps trie.dumpDebug()
	void loadTxt(const string &filename);
	void eraseAll();
    // void loadInfo(const string &filename);

private:
    Trie m_trie;

    /*********************************
    // Helper declarations go here
    **********************************/

	string normalize(const string &word) const;
	void load(const string &filename);
	void save(const string &filename) const;
	/*
    bool opencsv(const string &filename);
    bool opentsv(const string &filename);
    bool openjson(const string &filename);
    bool openxml(const string &filename);
	*/
};

class SpellChecker
{
public:
    // implement SpellChecker class here

private:
    // private members here

    /*********************************
    // Helper declarations go here
    **********************************/
};

#endif
