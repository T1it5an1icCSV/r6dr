#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <locale>

using namespace std;

int main() {

    setlocale(LC_ALL, "Russian");

    // служебная структура для хранение информации (ВЕРСИИ, СТРУКТУРЫ(НАПРИМЕР СЕМЕЙНУЮ)
   // о реализации Windows Sockets
    WSADATA wsaDataInfo;
    ADDRINFO addrHints;
    ADDRINFO* addrResult;
    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ConnectSocket = INVALID_SOCKET; //слушает соединение
    char recvBuffer[512];

    const char* sendbuffer = "Здравствуйте! От сервера)!";

    // старт использования библиотеки сокетов процессом определния версии и структуры
    int result = WSAStartup(MAKEWORD(2, 2), &wsaDataInfo);
    // Если произошла ошибка подгрузки библиотеки
    if (result != 0) {
        cout << "WSAStartup завершилась с ошибкой: " << result << endl;
        return 1;
    }

    ZeroMemory(&addrHints, sizeof(addrHints));//нам необходимо изначально занулить память, 1-ый паметр, что зануляем,2-ой сколько
    addrHints.ai_family = AF_INET;
    addrHints.ai_socktype = SOCK_STREAM;//задаем потоковый тип сокета
    addrHints.ai_protocol = IPPROTO_TCP;// Используем протокол TCP
    addrHints.ai_flags = AI_PASSIVE;// Пассивная сторона, потому что просто ждет соединения

    // функциия хранит в себе адрес, порт,семейство структур, адрес сокета
    result = getaddrinfo(NULL, "666", &addrHints, &addrResult);
    // Если инициализация структуры адреса завершилась с ошибкой,
    // выведем сообщением об этом и завершим выполнение программы 
    if (result != 0) {
        cout << "getaddrinfo завершилась с ошибкой: " << result << endl;
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }

    ListenSocket = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol);
    // Если создание сокета завершилось с ошибкой, выводим сообщение,
   // освобождаем память, выделенную под структуру addr,
    if (ListenSocket == INVALID_SOCKET) {
        cout << "создание сокета завершилось с ошибкой" << endl;
        freeaddrinfo(addrResult);
        WSACleanup();//очситка WSAStartup
        return 1;
    }

    // Привязываем сокет к IP-адресу (соединились с сервером)
    result = bind(ListenSocket, addrResult->ai_addr, (int)addrResult->ai_addrlen);
    // Если привязать адрес к сокету не удалось, то выводим сообщение
   // об ошибке, освобождаем память, выделенную под структуру addr.
   // и закрываем открытый сокет.
   // Выгружаем DLL-библиотеку из памяти и закрываем программу.
    if (result == SOCKET_ERROR) {
        cout << "bind завершилась с ошибкой, код: " << result << endl;
        closesocket(ListenSocket);
        freeaddrinfo(addrResult);
        WSACleanup();//очситка WSAStartup
        return 1;
    }

    //слушаем подключения клиентов к сокету ListenSocket.
    result = listen(ListenSocket, SOMAXCONN);
    if (result == SOCKET_ERROR) {
        cout << "listen завершилась с ошибкой, код: " << result << endl;
        closesocket(ListenSocket);
        freeaddrinfo(addrResult);
        WSACleanup();//в случае ошибки закрываем сокет и очищаем память
        return 1;
    }

    //принимаем входящее соединение и получаем сокет для общения с клиентом.
    ConnectSocket = accept(ListenSocket, NULL, NULL);
    if (ConnectSocket == INVALID_SOCKET) {
        cout << "accept завершилась с ошибкой, код: " << WSAGetLastError() << endl;
        closesocket(ListenSocket);
        freeaddrinfo(addrResult);
        WSACleanup();//в случае ошибки закрываем сокет и очищаем память к остальным двум тоже относиться
        return 1;
    }

    closesocket(ListenSocket);
    // цикл работает, пока есть данные для чтения
    do {
        ZeroMemory(recvBuffer, 512);
        result = recv(ConnectSocket, recvBuffer, 512, 0);
        //если чтение данных прошло успешно, то выводим количество и сами данные
        if (result > 0) {
            cout << "получено " << result << " байт" << endl;
            cout << "полученные данные: " << recvBuffer << endl;

            result = send(ConnectSocket, sendbuffer, (int)strlen(sendbuffer), 0);
            //отправляем ответ клиенту, затем проверяем наличие ошибок при отправке
            if (result == SOCKET_ERROR) {
                cout << "send завершилась с ошибкой, код: " << result << endl;
                closesocket(ConnectSocket);
                freeaddrinfo(addrResult);
                WSACleanup();//в случае ошибки закрываем сокет и очищаем память
                return 1;
            }
        }
        //закрываем отправку данных для клиента
        else if (result == 0) {
            cout << "соединение закрывается" << endl;
        }
        //если произошла ошибка при завершении соединения, вывести сообщение, закрывать сокет, освобождить память и закрывить программу
        else {
            cout << "recv завершилась с ошибкой, код: " << WSAGetLastError() << endl;
            closesocket(ConnectSocket);
            freeaddrinfo(addrResult);
            WSACleanup();//в случае ошибки закрываем сокеты и очищаем память
            return 1;
        }
    } while (result > 0);

    //обрабатываем случай ошибки при закрытии сокета
    result = shutdown(ConnectSocket, SD_SEND);
    if (result == SOCKET_ERROR) {
        cout << "shutdown завершилась с ошибкой, код: " << result << endl;
        closesocket(ConnectSocket);
        freeaddrinfo(addrResult);
        WSACleanup();//в случае ошибки закрываем сокеты и очищаем память
        return 1;
    }

    //закрываем сокеты, освобождаем ресурсы и завершаем программу
    closesocket(ConnectSocket);
    freeaddrinfo(addrResult);
    WSACleanup();//закрываем сокеты и очищаем память
    return 0;
}
