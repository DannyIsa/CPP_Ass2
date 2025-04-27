Main: main.o square_mat.o
	g++ -Wall -std=c++11 -o Main main.o square_mat.o

main.o: main.cpp square_mat.h
	g++ -Wall -std=c++11 -c main.cpp

square_mat.o: square_mat.cpp square_mat.h
	g++ -Wall -std=c++11 -c square_mat.cpp

clean:
	rm -f *.o Main

run: Main
	./Main