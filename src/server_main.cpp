//
// Created by eric on 19-1-6.
//
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/epoll.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string>

#include "PF_Test/pftest.h"
#include "RM_Test/rmtest.h"
#include "IX_Test/ixtest.h"
#include "SM/SM_PUBLIC.h"
#include "Parser/astree.h"
#include "QL/QL_PUBLIC.h"

using namespace std;

const int ListenPort = 9999;
const int MaxLine = 10000;
const int MAX_EVENTS = 10;

//int inputfd;
FILE *inputFile;

extern Printer *stdoutPrinter;
//Printer *printer = new StdoutPrinter;
//Printer *printer = stdoutPrinter;
FileManager* fmm = new FileManager();
BufPageManager* bpmm = new BufPageManager(fmm);
RM_Manager rmManager(fmm, bpmm);
IX_Manager ixManager(*fmm, *bpmm);
SM_Manager smManager(ixManager, rmManager, stdoutPrinter); // add printer
QL_Manager qlManager(smManager, ixManager, rmManager, stdoutPrinter);// add printer

extern int parserError;
string process(char *cmd)
{
    int rc;
    string input = string(cmd) + string("\nexit;\n");

    inputFile=fopen("server.in", "w");
    fprintf(inputFile, input.data());
    fflush(inputFile);
    fclose(inputFile);

    freopen("server.in", "r", stdin);
    bool hasError = false;
    for(;;)
    {
        rc = treeparser(smManager, qlManager, 0);
        if(rc == PARSEREXIT) break;
        if (parserError || hasError)
        {
            hasError = true;
            continue;
        }
        if (rc > 0)
        {
            qlManager.getPrinter()->getSS() << errorGet(rc) << '\n';
        } else
            qlManager.getPrinter()->getSS() << "OK." << '\n';

        if(rc == 0) printf("NORMAL.\n");
    }
    if (hasError)
        qlManager.getPrinter()->getSS() << "Syntax error." << '\n';
    string ret = qlManager.getPrinter()->getSS().str();
    qlManager.getPrinter()->flush();
//    printer->getSS().flush();
//    ret += '\n';
    return ret;
}

int epollLoop()
{
//    int  listenfd, connfd;
//    struct sockaddr_in  servaddr;
//    char  buff[4096];
//    int  n;
//
//    if( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){
//        printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);
//        return 0;
//    }
//
//    memset(&servaddr, 0, sizeof(servaddr));
//    servaddr.sin_family = AF_INET;
//    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
//    servaddr.sin_port = htons(ListenPort);
//
//    if (bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) == -1)
//    {
//        printf("bind socket error: %s(errno: %d)\n", strerror(errno), errno);
//        return 0;
//    }
//
//    if (listen(listenfd, 10) == -1)
//    {
//        printf("listen socket error: %s(errno: %d)\n", strerror(errno), errno);
//        return 0;
//    }
//
//    printf("======waiting for client's request======\n");
//    while(1){
//        if( (connfd = accept(listenfd, (struct sockaddr*)NULL, NULL)) == -1){
//            printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
//            continue;
//        }
//        n = recv(connfd, buff, MaxLine, 0);
//        buff[n] = '\0';
//        printf("recv msg from client: %s\n", buff);
//        close(connfd);
//    }
//    close(listenfd);
    int server_sockfd;
    int client_sockfd;
    int len;
    struct sockaddr_in my_addr;
    struct sockaddr_in remote_addr;
    int sin_size;
    char buf[MaxLine];
    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = INADDR_ANY;
    my_addr.sin_port = htons(ListenPort);
    if((server_sockfd=socket(PF_INET,SOCK_STREAM,0))<0)
    {
        perror("socket");
        return 1;
    }

    int opt = 1;
    if(setsockopt(server_sockfd, SOL_SOCKET,SO_REUSEADDR, (const void *) &opt, sizeof(opt))){
        perror("setsockopt reuse port");
        return -1;
    }

    if (bind(server_sockfd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr))<0)
    {
        perror("bind");
        return 1;
    }
    // 监听连接请求--监听队列长度为5
    listen(server_sockfd,5);
    sin_size=sizeof(struct sockaddr_in);
    int epoll_fd;
    epoll_fd=epoll_create(MAX_EVENTS);
    if(epoll_fd==-1)
    {
        perror("epoll_create failed");
        exit(EXIT_FAILURE);
    }
    struct epoll_event ev;
    struct epoll_event events[MAX_EVENTS];
    ev.events=EPOLLIN;
    ev.data.fd=server_sockfd;
    // 向epoll注册server_sockfd监听事件
    if(epoll_ctl(epoll_fd,EPOLL_CTL_ADD,server_sockfd,&ev)==-1)
    {
        perror("epll_ctl:server_sockfd register failed");
        exit(EXIT_FAILURE);
    }
    int nfds;// epoll监听事件发生的个数
    while(1)
    {
        nfds=epoll_wait(epoll_fd,events,MAX_EVENTS,-1);
        if(nfds==-1)
        {
            perror("start epoll_wait failed");
            exit(EXIT_FAILURE);
        }
        int i;
        for (i = 0; i < nfds; i++)
        {
            if (events[i].data.fd == server_sockfd)
            {
                if ((client_sockfd = accept(server_sockfd,
                                            (struct sockaddr *) &remote_addr,
                                            (socklen_t *) &sin_size)) < 0)
                {
                    perror("accept client_sockfd failed");
                    exit(EXIT_FAILURE);
                }
                ev.events = EPOLLIN;
                ev.data.fd = client_sockfd;
                if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_sockfd, &ev) == -1)
                {
                    perror("epoll_ctl:client_sockfd register failed");
                    exit(EXIT_FAILURE);
                }
                fprintf(stderr, "accept client %s\n", inet_ntoa(remote_addr.sin_addr));
                int len = 0;
                len = send(client_sockfd, smManager.getCurrentDbName().data(),
                           min((int) smManager.getCurrentDbName().length() + 1, 10000), 0);
                printf("Send %d bytes.\n", len);
            }
            else if (events[i].events == EPOLLIN)
            {
                client_sockfd = events[i].data.fd;
                len = recv(client_sockfd, buf, MaxLine, 0);
                if (len < 0)
                {
                    perror("receive from client failed");
                    exit(EXIT_FAILURE);
                }
                if (len == 0)
                {
                    fprintf(stderr, "Null string from client(Pipe broke)\n");
                }
                fprintf(stderr, "receive from client:%s\n", buf);
                string data = process(buf);
                cerr << data;
                send(client_sockfd, data.data(), min((int) data.length(), 10000), 0);
                memset(buf, 0, sizeof(buf));
            }
        }
    }
    return 0;
}

int main()
{
    epollLoop();
    return 0;
}