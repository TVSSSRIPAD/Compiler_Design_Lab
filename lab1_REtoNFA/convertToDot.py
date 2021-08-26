file = open('output.txt', 'r')

print("digraph finite_state_machine {")
print("\trankdir=LR;")
print("\tcolor=white;")
print("\tfontcolor=white;")
print("\tbgcolor=black;")

line = file.readline()
startstate = file.readline()
end = file.readline()
endstates = end.split()
print(f"\tlabel=\"Regex : {line[:-1]}\";")
for x in endstates:
    print(
        f"\tnode [color=white fontcolor=white shape = doublecircle label=\"\"]; addr_{x}")
print("\tnode [color=white fontcolor=white shape = circle]")
line = file.readline()
while line:
    lhs, rhs = line[:-2].split(' : ')
    lhs = lhs.split(' ')
    rhs = rhs.split(' ')
    line = file.readline()
    for value in rhs:
        print(
            f"\taddr_{lhs[0]} -> addr_{value} [color=white fontcolor=white  label = \"{lhs[1]}\" ];")

print("\tnode [color=white fontcolor=white shape = none label=\"\"]; start")
print(
    f"\tstart -> addr_{startstate[:-1]} [color=white fontcolor=white label = \"start\" ]")
print("}")

file.close()
