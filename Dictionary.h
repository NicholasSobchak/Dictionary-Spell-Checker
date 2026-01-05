#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <iostream>
#include <string>
#include <vector>
#include <sys/ioctl.h>
#include <unistd.h>
using std::cout;
using std::endl;
using std::string;
class Tester;


class Trie
{
public:
    Trie();
	~Trie();
	bool insert(const string &word);	
	bool contains(const string &word) const;
	void remove(const string &word);
	void clear();
	void writeAll(std::ostream &out) const;
	void dumpDebug() const;	
	void print() const;

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
	void write(TrieNode *node, string &currentWord, std::ostream &out) const;
};

class Dictionary
{
public:
    friend class Tester;
    // implement Dictionary class here
    Dictionary();
    ~Dictionary();
	void load();
	void save();
    void loadFromFile(const string &filename);
	bool addWord(const string &word);
    void dump() const; // dumps trie.print()
	void debug() const; // dumps trie.dumpDebug()
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
