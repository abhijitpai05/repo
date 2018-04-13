#ifndef _DICTIONARY_HPP_
#define _DICTIONARY_HPP_
/*
 * Below is the implementation of Dictinary.
 * It uses a 'TRIE' as its underlying data structure for efficient
 * storage and retrieval of information.
 * Some of the capabilities it provides are:
 *  1. Add word to dictionary
 *  2. Delete word to dictionary
 *  3. Find a full word
 *  4. Find all words with matching prefix
 */

#include "trie.hpp"

class Dictionary
{
    public:
        Dictionary();
        ~Dictionary();
        bool build (const string& filename);
        bool addword (const string& word, const string& meaning);
        pair<bool, string> lookup (const string& word);
        bool prefixmatch (const string& prefix, vector<string>& words);
        bool deleteword (const string& word);
    private:
        Trie <string> _trie;
};

#endif
