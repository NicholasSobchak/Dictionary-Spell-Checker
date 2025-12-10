#include "Dictionary.h"
// implement Dicionary.cpp here
Dictionary::Dictionary() : m_root(new TrieNode()) {}

Dictionary::~Dictionary() { delete m_root; }

void Dictionary::loadFromFile(const string &filename)
{
}

void insert(const string &word)
{
    int wordSize = sizeof(word) / sizeof(word[0]);
    for (int i = 0; i < wordSize; ++i)
    {
        if (!m_root.search(word[i])) // word[i] != m_root->m_children
        {
            m_root = nullptr
        }
    }
}

bool search(const string &word)
{
}

TrieNode findNode(const char &letter)
{
}

void printDictionary()
{
}
