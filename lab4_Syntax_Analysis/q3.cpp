#include <bits/stdc++.h>
using namespace std;

class RecursiveDescentParsing
{
public:
    map<string, vector<string>> grammar;
    string startSymbol;
    string inputString;
    int currentIndex;

    RecursiveDescentParsing(map<string, vector<string>> gr, string start, string input, int idx)
    {
        grammar = gr;
        startSymbol = start;
        inputString = input;
        currentIndex = idx;
    }

    bool replace(std::string &str, const std::string &from, const std::string &to)
    {
        size_t start_pos = str.find(from);
        if (start_pos == std::string::npos)
            return false;
        str.replace(start_pos, from.length(), to);
        return true;
    }

    bool parse(string symbol)
    {
        int pIndex = currentIndex;
        bool epsilonFound = false;

        // choosing production and derive
        for (string aProd : grammar[symbol])
        {
            int initIndex = currentIndex;
            cout << "------- Using production : " << aProd << " of symbol: " << symbol << "-----\n";

            // match each char of that production
            for (int i = 0; i < aProd.length(); i++)
            {
                string theSymbol;
                theSymbol += aProd.at(i);
                if (grammar.find(theSymbol) != grammar.end())
                {
                    //  Non Terminal found
                    if (!parse(theSymbol))
                    {
                        currentIndex = initIndex;
                        break;
                    }
                }
                else if (theSymbol == "e")
                {
                    // nothing
                    epsilonFound = true;
                    cout << "Making an epsilon transition for symbol: " << symbol << " and aProd: " << aProd << "\n";
                }
                else if ((currentIndex < inputString.length()) && (aProd.at(i) == inputString.at(currentIndex)))
                {
                    //terminal - matched
                    cout << "The terminal symbol matched at index " << currentIndex << "\n ";
                    currentIndex++;
                }
                else
                {
                    // terminal - not matched
                    if (currentIndex < inputString.length())
                    {
                        cout << "Mismatch for Prod: " << aProd << " and inputChar = " << inputString[currentIndex] << " at index" << currentIndex << "... backtrack now!\n";
                    }
                    else
                    {
                        cout << "Input exhausted for Prod: " << aProd << " and currentIdex: " << currentIndex << "\n";
                    }

                    currentIndex = initIndex;
                    break;
                }
            }
        }

        if ((pIndex == currentIndex) && (!epsilonFound))
        {
            cout << "None of the productions of symbol " + symbol + " could derive from the index " << currentIndex << "\n";
            return false;
        }

        return true;
    }

    void run()
    {
        cout << "Taking " << startSymbol << " as start symbol and " << inputString << " as inputString\n";
        if (parse(startSymbol) && (currentIndex == inputString.length()))
        {
            cout << "PARSING SUCCESSFUL\n";
        }
        else
        {
            cout << "PARSING FAILED.\n";
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
    string startSymbol, inputString;

    cout << "Enter Start Symbol:\n";
    getline(cin, startSymbol);

    cout << "Enter inputString:\n";
    getline(cin, inputString);

    RecursiveDescentParsing rdp(grammar, startSymbol, inputString, 0);

    rdp.run();
}