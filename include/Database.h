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
	bool insertWord(const std::string &lemma);
	bool insertSense(int word_id, const std::string &pos, const std::string &definition);
	bool insertEtymology(int word_id, const std::vector<std::string> &etymology);
	bool insertForm(int word_id, const std::string &form, const std::string &tag);
	bool removeWord(int word_id); // implement
	
	// getters
	sqlite3 *getDB();
	std::string getLemma(int word_id);
	std::vector<std::string> getSenses(int word_id); 
	std::vector<std::string> getEtymology(int word_id); 
	std::string getPos(int word_id); 	
	int getWordID(const std::string &lemma);

private:
	sqlite3 *db;

	/*********************************
    // Helper declarations go here
    **********************************/
};
#endif 
