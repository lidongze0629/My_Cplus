all: 0_1_back prim threeZS kruskal zyzz

clean:
	rm -f 0_1_back
	rm -f prim
	rm -f threeZS
	rm -f kruskal
	rm -f zyzz

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
