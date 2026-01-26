#ifndef DICTIONARY_H
#define DICTIONARY_H
#include "Trie.h"
#include "Database.h"
#include "../nlohmann/json.hpp"
#include <fstream>

class Tester;
//class Trie;
//class Database;

class Dictionary
{
public:
    friend class Tester;

    Dictionary();
    ~Dictionary() = default;

    bool addWord(std::string_view word);
    bool removeWord(std::string_view word); // implement databse logic
	bool search(std::string_view word) const; 
	bool isEmpty() const;

	void suggestFromPrefix(std::string_view prefix, std::vector<std::string> &results, std::size_t limit) const;
    void print() const; 
    void dump() const;
	void dumpWord(std::string_view word) const;
    void eraseAll();
   
    // expendable	
	// void loadInfo(const string &filename);
    bool openjson(const std::string &filename); // make public for now (load into db)
	void loadTxt(const std::string &filename); 

private:
	// represent word info from the db in memory
	struct WordInfo
	{
		std::string lemma;
        std::vector<std::string> senses;
	    std::vector<std::string> etymology;
		std::string pos;
	    int id{-1}; // ??
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
    void load(const std::string &filename);
    void save(const std::string &filename) const;

	std::string normalize(std::string_view word) const; 
};
#endif
