
# This file contains code for generating parseTable
# Required Inputs are Grammar, Set of Terminals, Set of Firsts and Follows

def printTable(table, terminals):
    print('%10s' % '', end='')
    for t in terminals:
        if t != '_eps':
            print('%20s' % t, end='')
    print('')
    for k in table.keys():
        print('%10s' % k, end='')
        for j in table[k]:
            print('%20s' % table[k][j], end='')
        print('')


def run(Grammar, Terminals, Firsts, Follows):
    parseTable = {}

    print('Terminals are ')
    print(Terminals)
    for key in Grammar.keys():
        parseTable[key] = {}
        for term in Terminals:
            if term != '_eps':
                parseTable[key][term] = None

    for key in Grammar.keys():
        # print('key is ' + key)
        for prod in Grammar[key]:
            # print('prod is:')
            # print(prod)
            resultset = []
            isepsilon = 1
            # print(prod[0] + ' is 1st')
            if prod[0][0] in Terminals:
                # print('Here for ' + prod[0][0])
                parseTable[key][prod[0][0]] = prod
            elif prod[0] == 'id':
                # print(' Here with ' + prod[0])
                parseTable[key][prod[0]] = prod
            elif prod[0] in Terminals and prod[0] != '_eps':
                # print(' Here with ' + prod[0])
                parseTable[key][prod[0]] = prod
            else:
                for it in prod:
                    # print(it + ' from 26')
                    resultset.extend(Firsts[it])
                    if '_eps' not in Firsts[it]:
                        isepsilon = 0
                        break
                # print('after')
                for term in resultset:
                    if term != '_eps':
                        parseTable[key][term] = prod
                if isepsilon == 1:
                    # print('fine')
                    for term in Follows[key]:
                        parseTable[key][term] = prod
    print('Final generated ParseTable is:- ')
    printTable(parseTable, Terminals)
    return parseTable
