
#ifndef __TINYXMLPARSER__H__
#define __TINYXMLRARSER__H__

#include "tinystr.h"
#include "tinyxml.h"
#include "contacts.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

extern "C"
{
#include "fcgi_stdio.h"
#include "sqlite3.h"
}

using namespace std;



class MyTinyXmlParse
{
	public:
			MyTinyXmlParse();
			MyTinyXmlParse(sqlite3 *db);
			~MyTinyXmlParse();
	public:
		bool readXmlParser(string& szFileName);
		bool makeXmlFile(string& szFileName);
		int insertData(Contacts *contact);
	public:		
		sqlite3 *db;
		
};


#endif
