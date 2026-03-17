CXXFLAGS += -std=c++14 -Wall -Wextra -Weffc++ 

top-vect: main.cpp
	g++ -o $@ $^

clean:
	rm -rf *.o top-vect
