#include "Dictionary.h"
// implement Dicionary.cpp here
Dictionary::Dictionary() : m_root(new TrieNode()) {}

Dictionary::~Dictionary()
{
    delete m_root;
}
