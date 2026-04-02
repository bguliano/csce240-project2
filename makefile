compiler = g++
flags = -Wall -std=c++17
compile = $(compiler) $(flags) -c
link = $(compiler) $(flags)

project2sampletests : project2sampletests.o dynamicarray.o
	$(link) $^ -o $@
	./$@

project2sampletests.o : project2sampletests.cc dynamicarray.h
	$(compile) $<

dynamicarray.o : dynamicarray.cc dynamicarray.h
	$(compile) $<

clean :
	rm *.o project2sampletests
