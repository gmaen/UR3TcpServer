#ifndef _UR3_TCPSERVER_HPP_
#define _UR3_TCPSERVER_HPP_

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <windows.h>
#include <winsock2.h>
#else /* _WIN32 */
#include <unistd.h>
#include <arpa/inet.h>

typedef int SOCKET;
#define INVALID_SOCKET (SOCKET)(~0)
#define SOCKET_ERROR (-1)
#endif /* _WIN32 */

#include <iostream>
#include <string>
#include "LogWrapper.hpp"

#define BUFFER_SIZE (1024)
#define LISTEN_N (5)

typedef enum
{
    HR_SUCCESS,
    HR_FAILURE
} HandleRes_e;

class UR3TcpServer
{
public:
    UR3TcpServer(std::string &addrRobot, std::string &addrControl, bool useFixedControl);
    virtual ~UR3TcpServer();

    HandleRes_e ServerInit();
    HandleRes_e ServerBind(unsigned short port, const char *ip = nullptr);
    HandleRes_e ServerListen(int n = LISTEN_N);
    HandleRes_e ServerOnRun(fd_set &fdReadSet, timeval &ts);
    HandleRes_e ServerAccept();
    HandleRes_e ServerTransmit(SOCKET &src, SOCKET &dst);
    void ServerClose();

private:
    SOCKET m_fdServer;
    SOCKET m_fdRobot;
    SOCKET m_fdControl;

    SOCKET m_fdMax;

    std::string m_addrRobot;
    std::string m_addrControl;
    bool m_useFixedControl;
};
#endif /* _UR3_TCPSERVER_HPP_ */