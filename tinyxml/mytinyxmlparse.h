#ifndef __TINYXMLPARSER__H__
#define __TINYXMLRARSER__H__

#include "tinystr.h"
#include "tinyxml.h"
#include "contacts.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class MyTinyXmlParse
{
	public:
			MyTinyXmlParse();
			~MyTinyXmlParse();
	public:
		bool ReadXmlParser(string& szFileName);
		bool MakeXmlFile(string& szFileName);
		
};


#endif
