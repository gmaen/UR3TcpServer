#include "main.hpp"

int main()
{
    LogWrapper::Instance().Init();
    LogInfo("main start");

    Config config;
    if (ConfigRes_e::SUCCESS != config.LoadFromFile()) {
        LogError("load config error!");
        return 1;
    }
    std::string addrRobot = config.GetRobotAddr();
    std::string addrControl = config.GetControlAddr();
    int port = config.GetServerPort();

    UR3TcpServer server(addrRobot, addrControl);
    if (HandleRes_e::HR_SUCCESS != server.ServerInit()) {
        LogError("init server error!");
        return 1;
    }
    if (HandleRes_e::HR_SUCCESS != server.ServerBind(port)) {
        LogError("bind error!");
        return 1;
    }
    if (HandleRes_e::HR_SUCCESS != server.ServerListen()) {
        LogError("listen error!");
        return 1;
    }

    fd_set fdReadSet;
    timeval ts;
    ts.tv_sec = 1;

    while (true) {
        if (HandleRes_e::HR_SUCCESS != server.ServerOnRun(fdReadSet, ts)) {
            LogError("running error!");
            return 1;
        }
    }

    server.ServerClose();

    return 0;
}
