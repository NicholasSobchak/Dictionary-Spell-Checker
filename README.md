Dictionary & Spell Checker (Trie + Database Engine)

This project is a C++ dictionary and spell-checking engine powered by a Trie (prefix tree) and a relational database. It loads large Wiktionary-style JSON data, organizes it efficiently, and provides fast word lookup, spell checking, autocomplete, and rich linguistic information.

Unlike a basic spell checker that only stores words, this system understands:

Lemmas vs word forms (run → running, ran, runs)

Multiple definitions (senses) per word

Parts of speech

Examples

Synonyms and antonyms

Etymology

Alternate spellings and plurals

🚀 What This Project Demonstrates

This project applies core data structures and database design to a real-world language problem.

You gain experience with:

Trie implementation (O(L) lookup time)

Recursion and node traversal

JSON parsing of large datasets

Relational database schema design

Mapping linguistic data into structured storage

Designing fast lookup + rich data retrieval systems

Building a mini dictionary engine similar to those used in search engines and word processors

🧠 Core Idea

The Trie is used for speed.
The Database is used for depth of information.

User searches: "running"
        │
        ▼
      Trie
        │
 finds lemma "run" using stored forms
        │
        ▼
   Database (word_id)
        │
        ▼
 Returns definitions, examples, synonyms, etymology...

🏗️ System Architecture
1. Trie Structure (Fast Lookup)

The Trie performs prefix searching, spell checking, and autocomplete.

(root)
  ├── r
  │    └── u
  │         └── n  (word_id = 42)
  ├── d
  │    └── i
  │         └── c ...


Each completed word in the Trie stores a word_id that links to the database.

2. Database Structure (Word Information)

The database stores all rich linguistic data for each word.

words
word_id | lemma
42      | run
51      | dictionary

forms
word_id | form       | tag
42      | running    | present-participle
42      | ran        | past
42      | runs       | third-person

senses
sense_id | word_id | pos  | definition
1        | 42      | verb | to move quickly
2        | 42      | noun | an act of running


Additional tables store:

examples

synonyms

antonyms

etymology

3. In-Memory Word Structure

During runtime, a WordInfo struct mirrors the database for fast access:

WordInfo
 ├─ lemma: "run"
 ├─ id: 42
 ├─ etymology: [...]
 └─ senses:
      ├─ pos: verb
      │   ├─ definition: "to move quickly"
      │   ├─ examples: [...]
      │   ├─ synonyms: [...]
      │   └─ antonyms: [...]


This avoids constant database queries while the program runs.

✨ Features

Load large dictionary JSON files (Wiktionary format)

Build Trie from lemmas and forms

Spell check words

Suggest similar words using Trie traversal

Prefix autocomplete

Retrieve full dictionary entries:

Definitions

Parts of speech

Examples

Synonyms / antonyms

Etymology

Handle alternate spellings and plurals

Alphabetical dictionary display

⚡ Performance

Trie search time is O(L) where L = length of the word, making lookups extremely fast even with very large dictionaries.

The database allows scalable storage of millions of word relations without slowing down lookup speed.

🧩 Real-World Comparison

This system mimics how:

Search engines autocomplete words

Phone keyboards predict words

Word processors perform spell checking

Online dictionaries organize word data

🛠️ Technologies Used

C++

Trie (prefix tree)

SQLite / relational database

nlohmann JSON parser

File I/O and data parsing

🎯 Project Goal

To build a data-structure-driven dictionary engine that combines:

Fast lookup (Trie) + Rich linguistic data (Database)

into a practical, scalable spell checker and dictionary system.
