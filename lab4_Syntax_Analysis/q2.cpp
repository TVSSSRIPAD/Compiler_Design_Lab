#include <bits/stdc++.h>
using namespace std;

class ProduceLeftFactoredGrammar
{
public:
    map<string, vector<string>> grammar;
    queue<string> newSym;

    ProduceLeftFactoredGrammar(map<string, vector<string>> gr)
    {
        grammar = gr;

        char j = 'A';
        for (int i = 0; i < 26; i++)
        {
            string tt;
            tt += j;
            tt += "'";

            newSym.push(tt);

            j += 1;
        }
    }

    bool replace(std::string &str, const std::string &from, const std::string &to)
    {
        size_t start_pos = str.find(from);
        if (start_pos == std::string::npos)
            return false;
        str.replace(start_pos, from.length(), to);
        return true;
    }

    map<string, vector<string>> factorize(string symbol)
    {
        vector<string> allProds = grammar[symbol];
        map<string, vector<string>> res;

        if (allProds.size() == 1)
        {
            return res;
        }

        // store the new strings for the same symbol
        vector<string> newProductions;

        int idx = 0, n = allProds.size();
        char chx = allProds[0].at(0);
        for (int i = 1; i < n; i++)
        {
            char curr_chx = allProds[i].at(0);
            if (curr_chx != chx)
            {
                if (idx == i - 1)
                {
                    newProductions.push_back(allProds[idx]);
                }
                else
                {
                    // add new production after finding the longest common prefix
                    int z = 0;
                    string s1, s2;
                    s1 = allProds[idx];
                    s2 = allProds[i - 1];
                    // cout << "\nmatching s1 = " << s1 << " and s2 = " << s2 << "\n";
                    for (z = 0; z < min(s1.length(), s2.length()); z++)
                    {
                        if (s1.at(z) != s2.at(z))
                        {
                            break;
                        }
                    }

                    string thePrefix = s1.substr(0, z);
                    // cout << "z = " << z << " and prefix: " << thePrefix;
                    string newSymbol = newSym.front();
                    newSym.pop();

                    // replacing earlier set of productions by a simgle production for the original symbol
                    newProductions.push_back(thePrefix + newSymbol);

                    // add the set of productions to a new symbol
                    vector<string> newSymbolProds;
                    for (z = idx; z < i; z++)
                    {
                        string newstring;
                        replace(allProds[z], thePrefix, "");
                        newstring = allProds[z];
                        newSymbolProds.push_back(newstring.length() == 0 ? "_epsilon" : newstring);
                    }

                    // add this new symbol + its prods to the hashmap
                    res[newSymbol] = newSymbolProds;
                }

                idx = i;
                chx = curr_chx;
                if (idx == n - 1)
                    newProductions.push_back(allProds[idx]);
            }
            else
            {
                // the first-char matched till the last string!
                if (i == n - 1)
                {
                    // add new production after finding the longest common prefix
                    int z = 0;
                    string s1, s2;
                    s1 = allProds[idx];
                    s2 = allProds[i];
                    // cout << "\nmatching s1 = " << s1 << " and s2 = " << s2 << " oo 2\n";
                    for (z = 0; z < min(s1.length(), s2.length()); z++)
                    {
                        if (s1.at(z) != s2.at(z))
                        {
                            break;
                        }
                    }

                    string thePrefix = s1.substr(0, z);
                    // cout << "z = " << z << " and prefix: " << thePrefix << "\n";
                    string newSymbol = newSym.front();
                    newSym.pop();
                    // cout << "New symbol is " << newSymbol << "\n";

                    // replacing earlier set of productions by a single production for the original symbol
                    newProductions.push_back(thePrefix + newSymbol);

                    // add the set of productions to a new symbol
                    vector<string> newSymbolProds;
                    for (z = idx; z <= i; z++)
                    {
                        replace(allProds[z], thePrefix, "");
                        string newstring = allProds[z];
                        // cout << "NewString is " << newstring << "\n";
                        newSymbolProds.push_back(newstring.length() == 0 ? "_epsilon" : newstring);
                    }

                    // add this new symbol + its prods to the hashmap
                    res[newSymbol] = newSymbolProds;
                }
            }
        }

        // changing the original set of productions for this symbol
        grammar[symbol] = newProductions;
        // printGrammar();
        return res;
    }

    void run()
    {
        bool done = false;
        while (!done)
        {
            done = true;
            map<string, vector<string>> newKeysToPut;

            vector<string> theKeys;
            for (auto it = grammar.begin(); it != grammar.end(); ++it)
            {
                theKeys.push_back(it->first);
            }
            for (string symbol : theKeys)
            {
                vector<string> allProds = grammar[symbol];
                sort(allProds.begin(), allProds.end());
                grammar[symbol] = allProds;

                map<string, vector<string>> temp = factorize(symbol);

                if (temp.size() != 0)
                {
                    done = false;
                    newKeysToPut.insert(temp.begin(), temp.end());
                }
            }

            grammar.insert(newKeysToPut.begin(), newKeysToPut.end());
        }
        cout << "Left Factored Grammar is :\n";
        printGrammar();
    }

    void printGrammar()
    {
        for (auto it = grammar.begin(); it != grammar.end(); ++it)
        {
            cout << "Key " << it->first << " --> ";
            for (string s : it->second)
            {
                cout << s << " ";
            }
            cout << "\n";
        }
    }
};

int main()
{
    map<string, vector<string>> grammar;
    cout << "Enter the grammar:\n";

    while (true)
    {
        cout << "Enter symbol or -1 to EXIT: \n";
        string theSymbol;
        getline(cin, theSymbol);

        if (theSymbol == "-1")
        {
            break;
        }

        cout << "Enter Productions separated by spaces: \n";
        string theProduction;
        getline(cin, theProduction);
        vector<string> allProductions;
        istringstream ss(theProduction);

        string word;

        while (ss >> word)
        {
            allProductions.push_back(word);
        }

        grammar[theSymbol] = allProductions;
    }
    ProduceLeftFactoredGrammar lf(grammar);

    lf.run();
}