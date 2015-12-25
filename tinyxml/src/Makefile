LIBRARY_SO=libtinyxml.so


$(LIBRARY_SO):tinyxmlerror.o tinyxml.o tinyxmlparser.o tinystr.o
	g++ -shared -W -o libtinyxml.so tinyxmlerror.o tinyxml.o tinyxmlparser.o tinystr.o

%.o:%.cpp
	g++ -c -fPIC $<

.PHONY:clean
clean:
	rm -rf $(LIBRARY_STATIC)
	rm -rf *.o
