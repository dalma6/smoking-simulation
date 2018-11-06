CFLAGS = -Wall -Wextra -std=c++11 -lglut -lGLU -lGL

smoking: main.o cigarette.o additional_obj.o animation.o
	g++ $^ $(CFLAGS) -o $@
	
main.o: main.cpp animation.hpp
	g++ -c $< $(CFLAGS)
	
cigarette.o: cigarette.cpp cigarette.hpp
	g++ -c $< $(CFLAGS)
	
additional_obj.o: additional_obj.cpp additional_obj.hpp
	g++ -c $< $(CFLAGS)
	
animation.o: animation.cpp animation.hpp additional_obj.hpp cigarette.hpp
	g++ -c $< $(CFLAGS)	
	
.PHONY: clean

clean: 
	rm *.o smoking