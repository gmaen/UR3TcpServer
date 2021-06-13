#include "Config.hpp"

Config::Config() {}
Config::~Config() {}

ConfigRes_e Config::LoadFromFile(std::string fileName)
{
    std::ifstream is(fileName);
    if (!is.is_open()) {
        return ConfigRes_e::FAILURE;
    }
    json config;
    is >> config;
    is.close();

    m_addrRobot = config["address"]["robot"];
    m_addrControl = config["address"]["control"];
    m_portServer = config["server"]["port"];

    return ConfigRes_e::SUCCESS;
}

std::string Config::GetRobotAddr() const
{
    return m_addrRobot;
}
std::string Config::GetControlAddr() const
{
    return m_addrControl;
}
int Config::GetServerPort() const
{
    return m_portServer;
}