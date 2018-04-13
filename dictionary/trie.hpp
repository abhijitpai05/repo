#ifndef _TRIE_HPP_
#define _TRIE_HPP_
/*
 * Below is the implementation of TRIE data structure.
 * Some of it's capabilities includes:
 *  1. Add key(string)/value(T)
 *  2. Delete key and its corresponding value
 *  3. Search for key
 *  4. Find all prefix matching keys
 *
 *  This class can be used to impement a 'word dictionary' or 'telephone directory/book'
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

enum { MAX_NODES = 26 };

template <typename T>
class Trie
{
    public:

        Trie();
        ~Trie();

        bool insert(const string& key, const T& value);
        pair<bool,T> find(const string& key);
        bool prefix_match(const string& prefix, vector<T>& outData);
        bool remove(const string& key);

    private:

        struct Node {
            T _value;
            bool _has_val;
            struct Node* _children[MAX_NODES];
            Node();
            ~Node();
        };

        Node* _root;

        // functions
        Node* getNode();
        bool _insert_value(Node* parent, const char* key,  const T& value);
        pair<bool,T> _find_value(Node* parent, const char* key);
        bool _prefix_match(Node* parent, const char* prefix, int pos, vector<T>& outData);
        bool _get_all_matching_child_keys(Node* parent, const char* prefix, vector<T>& outData);
        int _remove_value(Node* parent, const char* key);
        void _cleanup(Node *parent);

        // disable the copy constructor and assignement operator
        Trie(const Trie&);
        Trie& operator= (const Trie&);
};

template <typename T>
Trie<T>::Trie():_root(NULL){ }

template <typename T>
bool Trie<T>::insert(const string& key, const T& value)
{
    if(!_root) {
        _root = getNode();
    }
    return _insert_value(_root, key.c_str(), value);  
}

template <typename T>
bool Trie<T>::_insert_value(Node* parent, const char* key, const T& value)
{
    if(!parent) {
        // we are lost
        return false;
    }

    // reached end of the string??
    if (*key == '\0') {
        //fill up the parent with right value
        // case: if the value already exist, we overwrite it. no harm.
        parent->_value = value;
        parent->_has_val = true;
        return true;
    }

    // continue to find the right position to insert
    int index = *key - 'a';
    if ((0 > index) || (index > MAX_NODES)) {
        // we don't expect the key to be anything other than small case letters [a-z]
        return false;
    }
    if (parent->_children[index] == NULL) {
        // allocate new Node
        parent->_children[index] = getNode();
    }

    // continue to recurse for rest of the characters
    return _insert_value(parent->_children[index], key+1, value);
}

template <typename T>
pair<bool, T> Trie<T>::find(const string& key)
{
    return _find_value(_root, key.c_str());
}

template <typename T>
pair<bool, T> Trie<T>::_find_value(Node* parent, const char* key)
{
    if (!parent) {
        T t {};
        return (make_pair(false, t));
    }

    // reached end of the key??
    if (*key == '\0') {
        if (parent->_has_val) {
            return(make_pair(true, parent->_value));
        }
    }
    // get the right child
    int index = *key - 'a';
    if ((0 > index) || (index > MAX_NODES) || (parent->_children[index] == NULL)) {
        T t {};
        return (make_pair(false, t));
    }

    return _find_value(parent->_children[index], key+1);
}

template <typename T>
bool Trie<T>::prefix_match(const string& key, vector<T>& outData)
{
    return _prefix_match(_root, key.c_str(), 0, outData); 
}

template <typename T>
bool Trie<T>::_get_all_matching_child_keys(Node* parent, const char* prefix, vector<T>& outData)
{
    bool rc = true;
    string pref(prefix);

    if (parent->_has_val) {
        outData.push_back(pref);
    }

    // capture all the values including current one
    for (int i=0; i<MAX_NODES; i++) {
        if (parent->_children[i] != NULL) {
            char c = 'a' + i;
            string newprefix;
            newprefix = string(pref) + c;
            rc = _get_all_matching_child_keys(parent->_children[i], newprefix.c_str(), outData);
        }
    }
    return rc;
}

template <typename T>
bool Trie<T>::_prefix_match(Node* parent, const char* prefix, int pos, vector<T>& outData)
{
    if (!parent) {
        return false;
    }

    // reached end of the key??
    if (*(prefix+pos) == '\0') {
        // get all the matching keys
        return _get_all_matching_child_keys(parent, prefix, outData);
    }
    // get the right child
    int index = *(prefix+pos) - 'a';
    if ((0 > index) || (index > MAX_NODES) || (parent->_children[index] == NULL)) {
        return false;
    }

    return _prefix_match(parent->_children[index], prefix, pos+1, outData);
}

template <typename T>
bool Trie<T>::remove(const string& key)
{
    int rc = _remove_value(_root, key.c_str());
    return ((rc >=0)?true:false);
}

template <typename T>
int Trie<T>::_remove_value(Node* parent, const char* key)
{
    if(!parent) {
        return -1;
    }

    // is this end of the key??
    if (*key == '\0') {
        // key does not have entry
        if (parent->_has_val == false) {
            return -1;
        }

        // key exist, and also part of bigger word
        for (int i = 0; i < MAX_NODES; i++) {
            if (parent->_children[i] != NULL) {
                parent->_has_val = false;
                // false?? because we still have children using the node
                return 0;
            }
        }

        // key can be deleted
        return 1;
    }

    int index = *key - 'a';
    if ((0 > index) || (index > MAX_NODES) || (parent->_children[index] == NULL)) {
        return -1;
    }

    int rc = _remove_value(parent->_children[index], key+1);
    if(rc > 0) {
        delete parent->_children[index];
        parent->_children[index] = NULL;

        if (parent->_has_val == false) {
            for (int i=0; i < MAX_NODES; i++) {
                if (parent->_children[i] != NULL) {
                    //rc = -1;
                    break;
                }
            }
        } 
    }
    return rc;
}

template <typename T>
typename Trie<T>::Node* Trie<T>::getNode()
{
    // allocate a Node
    Node* node = new Node();
    return node;
}

template <typename T>
void Trie<T>::_cleanup(Node *parent)
{
    if (!parent) {
        return;
    }

    for (int i=0; i<MAX_NODES; i++) {
        if(parent->_children[i] != NULL) {
            _cleanup(parent->_children[i]);
            delete parent->_children[i];
            parent->_children[i] = NULL;
        }
    }
}

template <typename T>
Trie<T>::~Trie()
{
    _cleanup(_root);
}

template <typename T>
Trie<T>::Node::Node(): _value{}, _has_val(false)
{
    // initialize all children to NULL
    for (int i=0; i<MAX_NODES; i++) {
        _children[i] = NULL;
    }
}
template <typename T>
Trie<T>::Node::~Node(){ }

#endif
