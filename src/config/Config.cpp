#include "Config.hpp"

Config::Config() {}
Config::~Config() {}

ConfigRes_e Config::LoadFromFile(std::string fileName)
{
    std::ifstream is(fileName);
    if (!is.is_open())
    {
        return ConfigRes_e::FAILURE;
    }
    json config;
    is >> config;
    is.close();

    m_addrRobot = config["client"]["robot"];
    m_useFixedControl = config["client"]["usefixedcontrol"];
    m_addrControl = config["client"]["control"];
    m_addrServer = config["server"]["address"];
    m_portServer = config["server"]["port"];

    return ConfigRes_e::SUCCESS;
}

std::string Config::GetRobotAddr() const
{
    return m_addrRobot;
}
bool Config::GetUseFixedControl() const
{
    return m_useFixedControl;
}
std::string Config::GetControlAddr() const
{
    return m_addrControl;
}
std::string Config::GetServerAddr() const
{
    return m_addrServer;
}
int Config::GetServerPort() const
{
    return m_portServer;
}