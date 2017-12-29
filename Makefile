all: 0_1_back prim threeZS kruskal zyzz n_queens traceable

clean:
	rm -f 0_1_back
	rm -f prim
	rm -f threeZS
	rm -f kruskal
	rm -f zyzz
	rm -f n_queens
	rm -f traceable

0_1_back: 0_1_back.cpp
	g++ -Wall 0_1_back.cpp -o 0_1_back
prim: prim.cpp
	g++ -Wall prim.cpp -o prim -std=c++11
threeZS: threeZS.cpp
	g++ -Wall threeZS.cpp -o threeZS
kruskal: kruskal.cpp
	g++ -Wall kruskal.cpp -o kruskal -std=c++11
zyzz: zyzz.cpp
	g++ -Wall zyzz.cpp -o zyzz
n_queens: n_queens.cpp
	g++ -Wall n_queens.cpp -o n_queens
traceable: traceable.cpp
	g++ -Wall traceable.cpp -o traceable -std=c++11
