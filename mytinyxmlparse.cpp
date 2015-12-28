#include "mytinyxmlparse.h"

vector<Contacts*> *contacts;
char sqlselect[] = "select * from Contact";

MyTinyXmlParse::MyTinyXmlParse()
{
	
}

MyTinyXmlParse::MyTinyXmlParse(sqlite3 *db)
{
		this->db = db;
}

MyTinyXmlParse::~MyTinyXmlParse()
{
		
}

int MyTinyXmlParse::insertData(Contacts *contact)
{
        char *errmsg = NULL;
        int res;
        char sql[1024] = {0};


#if 1
        sprintf(sql, "insert into Contact(name,phoneNumber) values ('%s','%s')",(contact->name).c_str(),(contact->phone).c_str());

        res = sqlite3_exec(this->db,sql , NULL, NULL, &errmsg);
        if (res != SQLITE_OK)
        {
                printf("错误码：%d  错误信息：%s\n", res, errmsg);
                return -1;
        }
#endif
       return 0;
}




bool MyTinyXmlParse::readXmlParser(string& szFileName)
{
	//printf("MyTinyXmlParse::filename : %s\n",szFileName.c_str());
	//读取Xml文件，并遍历
	try
	{
		vector<Contacts*> contacts;

		//创建一个XML的文档对象。  
		TiXmlDocument *myDocument = new TiXmlDocument(szFileName.c_str());
		myDocument->LoadFile();

		//获得根元素，即Persons。  
		TiXmlElement *RootElement = myDocument->RootElement();


		//输出根元素名称，即输出Persons。
		//printf("%s\n",RootElement->Value());

		TiXmlElement *FirstPerson = RootElement->FirstChildElement();

		for (TiXmlNode *contactNode = RootElement->FirstChild("contact"); contactNode; contactNode = contactNode->NextSibling("contact"))
		{
			Contacts *contact = new Contacts;
			TiXmlAttribute* attributeOfImei = FirstPerson->FirstAttribute();  //获得student的name属性
			while (attributeOfImei) {
				contact->imei = attributeOfImei->Value();
				//cout << attributeOfImei->Name() << " : " << attributeOfImei->Value() << endl;
				attributeOfImei = attributeOfImei->Next();
				FirstPerson = FirstPerson->NextSiblingElement();
			}

			TiXmlNode *child = contactNode->FirstChild();
			//cout << child->ToElement()->GetText() << endl;
			contact->name = child->ToElement()->GetText();

			child = contactNode->IterateChildren(child);
			//cout << child->ToElement()->GetText() << endl;
			contact->phone = child->ToElement()->GetText();

			contacts.push_back(contact);
		}	

		for (vector<Contacts *>::iterator it = contacts.begin(); it != contacts.end(); it++)
		{
			Contacts *contact = *it;
			//printf("name = %s ,phone = %s\n",(contact->name).c_str(),(contact->phone).c_str());
			this->insertData(contact);
		}
	}
	catch (string& e)
	{
		return false;
	}
	return true;
}



int callback(void *para, int n_column, char **column_value, char **column_name)
{
	
#if 1
	Contacts *contact = new Contacts;
	contact->id = column_value[0];
	contact->name = column_value[1];
	contact->phone = column_value[2];
	contacts->push_back(contact);
#else
	int i;//3
	for (i = 1; i < n_column; ++i)
	{
		printf("%s ：%s\n", column_name[i], column_value[i]);
	}
#endif

	return 0;
}

int selectData(sqlite3 *db,char *sql)
{
	contacts = new vector<Contacts*>;
	
	char *errmsg;
	int res = sqlite3_exec(db, sql, callback, NULL, &errmsg);
	if (res != SQLITE_OK)
	{
		printf("查询失败，错误码：%d，错误原因：%s\n", res, errmsg);
		return -1;
	}
	return 0;
}


bool MyTinyXmlParse::makeXmlFile(string& szFileName)
{
	//查询数据库
	selectData(this->db,sqlselect);
	//创建xml文件，szFilePath为文件保存的路径，若创建成功返回true 否则false
	try
	{
		//创建一个XML的文档对象。  
		TiXmlDocument *myDocument = new TiXmlDocument();
		//描述
		TiXmlDeclaration *decl = new TiXmlDeclaration("1.0", "utf-8", "");  
		myDocument->LinkEndChild(decl);

		//创建一个根元素并连接。  
		TiXmlElement *RootElement = new TiXmlElement("Contacts");
		myDocument->LinkEndChild(RootElement);

		
		
		for (vector<Contacts *>::iterator it = contacts->begin(); it != contacts->end(); it++)
		{
			Contacts *contact = *it;
			
			//创建一个Contact元素并连接。
			TiXmlElement *PersonElement = new TiXmlElement("Contact");
			RootElement->LinkEndChild(PersonElement);

			//设置Contact元素的属性。  
			PersonElement->SetAttribute("ID", (contact->id).c_str());

			//创建name元素、age元素并连接。  
			TiXmlElement *NameElement = new TiXmlElement("name");
			TiXmlElement *AgeElement = new TiXmlElement("phone");
			PersonElement->LinkEndChild(NameElement);
			PersonElement->LinkEndChild(AgeElement);

			//设置name元素和age元素的内容并连接。  
			TiXmlText *NameContent = new TiXmlText((contact->name).c_str());
			TiXmlText *AgeContent = new TiXmlText((contact->phone).c_str());
			NameElement->LinkEndChild(NameContent);
			AgeElement->LinkEndChild(AgeContent);
		}

		myDocument->SaveFile(szFileName.c_str());//保存到文件
		
	}
	catch (string& e)
	{
		return false;
	}
	
	delete contacts;
	return true;
}
