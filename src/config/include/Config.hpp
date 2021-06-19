#ifndef _UR3_CONFIG_HPP_
#define _UR3_CONFIG_HPP_

#include <string>
#include <fstream>
#include "json.hpp"

#define DEFAULT_CONFIG "config.json"

using json = nlohmann::json;

typedef enum
{
    SUCCESS,
    FAILURE
} ConfigRes_e;

class Config
{
public:
    Config();
    virtual ~Config();

    ConfigRes_e LoadFromFile(std::string fileName = DEFAULT_CONFIG);

    std::string GetRobotAddr() const;
    bool GetUseFixedControl() const;
    std::string GetControlAddr() const;
    std::string GetServerAddr() const;
    int GetServerPort() const;

private:
    std::string m_addrRobot;
    bool m_useFixedControl;
    std::string m_addrControl;
    std::string m_addrServer;
    int m_portServer;
};

#endif /* _UR3_CONFIG_HPP_ */