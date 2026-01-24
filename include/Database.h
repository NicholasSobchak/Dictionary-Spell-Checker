#ifndef DATABASE_H // alternative (#pragma once)
#define DATABASE_H
#include <sqlite3.h>
#include <string>


// This class acts as a wrapper around a C library
class Database
{
public:
	Database(const std::string &filename);
	~Database();

	bool insertEtymology(int word_id, const std::string &etymology[]);
	bool insertForm(int word_id, const std::string &form, const std::string &tag);

	void createTables();
	void insertSense(int word_id, const std::string &pos, const std::string &definition);

	int insertWord(const std::string &lemma);

	sqlite3 *getDB();

private:
	sqlite3 *db;
};
#endif 
