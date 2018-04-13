#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "dictionary.hpp"
using namespace std;

int main()
{
    int rc = false;
    Dictionary d;
    // build vocabulary
    d.addword(string("happy"), string("feeling or showing pleasure or contentment"));
    d.addword(string("monologue"), string("a long speech by one actor in a play or movie, or as part of a theatrical or broadcast program"));
    d.addword(string("pursuit"), string("the action of following or pursuing someone or something"));
    d.addword(string("mono"), string("only one, sigle"));
    d.addword(string("aesthetic"), string("concerned with beauty or the appreciation of beauty"));
    d.addword(string("monopoly"), string("the exclusive possession or control of the supply or trade in a commodity or service"));
    d.addword(string("vital"), string("absolutely necessary or important; essential"));
    d.addword(string("passion"), string("strong and barely controllable emotion"));
    d.addword(string("monochrome"), string("a photograph or picture developed or executed in black and white or in varying tones of only one color"));

    // find several words
    string w1("happy");
    string exp("feeling or showing pleasure or contentment");

    auto res = d.lookup(w1);
    if(!res.first) {
        cout << "Error: lookup() failed for word " << w1 << endl;
    }
    // lsit all the word(s) that do prefix match
    vector <string> outdata;
    string prefix("mono");
    rc = d.prefixmatch(prefix, outdata);
    if(rc) {
        cout << "Words matchiing with prefix \"" << prefix << "\"" << endl;
        for(auto elem : outdata) {
            cout << elem << endl;
        }
    } else {
        cout << "No words found matching the prefix \"" << prefix << "\"" << endl;
    }

    // delete the word from dictionary
    string w2("vital");
    rc = d.deleteword(w2);
    if(!rc) {
        cout << "Failed to delete existing word " << w2 << endl;
    }

    // delete word that's not added
    string w3("aspen");
    rc = d.deleteword(w3);
    if(rc) {
        cout << "Failed! deleted a non-existing word " << w3 << endl;
    }

    return 0;
}
