file = open('output.txt', 'r')

print("digraph visualiseAST {") 
print("\tcolor=white;")
print("\tfontcolor=white;")
print("\tbgcolor=black;")
    
title = file.readline()
print(f"\tlabel=\" {title[:-1]}\";")

root = file.readline()

l,rootNode = root.split(':- ')

edges = []

line = file.readline() 
while line:
    lhs, rhs = line.strip('\n').split(' :- ')
    nodenumber = rhs
    line = file.readline()
    lhs, rhs = line.strip('\n').split(':-')
    value = rhs
    line = file.readline()
    lhs, rhs = line.strip('\n').split(' :- ') 
    left, right = rhs.split(' ',1) 
    print(f"\tnode [color=white fontcolor=white  label=\"{value}\"]; addr_{nodenumber}")
    if int(left) >= 0 and int(right) >= 0:
        edges.append(f"\taddr_{nodenumber} -> addr_{left} [color=white fontcolor=white ];")
        edges.append(f"\taddr_{nodenumber} -> addr_{right} [color=white fontcolor=white ];")
    line = file.readline() 
    line = file.readline() 

for edge in edges:
    print(edge)
 
print("}")

file.close()
