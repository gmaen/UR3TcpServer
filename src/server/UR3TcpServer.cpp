#include "UR3TcpServer.hpp"

UR3TcpServer::UR3TcpServer(std::string& addrRobot, std::string& addrControl, bool useFixedControl)
    : m_addrRobot(addrRobot), m_addrControl(addrControl), m_useFixedControl(useFixedControl),
      m_fdServer(INVALID_SOCKET), m_fdRobot(INVALID_SOCKET),
      m_fdControl(INVALID_SOCKET), m_fdMax(INVALID_SOCKET)
{

}

UR3TcpServer::~UR3TcpServer()
{
    ServerClose();
}

HandleRes_e UR3TcpServer::ServerInit()
{
#ifdef _WIN32
    WORD version = MAKEWORD(2,2);
    WSADATA wsadata;
    if (WSAStartup(version, &wsadata) != 0)
    {
        LogError("WSAStartup Error...");
        return HandleRes_e::HR_FAILURE;
    }
#endif /* _WIN32 */

    // 1 create
    m_fdServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (SOCKET_ERROR == m_fdServer) {
        LogError("Socket Error...");
        return HandleRes_e::HR_FAILURE;
    }
    m_fdMax = m_fdServer;
    return HandleRes_e::HR_SUCCESS;
}

HandleRes_e UR3TcpServer::ServerBind(unsigned short port, const char* ip)
{
    sockaddr_in addrServer = {};
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(port);
#ifdef _WIN32
    if (ip) {
        addrServer.sin_addr.S_un.S_addr = inet_addr(ip);
    }
    else {
        addrServer.sin_addr.S_un.S_addr = INADDR_ANY;
    }
#else /* _WIN32 */
    if (ip) {
        addrServer.sin_addr.s_addr = inet_addr(ip);
    }
    else {
        addrServer.sin_addr.s_addr = INADDR_ANY;
    }
#endif /* _WIN32 */

    int bindRet = bind(m_fdServer, (sockaddr*)&addrServer, sizeof(sockaddr_in));
    if (SOCKET_ERROR == bindRet) {
        LogError("Bind Error...");
        ServerClose();
        return HandleRes_e::HR_FAILURE;
    }
    return HandleRes_e::HR_SUCCESS;
}

HandleRes_e UR3TcpServer::ServerListen(int n)
{
    int listenRet = listen(m_fdServer, n);
    if (SOCKET_ERROR == listenRet) {
        LogError("Listen Error...");
        ServerClose();
        return HandleRes_e::HR_FAILURE;
    }
    return HandleRes_e::HR_SUCCESS;
}

HandleRes_e UR3TcpServer::ServerOnRun(fd_set& fdReadSet, timeval& ts)
{
    FD_ZERO(&fdReadSet);

    FD_SET(m_fdServer, &fdReadSet);
    if (INVALID_SOCKET != m_fdRobot) {
        FD_SET(m_fdRobot, &fdReadSet);
    }
    if (INVALID_SOCKET != m_fdControl) {
        FD_SET(m_fdControl, &fdReadSet);
    }

    int selRet = select(m_fdMax + 1, &fdReadSet, NULL, NULL, &ts);
    if (selRet < 0) {
        LogError("Select Error...");
        ServerClose();
        return HandleRes_e::HR_FAILURE;
    }

    if (FD_ISSET(m_fdServer, &fdReadSet)) {
        FD_CLR(m_fdServer, &fdReadSet);
        ServerAccept();
    }
    if (FD_ISSET(m_fdRobot, &fdReadSet)) {
        FD_CLR(m_fdRobot, &fdReadSet);
        ServerTransmit(m_fdRobot, m_fdControl);
    }
    if (FD_ISSET(m_fdControl, &fdReadSet)) {
        FD_CLR(m_fdControl, &fdReadSet);
        ServerTransmit(m_fdControl, m_fdRobot);
    }
    return HandleRes_e::HR_SUCCESS;
}

HandleRes_e UR3TcpServer::ServerAccept()
{
    sockaddr_in addrClient = {};
    int nAddrLen = sizeof(sockaddr_in);
    SOCKET fdClient = INVALID_SOCKET;

#ifdef _WIN32
    fdClient = accept(m_fdServer, (sockaddr*)&addrClient, &nAddrLen);
#else
    fdClient = accept(m_fdServer, (sockaddr*)&addrClient, (socklen_t *)&nAddrLen);
#endif
    if (INVALID_SOCKET == fdClient) {
        LogError("Client Socket Error...");
        return HandleRes_e::HR_FAILURE;
    }
    std::string addr = inet_ntoa(addrClient.sin_addr);
    LogInfo("Client IP: {0} fd: {1}", addr, fdClient);

    if (m_fdMax < fdClient) {
        m_fdMax = fdClient;
    }
    if (INVALID_SOCKET == m_fdRobot && addr == m_addrRobot) {
        m_fdRobot = fdClient;
    }
    else if (INVALID_SOCKET == m_fdControl && (!m_useFixedControl || addr == m_addrControl)) {
        m_fdControl = fdClient;
    }
    else {
#ifdef _WIN32
        closesocket(fdClient);
#else /* _WIN32 */
        close(fdClient);
#endif /* _WIN32 */
    }
    return HandleRes_e::HR_SUCCESS;
}

HandleRes_e UR3TcpServer::ServerTransmit(SOCKET& fdSrc, SOCKET& fdDst)
{
    char buf[BUFFER_SIZE];
    int recvLen = (int)recv(fdSrc, buf, BUFFER_SIZE, 0);
    if (recvLen > 0) {
        if (INVALID_SOCKET != fdDst) {
            send(fdDst, buf, recvLen, 0);
        }
        return HandleRes_e::HR_SUCCESS;
    }
    else {
#ifdef _WIN32
        closesocket(fdSrc);
#else /* _WIN32 */
        close(fdSrc);
#endif /* _WIN32 */
        fdSrc = INVALID_SOCKET;
        return HandleRes_e::HR_FAILURE;
    }
}

void UR3TcpServer::ServerClose()
{
#ifdef _WIN32
    if (INVALID_SOCKET != m_fdServer) {
        if (INVALID_SOCKET != m_fdRobot) {
            closesocket(m_fdRobot);
        }
        if (INVALID_SOCKET != m_fdControl) {
            closesocket(m_fdControl);
        }
        closesocket(m_fdServer);


        WSACleanup();
    }
#else /* _WIN32 */
    if (INVALID_SOCKET != m_fdServer) {
        if (INVALID_SOCKET != m_fdRobot) {
            close(m_fdRobot);
        }
        if (INVALID_SOCKET != m_fdControl) {
            close(m_fdControl);
        }
        close(m_fdServer);
    }
#endif /* _WIN32 */
}