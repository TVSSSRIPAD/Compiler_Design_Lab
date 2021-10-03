import firstsFollows as FF
import collections
import parseTable as TABLE


def parseTokens(parseTable, startSym, tokens, Terminals):

    tokens.append('$')
    parseStack = ['$', startSym]
    currentIndex = 0

    print('\n')
    print('Initial input is ', end='')
    print(tokens)
    print('Initial Stack is:- ', end='')
    print(parseStack)

    print('Parsing Starts..')
    # Parse until stack is empty
    while parseStack[-1] != '$':

        # current token
        currentToken = tokens[currentIndex]

        print('Current token is ' + currentToken)
        stackTop = parseStack.pop()

        if stackTop == currentToken:
            currentIndex += 1
            print('-----------Matched Token: ' + currentToken + ' ----------')
            print('Stack is:- ', end='')
            print(parseStack)
            print('Remaining input is ', end='')
            print(tokens[currentIndex:])
            print('----------------')
        elif stackTop in Terminals:
            print('PARSING ERROR!!!  Stack top = %s didn\'t match the current token %s' % (
                stackTop, currentToken))
            return False
        else:
            # get the table entry
            table_entry = parseTable[stackTop][currentToken]

            # Nothing in the table cell
            if table_entry == None:
                print('PARSING ERROR!!! Table Entry is None for stackTop: %s and currentToken: %s' % (
                    stackTop, currentToken))
                return False
            else:
                if table_entry == ['_eps']:
                    print('Push : ' + stackTop + '-> ', end='')
                    print(table_entry)
                    print('Stack is:- ', end='')
                    print(parseStack)
                    print('----------------')
                else:
                    eles = [x for x in table_entry]
                    eles.reverse()
                    parseStack += eles
                    print('Push : ' + stackTop + '-> ', end='')
                    print(table_entry)
                    print('Stack is:- ', end='')
                    print(parseStack)
                    print('----------------')

    if (currentIndex == len(tokens) - 1) and (parseStack[-1] == '$'):
        print('Stack is:- ', end='')
        print(parseStack)
        print('Input is ', end='')
        print(tokens[currentIndex:])
        print('----------------')
        print('Parsing Successful!')
        return True
    else:
        print('Stack is:- ', end='')
        print(parseStack)
        print('Input is ', end='')
        print(tokens[currentIndex:])
        print('----------------')
        print('PARSE ERROR!! ! Stack exhausted but inputs exist')
        return False


def main():
    q = int(input('Enter Question Number: '))
    grammar = []
    startSym = input('Enter the Start Symbol:- ')

    with open('grammar' + str(q) + '.txt') as f:
        grammar = f.readlines()

    # Get NTerminals and Terminals from the file
    NTerminals = grammar[0].rstrip('\n').split(',')
    Terminals = grammar[1].rstrip('\n').split(',')
    Prods = {}

    # Get the Productions from the file
    for x in grammar[2:]:
        l, r = x.split('->')
        lhs = l.replace(" ", "")
        # print(lhs)
        rhs = r.split('|')
        listofprods = []
        for prod in rhs:
            rr = prod.rstrip('\n').split(' ')
            r2 = [x.replace(" ", "") for x in rr if x != '']
            listofprods.append(r2)
        Prods[lhs] = listofprods

    print('Grammar is :-')
    print(Prods)

    if q == 1:
        firsts = collections.OrderedDict(FF.Firsts1)
        follows = collections.OrderedDict(FF.Follows1)
    else:
        firsts = collections.OrderedDict(FF.Firsts2)
        follows = collections.OrderedDict(FF.Follows2)

    parseTable = TABLE.run(Prods, Terminals, firsts, follows)

    # print(parseTable)
    with open('./token' + str(q) + '.txt') as f:
        tokens = f.readlines()
    tokens = [x.rstrip('\n') for x in tokens]

    if 'ERR' in tokens:
        print('ERROR DETECTED IN LEXICAL ANALYSIS!!')
        return

    if parseTokens(parseTable, startSym, tokens, Terminals):
        print('Successful')
    else:
        print('Error!')


main()
