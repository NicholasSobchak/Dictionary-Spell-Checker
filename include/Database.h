#ifndef DATABASE_H // alternative (#pragma once)
#define DATABASE_H
#include <sqlite3.h>
#include <vector>
#include <string>
#include <iostream>


// This class acts as a wrapper around a C library
class Database
{
public:
	Database(const std::string &filename);
	~Database();
	
	void createTables();

	// inserters
	bool insertEtymology(int word_id, const std::vector<std::string> &etymology);
	bool insertForm(int word_id, const std::string &form, const std::string &tag);
	bool insertExample(int word_id, const std::string &example);
	bool insertSynonym(int word_id, const std::string &synonym);
	bool insertAntonym(int word_id, const std::string &antonym);
	bool isEmpty() const;

	bool removeWord(int word_id); // implement
		
	int insertWord(const std::string &lemma);
	int insertSense(int word_id, const std::string &pos, const std::string &definition);
	int getWordID(const std::string &lemma) const;

	void print() const;
	void clearDB();

	sqlite3 *getDB();

private:
	sqlite3 *db;

	/*********************************
    // Helper declarations go here
    **********************************/
};
#endif 
