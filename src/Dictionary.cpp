#include "Dictionary.h"
#include "Utils.h"

Dictionary::Dictionary() : m_db{dct::g_dictDb}
{
	m_db.createTables();	
	loadDb(m_db); 
}

bool Dictionary::addWord(std::string_view word)
{
	std::string cleanWord {normalize(word)};
	if (cleanWord.empty()) return false;

	// insert into db
	if (m_db.insertWord(cleanWord)) return false;
	int word_id {m_db.getWordID(cleanWord)};
	if (word_id <= 0) return false;

	// insert into trie
	if (!m_trie.insert(cleanWord, word_id)) return false;

	return true;	
}

bool Dictionary::removeWord(std::string_view word)
{ // implement remove from db
	if (m_trie.isEmpty()) return false;

	std::string cleanWord {normalize(word)};
	if (cleanWord.empty()) return false;

	if (!m_trie.remove(cleanWord)) return false;

	return true;
}

bool Dictionary::search(std::string_view word) const
{
	if (m_trie.isEmpty()) return false;

	std::string cleanWord {normalize(word)};
	if (cleanWord.empty()) return false;
	return m_trie.contains(cleanWord);
}

void Dictionary::suggestFromPrefix(std::string_view prefix, std::vector<std::string> &results, std::size_t limit) const 
{
	std::string cleanPrefix {normalize(prefix)};
	if (cleanPrefix.empty()) return;
	m_trie.collectWithPrefix(cleanPrefix, results, limit+1); // LOGIC ERROR: (off by 1) - balance the prefix being removed from the results

	// remove the prefix from the results vector
	results.erase(std::remove(results.begin(), results.end(), prefix), results.end());
}

// void Dictionary::loadTxt(const string &filename) { load(filename); } // expendable

void Dictionary::print() const { m_trie.print(); } 

void Dictionary::dump() const { m_trie.dump(); }

void Dictionary::dumpWord(std::string_view word) const { m_trie.dumpWord(word); }

void Dictionary::eraseAll() { m_trie.clear(); }

bool Dictionary::isEmpty() const { return m_trie.isEmpty(); }

#if 0
void Dictionary::loadInfo(const string &filename)
{
	/*
	   compatible file type:
        .csv
        .tsv
        .json
        .xml
	*/
	// parse filename
	size_t p {filename.find_last_of('.')};
	string extension {""};

	if (p == string::npos) cout << "Error: file has no extension!" << endl;
	else extension = filename.substr(p);

	// control file calls
	if (extension == ".csv") 
		opencsv(filename); // .csv
	
	else if (extension == ".tsv") 
		opentsv(filename); // .tsv
	
	else if (extension == ".json") 
		openjson(filename); // .json
	
	else if (extension == ".xml") 
		openxml(filename); // .xml
	
	else cout << "Error: file extension not recognized." << endl;
}
#endif

/*********************************
// Dictionary Helper Functions
**********************************/
std::string Dictionary::normalize(std::string_view word) const 
{
	std::string cleanWord {""};
	for (char c : word)
	{
		if (!isalpha(static_cast<unsigned char>(c))) continue;
		{
		    // tolower() returns int, passing a negative value = undefined behavior
		    cleanWord.push_back(tolower(static_cast<unsigned char>(c))); 
		}	
	}
	return cleanWord;
}

void Dictionary::loadDb(Database &db) 
{
    sqlite3* sqlDB = m_db.getDB();
    sqlite3_stmt* stmt;
    const char* query = "SELECT lemma FROM words;";
    sqlite3_prepare_v2(sqlDB, query, -1, &stmt, nullptr);
    while (sqlite3_step(stmt) == SQLITE_ROW) 
	{
        const unsigned char* text = sqlite3_column_text(stmt, 0);
		std::string word {reinterpret_cast<const char*>(text)};
        m_trie.insert(word, m_db.getWordID(word)); 
	}
    sqlite3_finalize(stmt);
}

bool Dictionary::openjson(const std::string &filename)
{	
	std::ifstream file(filename);
	if (!file) throw std::runtime_error("Error: Cannot open external dictionary.\n");

	std::string line;
    while (std::getline(file, line))
    {
        try
        {
            nlohmann::json j = nlohmann::json::parse(line);

            if (!j.contains("word")) continue;

            // add to trie & db
			std::string lemma = j["word"];
            addWord(lemma); 
			int word_id = m_db.getWordID(lemma);

            // definitions
            if (j.contains("senses"))
            {
                for (auto& sense : j["senses"])
                {
                    if (sense.contains("glosses"))
                    {
                        for (auto& g : sense["glosses"])
                        {
                            m_db.insertSense(word_id,
                                           j.value("pos", ""),
                                           g.get<std::string>());
                        }
                    }
                }
            }

            // etymology
            if (j.contains("etymology_text"))
            {
			    continue; // delete
                m_db.insertEtymology(word_id, j["etymology_text"]);
            }

            // forms (plural & alt spellings)
            if (j.contains("forms"))
            {
				continue; // delete
                for (auto& f : j["forms"])
                {
                    std::string form = f["form"];
                    std::string tag = f["tags"][0];
                    m_db.insertForm(word_id, form, tag);
                }
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "Skipping bad line: " << e.what() << "\n";
        }
    }

    return true;
}

#if 0
void Dictionary::load(const string &filename)
{
	std::ifstream file(filename);
	if (!file) throw std::runtime_error("Error: Cannot open external dictionary.\n");

	string word;
	while (file >> word)
	{
		addWord(word);
	}
}

void Dictionary::save(const string &filename) const 
{
	// overwrite dictionary.txt with all words from trie
	std::ofstream file(filename);	
	if (!file) throw std::runtime_error("Error: Cannot open internal dictionary.\n");
	
	// "snapshot" trie in file
	m_trie.writeAll(file);		
}

bool Dictionary::opencsv(const string &filename)
{
    // open file
    std::ifstream file(filename);
	if (!file) throw std::runtime_error("Error: Cannot open file.");

    // load information

	return true;
}

bool Dictionary::opentsv(const string &filename)                                
{
	// open file
	std::ifstream file(filename);
	if (!file) throw std::runtime_error("Error: Cannot open file.");
	
	// load information

	return true;
}

bool Dictionary::openjson(const string &filename)
{
	return true;
}

bool Dictionary::openxml(const string &filename)
{
	return true;
}
#endif
