#include <iostream>
#include <unordered_set>
#include <string>
using namespace std;

unordered_set<string> keywords;

class Token
{
public:
    string type;
    string lexem;

    Token(string t, string lex)
    {
        type = t;
        lexem = lex;
    }
};

Token fail()
{
    Token t = Token("token_mismatch", "-1");
    return t;
}

string getToken(string lexem)
{
    if (keywords.find(lexem) != keywords.end())
        return lexem;
    return "Identifier";
}
string getLexem(string lexem)
{
    if (keywords.find(lexem) != keywords.end())
        return "";
    return lexem;
}

Token getRelop(int &position, string str)
{
    char c;
    int n = str.size(), state = 0;
    while (1)
    {
        switch (state)
        {
        case 0:
            c = str[position++];
            if (c == '<')
                state = 1;
            else if (c == '=')
                state = 5;
            else if (c == '>')
                state = 6;
            else
                return fail();
            break;

        case 1:
            c = str[position++];
            if (c == '=')
            {
                state = 2;
            }
            else if (c == '>')
            {
                state = 3;
            }
            else
            {
                state = 4;
            }
            break;
        case 2:
            return Token("Relop", "<=");
            break;
        case 3:
            return Token("Relop", "<>");
            break;
        case 4:
            position--; //Retracting State
            return Token("Relop", "<");
            break;
        case 5:
            return Token("Relop", "=");
            break;
        case 6:
            c = str[position++];
            if (c == '=')
                state = 7;
            else
                state = 8;
            break;
        case 7:
            return Token("Relop", ">=");
            break;
        case 8:
            position--; //Retracting State
            return Token("Relop", ">");
            break;
        }
    }
}

Token getIdentifier(int &position, string str)
{
    char c;
    int n = str.size(), state = 9, start = position;
    while (1)
    {
        switch (state)
        {
        case 9:
            c = str[position++];
            if (isalpha(c))
                state = 10;
            else
                return fail();
            break;

        case 10:
            c = str[position++];
            if (isalpha(c) || isdigit(c))
            {
                state = 10;
            }
            else
            {
                state = 11;
            }
            break;
        case 11:
            position--; //Retracting state
            string lex = str.substr(start, position - start);
            return Token(getToken(lex), getLexem(lex));
        }
    }
}

Token getNumber(int &position, string str)
{
    char c;
    int n = str.size(), state = 12, start = position;
    while (1)
    {
        switch (state)
        {
        case 12:
            c = str[position++];
            if (isdigit(c))
                state = 13;
            else
                return fail();
            break;
        case 13:
            c = str[position++];
            if (isdigit(c))
                state = 13;
            else if (c == '.')
                state = 14;
            else if (c == 'E')
                state = 16;
            else
                state = 20;
            break;
        case 14:
            c = str[position++];
            if (isdigit(c))
                state = 15;
            else
                return fail();
            break;
        case 15:
            c = str[position++];
            if (isdigit(c))
                state = 15;
            else if (c == 'E')
                state = 16;
            else
                state = 21;
            break;
        case 16:
            c = str[position++];
            if (isdigit(c))
                state = 18;
            else if (c == '+' || c == '-')
                state = 17;
            else
                return fail();
            break;
        case 17:
            c = str[position++];
            if (isdigit(c))
                state = 18;
            else
                return fail();
            break;
        case 18:
            c = str[position++];
            if (isdigit(c))
                state = 18;
            else
                state = 19;
            break;
        case 19:
        case 20:
        case 21:
            position--; //Retracting state
            return Token("Number", str.substr(start, position - start));
            break;
        }
    }
}

Token getSpace(int &position, string str)
{
    char c;
    int n = str.size(), state = 22, start = position;
    while (1)
    {
        switch (state)
        {
        case 22:
            c = str[position++];
            if (c == ' ')
                state = 23;
            else
                return fail();
            break;
        case 23:
            c = str[position++];
            if (c == ' ')
                state = 23;
            else
                state = 24;
            break;
        case 24:
            position--;
            return Token("Space", " ");

            break;
        }
    }
}

int main()
{
    string str;

    cout << "Enter string to be parsed:\n";
    getline(cin, str);

    keywords.insert("if");
    keywords.insert("then");
    keywords.insert("else");

    int n = str.size();

    cout << "Tokens are:-\n";
    for (int i = 0; i < n; i++)
    {
        int start = i;
        Token token = getSpace(start, str);
        if (token.type != "Space")
            start = i;
        else
        {
            start--;
            i = start;
            continue;
        }

        token = getIdentifier(start, str);

        if (token.lexem == "-1")
        {
            start = i;
            token = getRelop(start, str);
            if (token.lexem == "-1")
            {
                start = i;
                token = getNumber(start, str);
                if (token.lexem == "-1")
                {
                    cout << "Token not found" << str[i] << "\n";
                    continue;
                }
            }
        }
        cout << " ( " << token.type << " , " << token.lexem << " ) \n";
        i = start - 1;
    }
}