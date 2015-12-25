#include "mytinyxmlparse.h"

MyTinyXmlParse::MyTinyXmlParse()
{
	
}

MyTinyXmlParse::~MyTinyXmlParse()
{
		
}


bool MyTinyXmlParse::ReadXmlParser(string& szFileName)
{
	//��ȡXml�ļ���������
	try
	{
		vector<Contacts> contacts;

		//����һ��XML���ĵ�����  
		TiXmlDocument *myDocument = new TiXmlDocument(szFileName.c_str());
		myDocument->LoadFile();

		//��ø�Ԫ�أ���Persons��  
		TiXmlElement *RootElement = myDocument->RootElement();


		//�����Ԫ�����ƣ������Persons��  
		cout << RootElement->Value() << endl;
		TiXmlElement *FirstPerson = RootElement->FirstChildElement();

		for (TiXmlNode *contactNode = RootElement->FirstChild("Contact"); contactNode; contactNode = contactNode->NextSibling("Contact"))
		{
			Contacts *contact = new Contacts;
			TiXmlAttribute* attributeOfImei = FirstPerson->FirstAttribute();  //���student��name����
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
	//����xml�ļ���szFilePathΪ�ļ������·�����������ɹ�����true ����false
	try
	{
		//����һ��XML���ĵ�����  
		TiXmlDocument *myDocument = new TiXmlDocument();

		//����һ����Ԫ�ز����ӡ�  
		TiXmlElement *RootElement = new TiXmlElement("Contacts");
		myDocument->LinkEndChild(RootElement);

		//����һ��PersonԪ�ز����ӡ�  
		TiXmlElement *PersonElement = new TiXmlElement("Contact");
		RootElement->LinkEndChild(PersonElement);

		//����PersonԪ�ص����ԡ�  
		PersonElement->SetAttribute("ID", "1");

		//����nameԪ�ء�ageԪ�ز����ӡ�  
		TiXmlElement *NameElement = new TiXmlElement("name");
		TiXmlElement *AgeElement = new TiXmlElement("phone");
		PersonElement->LinkEndChild(NameElement);
		PersonElement->LinkEndChild(AgeElement);

		//����nameԪ�غ�ageԪ�ص����ݲ����ӡ�  
		TiXmlText *NameContent = new TiXmlText("������");
		TiXmlText *AgeContent = new TiXmlText("22");
		NameElement->LinkEndChild(NameContent);
		AgeElement->LinkEndChild(AgeContent);

		myDocument->SaveFile(szFileName.c_str());//���浽�ļ�  
	}
	catch (string& e)
	{
		return false;
	}
	return true;
}