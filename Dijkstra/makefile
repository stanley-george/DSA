useDijkstra.exe: useDijkstra.o Heap.o Hash.o Graph.o
	g++ -o useDijkstra.exe useDijkstra.o Heap.o Hash.o Graph.o

useDijkstra.o: useDijkstra.cpp
	g++ -c useDijkstra.cpp

Heap.o: Heap.cpp Heap.h
	g++ -c Heap.cpp

Hash.o: Hash.cpp Hash.h
	g++ -c Hash.cpp

Graph.o: Graph.cpp Graph.h
	g++ -c Graph.cpp

debug:
	g++ -g -o useDijkstraDebug.exe useDijkstra.cpp Heap.cpp Hash.cpp Graph.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups
