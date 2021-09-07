#include <bits/stdc++.h>
using namespace std;

class LeftRecursion
{
public:
    map<string, vector<string>> grammar;

    LeftRecursion(map<string, vector<string>> gr)
    {
        grammar = gr;
    }

    void run()
    {
        vector<string> keys;
        for (auto it = grammar.begin(); it != grammar.end(); ++it)
        {
            keys.push_back(it->first);
            // cout << "Key: " << it->first << endl;
        }
        // for every symbol Ai
        for (int i = 0; i < keys.size(); i++)
        {
            string symbol = keys[i];
            // for every previous symbol Aj
            for (int j = 0; j < i; j++)
            {
                string prevSymbol = keys[j];
                vector<string> newProds;
                // for every prod of Ai
                for (string aProd : grammar[symbol])
                {
                    // if Ai -> AjGamma holds
                    if (aProd.rfind(prevSymbol, 0) == 0)
                    {
                        cout << "Substituting : " << prevSymbol << " in " << symbol << "\n";
                        for (string prevProd : grammar[prevSymbol])
                        {
                            replace(aProd, prevSymbol, "");
                            newProds.push_back(prevProd + aProd);
                        }
                    }
                    else
                    {
                        newProds.push_back(aProd);
                    }
                }

                if (newProds.size() != 0)
                {
                    grammar[symbol] = newProds;
                }
            }
            checkLeftRecursion(symbol);
        }
        printGrammar();
    }

    bool replace(std::string &str, const std::string &from, const std::string &to)
    {
        size_t start_pos = str.find(from);
        if (start_pos == std::string::npos)
            return false;
        str.replace(start_pos, from.length(), to);
        return true;
    }

    void checkLeftRecursion(string symbol)
    {
        vector<string> lrs, nlrs;

        for (string prod : grammar[symbol])
        {
            if (prod.rfind(symbol, 0) == 0)
            {
                cout << "Left Recursion Detected. Symbol: " << symbol << " Prod: " << prod << "\n";
                replace(prod, symbol, "");
                lrs.push_back(prod + symbol + "'");
            }
            else
            {
                nlrs.push_back(prod + symbol + "'");
            }
        }

        if (lrs.size() != 0)
        {
            lrs.push_back("e");
            grammar[symbol] = nlrs;
            grammar[symbol + "'"] = lrs;
        }
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
        string symbol;
        getline(cin, symbol);

        if (symbol == "-1")
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

        grammar[symbol] = allProductions;
    }
    LeftRecursion lr(grammar);

    lr.run();
}