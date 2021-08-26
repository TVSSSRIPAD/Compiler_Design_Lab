#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <sstream>
using namespace std;
int main()
{

    freopen("dfamin.txt", "r", stdin);

    int initStates;
    // cout << "Enter number of initial States:\n";
    cin >> initStates;
    char a[initStates][3];
    // cout << "Enter transition function as : A B C where B is 0 transition from A and C is 1 transition from A\n";
    for (int i = 0; i < initStates; i++)
    {
        char t, t0, t1;
        cin >> t >> t0 >> t1;
        a[i][0] = t;
        a[i][1] = t0;
        a[i][2] = t1;
    }
    cout << "Given initial transition function is:\n";
    cout << "State   0 1\n";
    for (int i = 0; i < initStates; i++)
    {
        cout << a[i][0] << "\t" << a[i][1] << " " << a[i][2] << "\n";
    }

    char start;

    // cout << "Enter start state:\n";
    cin >> start;

    string fin;
    // cout << "Enter finish states seperated by spaces:\n";
    cin.ignore();

    getline(cin, fin);

    unordered_set<char> final = unordered_set<char>();
    std::istringstream iss(fin);
    char temp;
    while (iss >> temp)
    {
        final.insert(temp);
    }

    map<pair<char, char>, vector<pair<char, char>>> m;
    int count = 0;
    for (int i = 0; i < initStates; i++)
    {
        for (int j = i + 1; j < initStates; j++)
        {
            char x, y;
            x = a[i][1];
            y = a[j][1];
            if (x > y)
                swap(x, y);
            m[make_pair(x, y)].insert(m[make_pair(x, y)].begin(), make_pair(a[i][0], a[j][0]));
            x = a[i][2];
            y = a[j][2];
            if (x > y)
                swap(x, y);
            m[make_pair(x, y)].insert(m[make_pair(x, y)].begin(), make_pair(a[i][0], a[j][0]));
            count++;
        }
    }
    int mat[initStates][initStates];
    for (int i = 0; i < initStates; i++)
    {
        for (int j = 0; j < initStates; j++)
        {
            mat[i][j] = 0;
        }
    }

    queue<pair<char, char>> q;

    // First iteration
    for (int i = 0; i < initStates; i++)
    {
        for (int j = i + 1; j < initStates; j++)
        {
            if (final.find(a[i][0]) == final.end() && final.find(a[j][0]) != final.end())
            {
                mat[i][j] = 1;
                q.push({a[i][0], a[j][0]});
            }
            else if (final.find(a[i][0]) != final.end() && final.find(a[j][0]) == final.end())
            {
                mat[i][j] = 1;
                q.push({a[i][0], a[j][0]});
            }
        }
    }

    while (!q.empty())
    {
        pair<char, char> top = q.front();
        q.pop();
        mat[top.first - 'A'][top.second - 'A'] = 1;
        for (auto it : m[top])
        {

            if (mat[it.first - 'A'][it.second - 'A'] == 0)
            {

                mat[it.first - 'A'][it.second - 'A'] = 1;
                q.push(it);
            }
        }
    }
    // cout << "Matrix is \n";
    // cout << "  ";
    // for (int i = 1; i < initStates; i++)
    // {
    //     cout << (char)('A' + i) << " ";
    // }
    // cout << "\n";
    // for (int i = 0; i < initStates - 1; i++)
    // {
    //     cout << (char)('A' + i) << " ";
    //     for (int j = 1; j < initStates; j++)
    //     {
    //         cout << mat[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
    for (int i = 0; i < initStates - 1; i++)
    {
        for (int j = i + 1; j < initStates; j++)
        {
            if (mat[i][j] == 0)
            {
                cout << "The states " << (char)('A' + i) << " , " << (char)('A' + j) << " are equivalent\n";
            }
        }
    }

    unordered_map<char, int> fstate;
    count = 0;
    for (int i = 0; i < initStates; i++)
    {
        fstate[a[i][0]] = count;
        count++;
    }
    for (int i = 0; i < initStates - 1; i++)
    {
        for (int j = i + 1; j < initStates; j++)
        {
            if (mat[i][j] == 0)
            {
                fstate['A' + j] = fstate['A' + i];
            }
        }
    }
    unordered_map<int, int> seen;
    cout << "The Reduced Transition function is:\n";
    for (int i = 0; i < initStates; i++)
    {
        char t, t0, t1;

        t = a[i][0];
        t0 = a[i][1];
        t1 = a[i][2];

        if (seen.find(fstate[t]) == seen.end())
        {
            seen[fstate[t]] = 1;
            t = +'A' + fstate[t];
            t0 = 'A' + fstate[t0];
            t1 = 'A' + fstate[t1];

            cout << t << " " << t0 << " " << t1 << "\n";
        }
    }
}