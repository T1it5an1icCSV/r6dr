#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <Windows.h>
#include <Winsock2.h>
#include <WS2tcpip.h>
#include <locale>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    WSADATA wsaDataInfo;
    ADDRINFO addrHints;
    ADDRINFO* addrResultPointer;
    const char* messageToSend = "Здравствуйте!";
    char receivedMessage[512];

    SOCKET connectionSocket = INVALID_SOCKET;

    int startupResult = WSAStartup(MAKEWORD(2, 2), &wsaDataInfo);
    if (startupResult != 0) {
        cout << "WSAStartup завершилась с ошибкой: " << endl;
        return 1;
    }

    ZeroMemory(&addrHints, sizeof(addrHints));
    addrHints.ai_family = AF_INET;
    addrHints.ai_socktype = SOCK_STREAM;
    addrHints.ai_protocol = IPPROTO_TCP;

    int getAddressResult = getaddrinfo("127.0.0.1", "666", &addrHints, &addrResultPointer);
    if (getAddressResult != 0) {
        cout << "Ошибка при получении информации об адресе" << endl;
        WSACleanup();
        return 1;
    }

    connectionSocket = socket(addrResultPointer->ai_family, addrResultPointer->ai_socktype, addrResultPointer->ai_protocol);
    if (connectionSocket == INVALID_SOCKET) {
        cout << "Ошибка при создании сокета" << endl;
        freeaddrinfo(addrResultPointer);
        WSACleanup();
        return 1;
    }

    int connectResult = connect(connectionSocket, addrResultPointer->ai_addr, (int)addrResultPointer->ai_addrlen);
    if (connectResult == SOCKET_ERROR) {
        cout << "Ошибка при соединении с сервером" << endl;
        closesocket(connectionSocket);
        WSACleanup();
        return 1;
    }

    cout << "Подключено к серверу" << endl;

    int receivedBytes;
    do {
        int sendingResult = send(connectionSocket, messageToSend, (int)strlen(messageToSend), 0);
        if (sendingResult == SOCKET_ERROR) {
            cout << "Ошибка при отправке" << endl;
            closesocket(connectionSocket);
            WSACleanup();
            return 1;
        }

        receivedBytes = recv(connectionSocket, receivedMessage, sizeof(receivedMessage), 0);
        if (receivedBytes > 0) {
            receivedMessage[receivedBytes] = '0';
            cout << "Получено " << receivedBytes << " байт: " << receivedMessage << endl;
        }
        else if (receivedBytes == 0) {
            cout << "Соединение закрыто сервером" << endl;
        }
        else {
            cout << "Ошибка при получении данных" << endl;
            closesocket(connectionSocket);
            WSACleanup();
            return 1;
        }

    } while (receivedBytes > 0);

    closesocket(connectionSocket);
    WSACleanup();
    return 0;
}
