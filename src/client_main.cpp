//
// Created by eric on 19-1-6.
//

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <cstdio>
#include <iostream>
using namespace std;

#define BUFFER_SIZE 4000
const int ListenPort = 9999;

int main(int argc, char *argv[])
{
    int client_sockfd;
    int len;
    struct sockaddr_in remote_addr; // 服务器端网络地址结构体
    char buf[BUFFER_SIZE];  // 数据传送的缓冲区
    memset(&remote_addr,0,sizeof(remote_addr)); // 数据初始化--清零
    string ipAddr;
    int port;
    printf("====================================\n");
    printf("              YourSQL               \n");
    printf("====================================\n");
    printf("Default connection(localhost:9999)(Y/N):");
    cin.getline(buf, 100);
    if (buf[0]=='N')
    {
        printf("Server IP address(default localhost):");
        cin >> ipAddr;
        if (ipAddr=="")
            ipAddr = string("127.0.0.1");
        printf("Server IP port:");
        cin>>port;
    } else{
        ipAddr="127.0.0.1";
        port = 9999;
    }
    remote_addr.sin_family=AF_INET; // 设置为IP通信
//    remote_addr.sin_addr.s_addr=inet_addr("127.0.0.1");// 服务器IP地址
//    remote_addr.sin_port=htons(ListenPort); // 服务器端口号
    remote_addr.sin_addr.s_addr = inet_addr(ipAddr.data());// 服务器IP地址
    remote_addr.sin_port=htons(port); // 服务器端口号
    // 创建客户端套接字--IPv4协议，面向连接通信，TCP协议
    if ((client_sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("client socket creation failed");
        exit(EXIT_FAILURE);
    }
    // 将套接字绑定到服务器的网络地址上
    if(connect(client_sockfd,(struct sockaddr *)&remote_addr,sizeof(struct sockaddr))<0)
    {
        perror("connect to server failed");
        exit(EXIT_FAILURE);
    }
    // 循环监听服务器请求
    while(1)
    {
        printf("> ");
//        scanf("%s",buf);
        cin.getline(buf,400);
        // exit
        if(strcmp(buf,"exit")==0)
        {
            break;
        }
        send(client_sockfd,buf,BUFFER_SIZE,0);
        // 接收服务器端信息
        memset(buf, 0, sizeof(buf));
        len=recv(client_sockfd,buf,BUFFER_SIZE,0);
//        buf[len]=0;
        printf("< %s\n",buf);
        if(len<0)
        {
            perror("receive from server failed");
            exit(EXIT_FAILURE);
        }
    }
    close(client_sockfd);// 关闭套接字
    return 0;
}