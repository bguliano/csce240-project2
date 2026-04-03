compiler = g++
flags = -Wall -std=c++17
compile = $(compiler) $(flags) -c
link = $(compiler) $(flags)


project2test : project2sampletests.cc dynamicarray.h
	$(link) project2sampletests.cc -o project2test

clean :
	rm -f project2test *.o 
