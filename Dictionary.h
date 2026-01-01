#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
class Tester;

class Trie
{
public:
    Trie();
	~Trie();
	bool insert(const string &word);	
	bool contains(const string &word);
	void clear();

private:
	struct TrieNode {
		TrieNode *m_children[26];
		bool m_isEndOfWord;
		string m_word;
		
		TrieNode() : m_isEndOfWord(false), m_word("")
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
	};

class Dictionary
{
public:
    friend class Tester;
    // implement Dictionary class here
    Dictionary();
    ~Dictionary();
    void loadFromFile(const string &filename);
	bool addWord(const string &word);
    void printDictionary() const;
	void eraseAll();

private:
    Trie m_trie;

    /*********************************
    // Helper declarations go here
    **********************************/
    bool opentxt(const string &filename);
    bool opencsv(const string &filename);
    bool opentsv(const string &filename);
    bool openjson(const string &filename);
    bool openxml(const string &filename);
	string normalize(const string &word) const;
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
