backupcontact : mytinyxmlparse.o contacts.o
	@g++  mytinyxmlparse.o contacts.o sql_con.cpp -Isrc -Lsrc -ltinyxml -o backupcontact -lsqlite3 -lfcgi

#test : mytinyxmlparse.o contacts.o
#	@g++  mytinyxmlparse.o contacts.o test.cpp -Isrc -Lsrc -ltinyxml -o test

contacts.o : contacts.cpp
	g++ -c contacts.cpp

mytinyxmlparse.o : mytinyxmlparse.cpp
	g++ -c -Isrc mytinyxmlparse.cpp


.PHONY:clean
clean:
	@rm *.o 