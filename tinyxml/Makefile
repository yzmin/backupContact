app:mytinyxmlparse.o contacts.o
	g++ mytinyxmlparse.o contacts.o test.cpp -Isrc -Lsrc -ltinyxml -o app 

contacts.o:contacts.cpp
	g++ -c contacts.cpp

mytinyxmlparse.o:mytinyxmlparse.cpp
	g++ -c -Isrc mytinyxmlparse.cpp

.PHONY:clean
clean:
	rm contacts.o mytinyxmlparse.o 
