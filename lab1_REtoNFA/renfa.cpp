#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <stack>

using namespace std;

int init()
{
    static int i = -1;
    i++;
    return i;
}

class NFA
{
public:
    int start, final;
    vector<int> finish;
    unordered_map<int, unordered_map<char, unordered_set<int>>> delta;

    NFA(char c)
    {
        if (c == '~') //~ denotes phi
        {
            start = init();
            final = init();
            finish = vector<int>();
            finish.push_back(final);
            delta[start] = unordered_map<char, unordered_set<int>>();
            delta[final] = unordered_map<char, unordered_set<int>>();
        }
        else if (c == 'e') //e denotes epsilon
        {
            start = init();
            final = start;

            finish = vector<int>();
            finish.push_back(final);

            delta[start] = unordered_map<char, unordered_set<int>>();
        }
        else
        {
            start = init();
            final = init();

            finish = vector<int>();
            finish.push_back(final);

            delta[start] = unordered_map<char, unordered_set<int>>();
            delta[final] = unordered_map<char, unordered_set<int>>();

            delta[start][c] = unordered_set<int>();
            delta[start][c].insert(final);
        }
    }

    NFA(int s, vector<int> f, NFA *left, NFA *right = NULL)
    {
        start = s;
        finish = f;
        delta = left->delta;
        if (right)
        {
            for (auto it = right->delta.begin(); it != right->delta.end(); it++)
            {
                delta[it->first] = it->second;
            }
        }
    }

    void printNFA()
    {
        cout << start << "\n";
        for (int x : finish)
        {
            cout << x << " ";
        }
        cout << "\n";

        for (auto i = delta.begin(); i != delta.end(); i++)
        {
            for (auto j = i->second.begin(); j != i->second.end(); j++)
            {
                cout << i->first << " " << j->first << " : ";
                for (auto k = j->second.begin(); k != j->second.end(); k++)
                    cout << *k << " ";
                cout << "\n";
            }
        }
    }
};

NFA star(NFA l)
{
    NFA n(init(), l.finish, &l);

    n.delta[n.start]['e'] = unordered_set<int>();
    n.delta[n.start]['e'].insert(l.start);

    for (int x : n.finish)
    {
        n.delta[x]['e'] = unordered_set<int>();
        n.delta[x]['e'].insert(l.start);
    }

    n.finish.push_back(n.start);

    return n;
}
NFA dot(NFA l, NFA r)
{
    NFA n(l.start, r.finish, &l, &r);

    for (int x : l.finish)
    {
        n.delta[x]['e'].insert(r.start);
    }

    return n;
}
NFA oroperation(NFA l, NFA r)
{
    l.finish.insert(l.finish.end(), r.finish.begin(), r.finish.end());

    NFA n(init(), l.finish, &l, &r);

    n.delta[n.start]['e'] = unordered_set<int>();
    n.delta[n.start]['e'].insert(l.start);
    n.delta[n.start]['e'].insert(r.start);

    return n;
}

int main(int argc, char **argv)
{
    string regex, re, postRe;

    if (argc <= 1)
    {
        printf("Enter the regular expression as a command line argument\n");
        return 0;
    }
    else
        regex = argv[1];

    cout << argv[1] << "\n";

    if (!regex.empty())
        re += regex[0];

    for (int i = 1; i < regex.length(); i++)
    {
        if (regex[i - 1] != '+' && regex[i - 1] != '(' && regex[i] != '+' && regex[i] != '*' && regex[i] != ')')
            re += '.';
        re += regex[i];
    }

    unordered_map<char, int> precedence;
    precedence['+'] = 0;
    precedence['.'] = 1;
    precedence['*'] = 2;

    stack<char> st;

    for (int i = 0; i < re.length(); i++)
    {
        if (re[i] == '(')
        {
            st.push('(');
        }
        else if (re[i] == '+' || re[i] == '.' || re[i] == '*')
        {
            if (st.empty())
                st.push(re[i]);
            else if (st.top() == '(')
                st.push(re[i]);
            else if (precedence[re[i]] > precedence[st.top()])
                st.push(re[i]);
            else
            {
                while (!st.empty() && st.top() != '(' && precedence[st.top()] >= precedence[re[i]])
                {
                    postRe += st.top();
                    st.pop();
                }
                st.push(re[i]);
            }
        }
        else if (re[i] == ')')
        {
            while (!st.empty() && st.top() != '(')
            {
                postRe += st.top();
                st.pop();
            }
            if (!st.empty())
                st.pop();
        }
        else
            postRe += re[i];
    }
    while (!st.empty())
    {
        postRe += st.top();
        st.pop();
    }
    // cout << "The postfix notation of given regex is: " << postRe << "\n";

    stack<NFA> nfastack;
    for (int i = 0; i < postRe.length(); i++)
    {
        if (postRe[i] == '+')
        {
            NFA r = nfastack.top();
            nfastack.pop();
            NFA l = nfastack.top();
            nfastack.pop();
            nfastack.push(oroperation(l, r));
        }
        else if (postRe[i] == '.')
        {
            NFA r = nfastack.top();
            nfastack.pop();
            NFA l = nfastack.top();
            nfastack.pop();

            nfastack.push(dot(l, r));
        }
        else if (postRe[i] == '*')
        {
            NFA n = nfastack.top();
            nfastack.pop();
            nfastack.push(star(n));
        }
        else
        {
            nfastack.push(NFA(postRe[i]));
        }
    }
    nfastack.top().printNFA();

    return 0;
}