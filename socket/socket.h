#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

namespace win32 {
    class socket {
    public:
        socket(LPCWSTR strHost, LPCWSTR strPort) {
            WSADATA wsaData;
            int err = WSAStartup(
                MAKEWORD(2, 2),
                &wsaData
            );
            ADDRINFOW hints;
            ZeroMemory(
                &hints,
                sizeof(hints)
            );
            hints.ai_family = AF_INET;
            hints.ai_socktype = SOCK_STREAM;
            hints.ai_protocol = IPPROTO_TCP;
            err = GetAddrInfoW(
                strHost,
                strPort,
                &hints,
                &this->paiw
            );
        };
        ~socket() {
            FreeAddrInfoW(this->paiw);
            WSACleanup();
        };
        void open() {
            this->sock = ::socket(
                this->paiw->ai_family,
                this->paiw->ai_socktype,
                this->paiw->ai_protocol
            );
        }
        void close() {
            closesocket(this->sock);
            this->sock = INVALID_SOCKET;
        }
        int connect() {
            return ::connect(
                this->sock,
                this->paiw->ai_addr,
                (int)this->paiw->ai_addrlen
            );
        }
        int send(const char* buf, int len) {
            return ::send(
                this->sock, 
                buf, 
                len, 
                0
            );
        }
        int recv(char* buf, int len) {
            return ::recv(
                this->sock, 
                buf, 
                len, 
                0
            );
        }
    private:
        PADDRINFOW paiw;
        SOCKET sock;
    };
}
