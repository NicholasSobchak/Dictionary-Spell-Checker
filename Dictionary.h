#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <fstream>
#include <string_view>
#include <filesystem>
#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::string;
using std::string_view;
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
    bool insert(string_view word);
    bool contains(string_view word) const;
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
    void rewrite(const TrieNode *node, string &currentWord, std::ostream &out) const;
    void dumpNode(const TrieNode *node, const string &prefix) const;
    bool remove(TrieNode *&node, string_view word);
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
    void dump() const; // dumps trie.print()
    void debug() const; // dumps trie.dumpDebug()
    void loadTxt(const string &filename);
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
    //bool openjson(const string &filename);
    /*
    bool opencsv(const string &filename);
    bool opentsv(const string &filename);
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
