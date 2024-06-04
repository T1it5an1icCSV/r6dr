#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <locale>


#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

int main() {

    setlocale(LC_ALL, "Russian");
    WSADATA wsaData;
    ADDRINFO hints;
    ADDRINFO* addrResult;
    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ConnectSocket = INVALID_SOCKET;
    char recvBuffer[512];

    const char* sendbuffer = "Здравствуйте!";

    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        cout << "WSAStartup завершилась с ошибкой: " << result << endl;
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    result = getaddrinfo(NULL, "666", &hints, &addrResult);
    if (result != 0) {
        cout << "getaddrinfo завершилась с ошибкой: " << result << endl;
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }

    ListenSocket = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        cout << "создание сокета завершилось с ошибкой" << endl;
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }

    result = bind(ListenSocket, addrResult->ai_addr, (int) addrResult->ai_addrlen);
    if (result == SOCKET_ERROR) {
        cout << "bind завершилась с ошибкой, код: " << result << endl;
        closesocket(ListenSocket);
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }

    result = listen(ListenSocket, SOMAXCONN);
    if (result == SOCKET_ERROR) {
        cout << "listen завершилась с ошибкой, код: " << result << endl;
        closesocket(ListenSocket);
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }

    ConnectSocket = accept(ListenSocket, NULL, NULL);
    if (ConnectSocket == INVALID_SOCKET) {
        cout << "accept завершилась с ошибкой, код: " << WSAGetLastError() << endl;
        closesocket(ListenSocket);
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }

    closesocket(ListenSocket);

    do {
        ZeroMemory(recvBuffer, 512);
        result = recv(ConnectSocket, recvBuffer, 512, 0);
        if (result > 0) {
            cout << "получено " << result << " байт" << endl;
            cout << "полученные данные: " << recvBuffer << endl;

            result = send(ConnectSocket, sendbuffer, (int)strlen(sendbuffer), 0);
            if (result == SOCKET_ERROR) {
                cout << "send завершилась с ошибкой, код: " << result << endl;
                closesocket(ConnectSocket);
                freeaddrinfo(addrResult);
                WSACleanup();
                return 1;
            }
        }
        else if (result == 0) {
            cout << "соединение закрывается" << endl;
        }
        else {
            cout << "recv завершилась с ошибкой, код: " << WSAGetLastError() << endl;
            closesocket(ConnectSocket);
            freeaddrinfo(addrResult);
            WSACleanup();
            return 1;
        }
    } while (result > 0);

    result = shutdown(ConnectSocket, SD_SEND);
    if (result == SOCKET_ERROR) {
        cout << "shutdown завершилась с ошибкой, код: " << result << endl;
        closesocket(ConnectSocket);
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }

    closesocket(ConnectSocket);
    freeaddrinfo(addrResult);
    WSACleanup();
    return 0;
}
