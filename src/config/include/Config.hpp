#ifndef _UR3_CONFIG_HPP_
#define _UR3_CONFIG_HPP_

#include <string>
#include <fstream>
#include "json.hpp"

#define DEFAULT_CONFIG "config.json"

using json = nlohmann::json;

typedef enum {
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
    std::string GetControlAddr() const;
    int GetServerPort() const;
private:
    std::string m_addrRobot;
    std::string m_addrControl;
    int m_portServer;
};

#endif /* _UR3_CONFIG_HPP_ */