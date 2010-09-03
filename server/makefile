#makefile for server

all:client serv01

client:client.c ../lib/tcp_connect.c
	gcc -o client client.c ../lib/tcp_connect.c -Wall -g
serv01:serv01.c ../lib/tcp_connect.c pr_cpu_time.c
	gcc -o serv01 serv01.c ../lib/tcp_connect.c pr_cpu_time.c -Wall -g
