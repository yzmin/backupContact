#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "fcgi_stdio.h"
#include "mytinyxmlparse.h"

using namespace std;

extern "C"
{
#include "sqlite3.h"
}


//当接收到一个请求时，创建一个新数据库文件和创建表
int createsql3(sqlite3 **db,const char *namefile)
{
	if(!namefile)
		return -2;
		
	char *errmsg = NULL;
	int res;
	res = sqlite3_open(namefile, db);
	if (res != SQLITE_OK)
	{
		printf("error\n");
		return -1;
	}
	
	res = sqlite3_exec(*db, "create table  if not exists Contact(id INTEGER PRIMARY KEY  AUTOINCREMENT, name CHAR(15) NOT NULL, phoneNumber CHAR(50))", NULL, NULL, &errmsg);
	if (res != SQLITE_OK)
		printf("创建表失败，错误码:%d，错误原因:%s\n", res, errmsg);

	return 0;
}

int insertData(sqlite3 *db)
{
	char *errmsg = NULL;
	int res;
	char sql[1024] = {0};
	//插入时注意单引号
	sprintf(sql, "insert into Contact(name,phoneNumber) values ('%s','%s')","叶志敏","15889970648");

	res = sqlite3_exec(db,sql , NULL, NULL, &errmsg);
	if (res != SQLITE_OK)
		printf("插入失败，错误码:%d，错误原因：%s\n", res, errmsg);
}

int createSqlite3(sqlite3 **db)
{
	char *errmsg = NULL;
	int res;
	res = sqlite3_open("QQTable.db", db);
	if (res != SQLITE_OK)
	{
		printf("error\n");
		return -1;
	}
	
	res = sqlite3_exec(*db, "create table  if not exists QQTable(id INTEGER PRIMARY KEY  AUTOINCREMENT, qq CHAR(15) NOT NULL, passwd CHAR(50))", NULL, NULL, &errmsg);
	if (res != SQLITE_OK)
		printf("创建表失败，错误码:%d，错误原因:%s\n", res, errmsg);

	return 0;
}

int callback(void *para, int n_column, char **column_value, char **column_name)
{
	if(!n_column)
	{
		printf("查找结果：不存在！");
	}
	
	int i;
	for (i = 1; i < n_column; ++i)
	{
		printf("%s ：%s\n", column_name[i], column_value[i]);
	}

	return 0;
}

int selectData(sqlite3 *db,char *sql)
{
	char *errmsg;
	int res = sqlite3_exec(db, sql, callback, NULL, &errmsg);
	if (res != SQLITE_OK)
	{
		printf("查询失败，错误码：%d，错误原因：%s\n", res, errmsg);
		return -1;
	}
	return 0;
}


char* decode(char* URL)
{
    char* pDecode    =URL;
    char* pURL       =URL;

    while('\0'!=(*pDecode=*pURL))
    {
        ++pURL;
        if('%'==*pDecode)
        {
            *pDecode=(*pURL>='A'?(*pURL-'A'+10):(*pURL-'0'));
            ++pURL;
            *pDecode=(*pDecode<<=4)|(*pURL>='A'?(*pURL-'A'+10):(*pURL-'0'));
            ++pURL;
        }
        ++pDecode;
    }

    return URL;
}

int main(int argc,char **argv)
{
	
	while(FCGI_Accept() >= 0)
	{
		sqlite3 *db = NULL;
		printf("Content-type: text/html\r\n\r\n");
		
		int length = atoi(getenv("CONTENT_LENGTH"));
		char *buf = (char *)calloc(1,length);
		
		printf("length = %s\n",getenv("CONTENT_LENGTH"));

		fread(buf,1,length,stdin);
		//printf("%s\n",decode(buf));

		char *imei = strtok(buf,"&");
		char *xml = strtok(buf,"&");

		char *name1 = strtok(imei,"=");
		char *filename = strtok(NULL,"=");

		char *name2= strtok(xml,"=");
		char *content = strtok(NULL,"=");
		printf("content: %s\n",decode(content));
		
		MyTinyXmlParse myparse;
		string file = "info.xml";
		myparse.ReadXmlParser(file);
		
		createsql3(&db,filename);
		insertData(db);
		
		free(buf);
	}
	return 0;
}

