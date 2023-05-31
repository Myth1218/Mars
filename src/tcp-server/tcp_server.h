#pragma once
#include <string>
#include <iostream>

#include <netinet/in.h>

/* tcp服务器对外封装的接口。当我创建并初始化一个服务器对象后，相当于运行了一个服务器了，不需要关注服务器具体的细节

int main () {
    tcp_server server("127.0.0.1",7777);
    server.do_accept();
}

*/

namespace Mars {

class Tcp_server {
    public:
        //构造函数
        Tcp_server(const char* ip, uint16_t port); //short就是16位

        //析构函数，释放资源
        ~Tcp_server();

        //服务器的链接客户端服务
        void do_accept();

    private:
        int listen_sockfd_;                 //监听套接字：监听套接字是属于服务器端的一个数据成员,是属于的服务器的。一个 b监听套接字，他在该服务器的生命期内一直存在。
        struct sockaddr_in client_addr_;    //已连接的对端进程（客户端）的协议地址
        socklen_t client_addr_len_;         //内核存放在在套接字地址结构类的确切字节数

    };

}


