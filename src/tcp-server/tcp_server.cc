#include "tcp_server.h"

#include <sys/socket.h>     //是socket() bind() listen() accept()  connect()函数的头文件
#include <sys/types.h>      //是socket() bind() listen() accept()  connect()函数的头文件

#include <unistd.h>         //是close()函数的头文件
#include <stdio.h>          //fprintf()的头文件
#include <stdlib.h>         //exit()的头文件

#include <strings.h>        //bzero()的头文件
#include <arpa/inet.h>      //inet_aton()的头文件

#include <signal.h>         //与信号相关的处理函数
#include <error.h>          //处理系统调用和库调用错误相关的函数

/// @brief 1. 创建socket 2.初始化服务器的地址 3. 绑定端口 4.监听 5.进行相应的优化:忽略某些信号 6.设置重复监听
/// @param ip 
/// @param port 

Mars::Tcp_server::Tcp_server(const char* ip, uint16_t port) {
//5. 忽略一些信号：SIGPIPE
    if (signal(SIGHUP, SIG_IGN) == SIG_ERR) {     //出错处理
        fprintf(stderr,"signal iganore SIGHUP \n");
    }

    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {     //出错处理
        fprintf(stderr,"signal iganore SIGPIPE \n");
    }

//1. 创建监听套接字

    //监听套接字是属于服务器端的一个数据成员
    ///成功则为肺腑描述符；出错则为-1
    listen_sockfd_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listen_sockfd_ == -1) {
        fprintf(stderr, "tcp::server :socket()\n");
        exit(1);
    }


//2. 初始化服务器的协议地址

    // 协议地址是32位的IPv4地址与16位的TCP或者UDP端口号的组合
    struct sockaddr_in server_addr;
    /*
        void explicit_bzero(void *s, size_t n);
        The bzero() function erases the data in the n bytes of the memory starting at the location pointed to by s, by writing zeros (bytes containing '\0') to that
    area.
    */
    ///将内存空间清零
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;       //协议族：TCP/IP协议族
    inet_aton(ip, &server_addr.sin_addr);   //将点分十进制形式的ip转换为一个32为得网络字节序二进制。server_addr.sin_addr是32为
    server_addr.sin_port = htons(port);     //erver_addr.sin_por是16位。htons 将主机字节序转换为16位网络字节序

//7. 设置sock可以重复监听
    int op = 1;
    if (setsockopt(listen_sockfd_, SOL_SOCKET, SO_REUSEADDR, &op, sizeof(op)) < 0) {
        fprintf(stderr, "set socket reuse failed\n");
        exit(1);
    }

//3. 绑定端口bind
    //bind函数将一个本地协议地址赋予一个套接字
    if (bind(listen_sockfd_, (const struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        fprintf(stderr, "bind error\n");
        exit(1);
    }
//4. 监听listen
    //当socket()创建的套接字是主动套接字，他应该用与调用connect发起连接的，listen()将一个未连接的套接字转换为一个被动套接字，指示内核应该接受指向该套接字的链接请求。
    //listen的第二个参数规定了内核为相应套接字排队的最大连接个数(全连接队列和半连接队列之和小于该数)    
    if (listen(listen_sockfd_, 500)  == -1) {
        fprintf(stderr, "listen error\n");
        exit(1);
    }
}


Mars::Tcp_server::~Tcp_server() {
    
}

/// @brief 开始提供创建连接的服务： 1. accept

/// 服务器中listenfd不需要设置为非阻塞，accept成功返回的connecfd需要设置为非阻塞。数据的传输都是通过connectfd实现的
void Mars::Tcp_server::do_accept() {
    int connect_sockfd;

    while (true) {
    //1. 连接
        ///后两个为传出参数：客户端协议地址，协议地址长度
        connect_sockfd = accept(listen_sockfd_, (struct sockaddr*)&client_addr_, &client_addr_len_);
        if (connect_sockfd == -1) {
            if(errno == EINTR) {        //The system call was interrupted by a signal that was caught before a valid connection arrived; see signal(7).
                perror("accept error = EINTR\n");
                continue;
            }else if (errno == (EAGAIN || EWOULDBLOCK)) {
                perror("accept error = (EAGAIN || EWOULDBLOCK)\n");  ///The socket is marked nonblocking and no connections are present to be accepted.
                break;
            }else if (errno == EMFILE) {       ///The per-process limit on the number of open file descriptors has been reached.
                perror("accept error = EMFILE\n");
            }
            
        }else {  //accept成功
            //Todo 添加一些心跳机制
            //添加消息队列机制
            //写一个回显任务
            
        }
    }

}