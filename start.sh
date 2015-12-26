#! /bin/sh

make 

spawn-fcgi -a 127.0.0.1 -p 8030 -f /usr/local/nginx/fastcgi_temp/backupContact/backupcontact

netstat -na | grep 8030
