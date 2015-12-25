#include "mytinyxmlparse.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc,char **argv)
{
	MyTinyXmlParse myparse;
	string file = "test.xml";
	myparse.ReadXmlParser(file);
	return 0;
}
