#include <iostream>
#include <SFML/Network.hpp>

#include "../data/ClassCard.hpp"
#include "../data/netWorkUtils.hpp"

#define CL "CLIENT: "
#define MAX_BUFF 1024
#define DEFAULT_PORT 8081

using namespace std;
int main(int argc, char* argv[]) {
    sf::TcpSocket client_socket;
    cout << CL << "Сокет создан!" << endl;
    sf::Time timeout = sf::seconds(1.f);
    sf::Socket::Status status = client_socket.connect("127.0.0.1", DEFAULT_PORT, timeout);
    if (status != sf::Socket::Done) {
        cout << CL << "Произошла ошибка соединения с сервером" << endl;
    } else {
        cout << CL << "Подключился к серверу " << client_socket.getRemoteAddress()
                << " На порту " << client_socket.getRemotePort() << endl;
    }
    Card a(111);
    sf::Packet packet;
    if (client_socket.receive(packet) != sf::Socket::Done) {
        return 1;
    }
    cout << "Словил пакет!" << endl;
    packet >> a;
    a.GetParameters();



    return 0;
}