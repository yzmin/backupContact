#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "fcgi_stdio.h"
#include "mytinyxmlparse.h"

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

extern "C"
{
#include "sqlite3.h"
}


int opensql3(sqlite3 **db,const char *namefile)
{
	if(!namefile)
		return -2;
		
	int res;
	res = sqlite3_open(namefile, db);
	if (res != SQLITE_OK)
	{
		printf("error\n");
		return -1;
	}
	return 0;
}


//当接收到一个请求时，创建一个新数据库文件和创建表
int createsql3(sqlite3 **db,const char *namefile)
{
	opensql3(db,namefile);
	
	int res;
	char *errmsg = NULL;
	res = sqlite3_exec(*db, "create table  if not exists Contact(id INTEGER PRIMARY KEY  AUTOINCREMENT, name CHAR(32) NOT NULL, phoneNumber CHAR(50))", NULL, NULL, &errmsg);
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

void eatspace(char *str)
{
	char *p = str;
	while(*p)
	{
		if(*p == '+')
			*p = ' ';
		p++;
	}
}

int main(int argc,char **argv)
{
	
	while(FCGI_Accept() >= 0)
	{
		sqlite3 *db = NULL;
		printf("Content-type: text/html\r\n\r\n");
		
		int length = atoi(getenv("CONTENT_LENGTH"));
		char *buf = (char *)calloc(1,length);
		
		//printf("contact-length = %s\n",getenv("CONTENT_LENGTH"));


		fread(buf,1,length,stdin);
		//printf("buf : %s\n",decode(buf));

		char *imei = strtok(buf,"&");
		char *xml = strtok(NULL,"&");

		//imei
		char *name1 = strtok(imei,"=");
		char *filename = strtok(NULL,"=");
		//printf("filename: %s\n",decode(filename));

		//XML
		char *name2= strtok(xml,"=");
		char *content = strtok(NULL,"=");
		
		//数据库文件路径
		char dbfilename[1024] = {0};
		sprintf(dbfilename,"./ContactDB/%s",filename);
		
		//下载
		if(0 == strcmp(content,"download"))
		{
			printf("download\n");
			opensql3(&db,dbfilename);
			
			MyTinyXmlParse myparse(db);
			string namefile = "tempxml.xml";
			myparse.makeXmlFile(namefile);
			
			//打开临时文件
			int fd = open("tempxml.xml",O_RDWR);
			struct stat buf;
			stat("tempxml.xml",&buf);
			printf("%s : %d\n","tempxml.xml",(int)buf.st_size);
			int len = (int)buf.st_size;
			char *filesize = new char[len];
			read(fd,filesize,len);
			printf("%s\n",filesize);
			close(fd); 
			unlink("tempxml.xml");
			
		}
		else //上传
		{
			eatspace(decode(content));
			//printf("content: %s\n",content);
			
			//临时文件
			char name[1024] = {0};
			sprintf(name, "%s.xml",filename);
		
			int fd = open(name,O_CREAT|O_RDWR|O_TRUNC,0664);
			int lencon = strlen(content);
			write(fd,content,lencon);
			lseek(fd,0,SEEK_SET);
		
			
			createsql3(&db,dbfilename);
		
			MyTinyXmlParse myparse(db);
			string file = name;
			int res = myparse.readXmlParser(file);
			if(res != 1)
			{
				printf("同步失败!\n");
			}
			else
			{
				printf("同步成功\n");		
			}		

			close(fd);
			unlink(name);
		}
		
		free(buf);
	}
	return 0;
}

