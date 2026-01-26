#include "Database.h"

Database::Database(const std::string& filename) 
{ 
	// open database
	if (sqlite3_open(filename.c_str(), &db)) throw std::runtime_error("Error: Can't open database\n");
}

Database::~Database() { sqlite3_close(db); }

sqlite3* Database::getDB() { return db; }

void Database::createTables() 
{
    const char* sql {
        "CREATE TABLE IF NOT EXISTS words ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "lemma TEXT UNIQUE);"

        "CREATE TABLE IF NOT EXISTS senses ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "word_id INTEGER,"
        "pos TEXT,"
        "definition TEXT,"
        "FOREIGN KEY(word_id) REFERENCES words(id));"};

    char* errMsg {nullptr};
    sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
}

bool Database::insertWord(const std::string& lemma) 
{
    sqlite3_stmt* stmt; // prepared SQL statement object
    const char* sql {"INSERT OR IGNORE INTO words (lemma) VALUES (?);"}; // add new row if word does not exist, otherwise ignore

	/* 
	db → your open database
	sql → the SQL string
	-1 → read full string
	&stmt → where to store the compiled statement
	nullptr → ignore unused output
	*/	
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;

	/*
	stmt → prepared statement
	1 → first `?` in SQL
	lemma.c_str() → actual word
	-1 → length (auto)
	SQLITE_STATIC → SQLite can safely reference this memory
	*/
    sqlite3_bind_text(stmt, 1, lemma.c_str(), -1, SQLITE_STATIC);
	
	// run the statement
	if (sqlite3_step(stmt) != SQLITE_DONE) return false; 
	sqlite3_finalize(stmt); // free the statement from memory to avoid leaks
    return true; // word inserted successfully
}

bool Database::insertSense(int word_id, const std::string& pos, const std::string& definition) 
{
    sqlite3_stmt* stmt;
    const char* sql = "INSERT INTO senses (word_id, pos, definition) VALUES (?, ?, ?);";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;

	// fill values
    sqlite3_bind_int(stmt, 1, word_id);
    sqlite3_bind_text(stmt, 2, pos.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, definition.c_str(), -1, SQLITE_STATIC);

	if (sqlite3_step(stmt) != SQLITE_DONE) return false;
    sqlite3_finalize(stmt);
	return true;
}

bool Database::insertEtymology(int word_id, const std::vector<std::string> &etymology)
{ // implement
	return true;
}	

bool Database::insertForm(int word_id, const std::string &form, const std::string &tag)
{ // implement
	return true;
}

bool Database::removeWord(int word_id)
{ // implement
	return false;
}

std::string Database::getLemma(int word_id)
{ // impelement
	return "";
}

std::vector<std::string> Database::getSenses(int word_id)
{ // implement
	std::vector<std::string> result;
	return result;
}

std::vector<std::string> Database::getEtymology(int word_id)
{ // implement
	std::vector<std::string> result;
	return result;
}

std::string getPos(int word_id)
{ // implement
	return "";
}

int Database::getWordID(const std::string &lemma)
{
	sqlite3_stmt* stmt;
	const char* sql {"SELECT id FROM words WHERE lemma = ?;"};

	// prepare the sql statement
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return -1;

	// bind the word into the ?
	sqlite3_bind_text(stmt, 1, lemma.c_str(), -1, SQLITE_STATIC);

	// execute the query
	int word_id = -1;
	if (sqlite3_step(stmt) == SQLITE_ROW)
	{
		word_id = sqlite3_column_int(stmt, 0);
	}

	sqlite3_finalize(stmt);
	return word_id;
}
