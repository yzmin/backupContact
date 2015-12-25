#include "mytinyxmlparse.h"

MyTinyXmlParse::MyTinyXmlParse()
{
	
}

MyTinyXmlParse::~MyTinyXmlParse()
{
		
}


bool MyTinyXmlParse::ReadXmlParser(string& szFileName)
{
	//读取Xml文件，并遍历
	try
	{
		vector<Contacts> contacts;

		//创建一个XML的文档对象。  
		TiXmlDocument *myDocument = new TiXmlDocument(szFileName.c_str());
		myDocument->LoadFile();

		//获得根元素，即Persons。  
		TiXmlElement *RootElement = myDocument->RootElement();


		//输出根元素名称，即输出Persons。  
		cout << RootElement->Value() << endl;
		TiXmlElement *FirstPerson = RootElement->FirstChildElement();

		for (TiXmlNode *contactNode = RootElement->FirstChild("Contact"); contactNode; contactNode = contactNode->NextSibling("Contact"))
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

			contacts.push_back(*contact);
		}	

		for (vector<Contacts>::iterator it = contacts.begin(); it != contacts.end(); it++)
		{
			cout << it->imei << endl;
			cout << it->name << endl;
			cout << it->phone << endl;
		}
	}
	catch (string& e)
	{
		return false;
	}
	return true;
}


bool MyTinyXmlParse::MakeXmlFile(string& szFileName)
{
	//创建xml文件，szFilePath为文件保存的路径，若创建成功返回true 否则false
	try
	{
		//创建一个XML的文档对象。  
		TiXmlDocument *myDocument = new TiXmlDocument();

		//创建一个根元素并连接。  
		TiXmlElement *RootElement = new TiXmlElement("Contacts");
		myDocument->LinkEndChild(RootElement);

		//创建一个Person元素并连接。  
		TiXmlElement *PersonElement = new TiXmlElement("Contact");
		RootElement->LinkEndChild(PersonElement);

		//设置Person元素的属性。  
		PersonElement->SetAttribute("ID", "1");

		//创建name元素、age元素并连接。  
		TiXmlElement *NameElement = new TiXmlElement("name");
		TiXmlElement *AgeElement = new TiXmlElement("phone");
		PersonElement->LinkEndChild(NameElement);
		PersonElement->LinkEndChild(AgeElement);

		//设置name元素和age元素的内容并连接。  
		TiXmlText *NameContent = new TiXmlText("周星星");
		TiXmlText *AgeContent = new TiXmlText("22");
		NameElement->LinkEndChild(NameContent);
		AgeElement->LinkEndChild(AgeContent);

		myDocument->SaveFile(szFileName.c_str());//保存到文件  
	}
	catch (string& e)
	{
		return false;
	}
	return true;
}