#include "SpellChecker.h"
#include "Utils.h"

SpellChecker::SpellChecker(const Dictionary &dict) : m_dict{dict} {}

bool SpellChecker::check(std::string_view word) const
{
	// returns false if word is mispelled or not found in dictionary
	return (!m_dict.search(word) ? false : true);
}

std::vector<std::string> SpellChecker::suggest(std::string_view prefix) const 
{ 
	std::vector<std::string> results;

	if (m_dict.isTrieEmpty()) return results;	
	
	if (!prefix.empty()) m_dict.suggestFromPrefix(prefix, results, dct::g_maxSuggest);

	return results; 
}

std::vector<std::string> SpellChecker::correct(std::string_view word) const 
{ // implement
	std::vector<std::string> results;
	return results;
}

std::string SpellChecker::autofill(std::string_view word) const 
{ // implement
	std::string result {word};
	return result;
}

void SpellChecker::printSuggest(const std::vector<std::string> &out) const
{
	if (out.empty()) 
	{
		return;
	} 
	else
	{
		for (const auto &word : out)
		{
			std::cout << "→ " << word << '\n'; 
		}
	}
}
