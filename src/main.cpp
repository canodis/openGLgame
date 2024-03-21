#include "Navigator.hpp"
#include "MainStage.hpp"

void Test();

int main(int ac, char **av)
{
    Navigator &navigator = Navigator::getInstance();
    Stage *mainScene = new MainStage();

    navigator.setActiveStage(mainScene);
    while (navigator.isRunning)
    {
        navigator.runActiveStage();
    }

    // TEST //
    //  Test();
}

#include "PlayerPositionPackage.hpp"

class Data
{
public:
    std::string message;
    MSGPACK_DEFINE(message);
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

void Test()
{
    Data data;
    data.message = "Hello, this is an test message.";

    send_data("37.247.108.252", 8080, data);
}
