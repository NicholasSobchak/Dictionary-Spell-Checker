#include "include/Database.h"
#include <iostream>

Database::Database(const std::string& filename) {
    if (sqlite3_open(filename.c_str(), &db)) {
        std::cerr << "Can't open database\n";
    }
}

Database::~Database() 
{
    sqlite3_close(db);
}

sqlite3* Database::getDB() 
{
    return db;
}

void Database::createTables() 
{
    const char* sql =
        "CREATE TABLE IF NOT EXISTS words ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "lemma TEXT UNIQUE);"

        "CREATE TABLE IF NOT EXISTS senses ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "word_id INTEGER,"
        "pos TEXT,"
        "definition TEXT,"
        "FOREIGN KEY(word_id) REFERENCES words(id));";

    char* errMsg = nullptr;
    sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
}

int Database::insertWord(const std::string& lemma) 
{
    sqlite3_stmt* stmt;
    const char* sql = "INSERT OR IGNORE INTO words (lemma) VALUES (?);";
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, lemma.c_str(), -1, SQLITE_STATIC);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return sqlite3_last_insert_rowid(db);
}

void Database::insertSense(int word_id, const std::string& pos, const std::string& definition) 
{
    sqlite3_stmt* stmt;
    const char* sql =
        "INSERT INTO senses (word_id, pos, definition) VALUES (?, ?, ?);";
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    sqlite3_bind_int(stmt, 1, word_id);
    sqlite3_bind_text(stmt, 2, pos.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, definition.c_str(), -1, SQLITE_STATIC);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

