backupcontact : mytinyxmlparse.o contacts.o contact_con.cpp
	@g++  mytinyxmlparse.o contacts.o contact_con.cpp -Isrc -Lsrc -ltinyxml -o backupcontact -lsqlite3 -lfcgi 

#test : mytinyxmlparse.o contacts.o test.cpp
#	@g++  mytinyxmlparse.o contacts.o test.cpp -Isrc -Lsrc -ltinyxml -o test

contacts.o : contacts.cpp
	g++ -c contacts.cpp

mytinyxmlparse.o : mytinyxmlparse.cpp
	g++ -c -Isrc -lfcgi -lsqlite3 mytinyxmlparse.cpp


.PHONY:clean
clean:
	@rm *.o 
