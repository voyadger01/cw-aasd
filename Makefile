CXXFLAGS += -std=c++14 -Wall -Wextra -Weffc++ -MMD

top-vect: main.o
	g++ -o $@ $^

-include main.d

clean:
	rm -rf *.d *.o top-vect
