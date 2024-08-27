#pragma once

#include <unordered_map>
#include <iostream>
#include <boost/variant.hpp>
#include <vector>

#define PI 3.141592
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef signed int int32;

class Parameter
{
public:
    Parameter(){};
    ~Parameter(){};

    bool modifyParam(std::string key, boost::variant<int, std::string> value)
    {
        if (params.find(key) == params.end())
            return false;
        params[key] = value;
        return true;
    }
    bool insertParam(std::string key, boost::variant<int, std::string> value)
    {
        if (params.find(key) == params.end())
        {
            params[key] = value;
            return true;
        }

        return false;
    }
    int getParamInt(std::string key)
    {
        auto iter = params.find(key);
        if (iter != params.end())
        {
            if (iter->second.which() == 0)
                return boost::get<int>(iter->second);
        }
        return 0;
    }
    std::string getParamStr(std::string key)
    {
        auto iter = params.find(key);
        if (iter != params.end())
        {
            if (iter->second.which() == 1)
                return boost::get<std::string>(iter->second);
        }
        return "";
    }
    boost::variant<int, std::string> getParamVar(std::string key)
    {
        auto iter = params.find(key);
        if (iter != params.end())
        {
            return iter->second;
        }
        return boost::variant<int, std::string>{};
    }
    std::unordered_map<std::string, boost::variant<int, std::string>> getAllParams()
    {
        return params;
    }
    void printAllParams()
    {
        std::cout << "---------------------------------\n";
        for (auto iter = params.begin(); iter != params.end(); ++iter)
        {
            std::cout << "[" << iter->first << "] : " << iter->second << std::endl;
        }
        std::cout << "---------------------------------\n";
        return;
    }

private:
    std::unordered_map<std::string, boost::variant<int, std::string>> params;
};