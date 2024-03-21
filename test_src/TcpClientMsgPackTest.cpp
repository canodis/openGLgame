#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <unistd.h>
#include <msgpack.hpp>

class DefaultPackage {
public:
    DefaultPackage() {};
    DefaultPackage(int id) : id(id) {}
    int id;
    MSGPACK_DEFINE(id);
};


class Data : public DefaultPackage
{
public:
    Data() : DefaultPackage(0) {}
    Data(int id, int data, std::string message) : DefaultPackage(id), data(data), message(message) {}
    int data;
    std::string message;
    MSGPACK_DEFINE(data, message, MSGPACK_BASE(DefaultPackage));
};

void send_data(const std::string &server_ip, int port, const Data &data)
{
    int sock = 0;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cout << "\n Socket creation error \n";
        return;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, server_ip.c_str(), &serv_addr.sin_addr) <= 0)
    {
        std::cout << "\nInvalid address/ Address not supported \n";
        return;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cout << "\nConnection Failed \n";
        return;
    }

    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, data);

    send(sock, sbuf.data(), sbuf.size(), 0);
    std::cout << "Mesaj gönderildi" << std::endl;

    close(sock);
}

int main()
{
    Data data(1, 2, "test message");

    send_data("37.247.108.252", 8080, data);
}
