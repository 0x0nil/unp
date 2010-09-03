#makefile for server

all:client serv01

client:client.c ../lib/tcp_connect.c
	gcc -o client client.c ../lib/tcp_connect.c -Wall -g
serv01:serv01.c ../lib/tcp_connect.c
	gcc -o serv01 serv01.c ../lib/tcp_connect.c -Wall -g
