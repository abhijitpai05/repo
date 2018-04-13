
#include <iostream>
#include <string>
#include <fstream>
#include "trie.hpp"
#include "dictionary.hpp"

using namespace std;

Dictionary::Dictionary()
{
}

Dictionary::~Dictionary()
{
}

bool Dictionary::build(const string& filename)
{
    // todo: add code to load from file
    return false;
}

bool Dictionary::addword(const string& word, const string& meaning)
{
    return _trie.insert(word, meaning);
}

pair<bool, string> Dictionary::lookup(const string& word)
{
    return _trie.find(word);
}

bool Dictionary::prefixmatch(const string& prefix, vector<string>& words)
{
    return _trie.prefix_match(prefix, words);
}

bool Dictionary::deleteword(const string& word)
{
    return _trie.remove(word);
}
