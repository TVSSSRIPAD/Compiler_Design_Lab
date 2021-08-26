g++ renfa.cpp
./a.out "$1" > output.txt
python3 convertToDot.py > graph.dot
dot -Tpng graph.dot > graph.png
xdg-open graph.png