#include "loader.h"

Loader::Loader()
{

}

ReadWriteResult Loader::readData(const std::string path, std::vector<NavigationData>& data)
{
    try {
        std::ifstream rFile(path);
        if (rFile.is_open()) {
            std::string str;
            std::getline(rFile, str);

            while (std::getline(rFile, str)) {
                std::vector<std::string> vecParam;
                parseString(str, vecParam);
                NavigationData tmp;
                parseVector(vecParam, tmp);
                data.push_back(tmp);
            }
            rFile.close();
            return ReadWriteResult::Successfully;
        }
        else {
            return ReadWriteResult::ErrorReadFile;
        }
    }
    catch(...) {
        return ReadWriteResult::ErrorReadFile;
    }
}

// dd_mm_yyyy hh_mm_ss
std::string timeToString(const std::tm& time) {
    std::string res = "";
    res = res + std::to_string(time.tm_mday) + ".";
    res = res + std::to_string(time.tm_mon + 1) + ".";
    res = res + std::to_string(time.tm_year) + " ";
    res = res + std::to_string(time.tm_hour + 1) + ":";
    res = res + std::to_string(time.tm_min) + ":";
    res = res + std::to_string(time.tm_sec);
    return res;
}

ReadWriteResult Loader::writeData(const std::string path, const std::vector<NavigationData>& data)
{
    try {
        std::ofstream wFile(path, std::ios::trunc);
        if (wFile.is_open()) {
            wFile << "idx,time,latitude,longitude,altitude,track angle,speed,roll,pitch,drift" << std::endl;
            const std::string comma(",");
            for (auto navigData : data) {
                wFile << std::to_string(navigData.idx) << comma
                      << timeToString(navigData.time) << comma
                      << std::to_string(navigData.latitude.value()) << comma
                      << std::to_string(navigData.longitude.value()) << comma
                      << std::to_string(navigData.altitude.value()) << comma
                      << std::to_string(navigData.trackAngle.value()) << comma
                      << std::to_string(navigData.speed.value()) << comma
                      << std::to_string(navigData.roll.value()) << comma
                      << std::to_string(navigData.pitch.value()) << comma
                      << std::to_string(navigData.drift.value()) << std::endl;
            }
            wFile.close();
            return ReadWriteResult::Successfully;
        }
        else {
            return ReadWriteResult::ErrorWriteFile;
        }
    }
    catch(...) {
        return ReadWriteResult::ErrorWriteFile;
    }
}

ReadWriteResult Loader::parseVector(const std::vector<std::string> &vec, NavigationData &data)
{
    try {
        int indx = 0;
        data.idx = std::stoi(vec[indx ++]);
        // время
        data.latitude = std::stof(vec[indx ++]);
        data.longitude = std::stof(vec[indx ++]);
        data.altitude = std::stof(vec[indx ++]);
        data.trackAngle = std::stof(vec[indx ++]);
        data.speed = std::stof(vec[indx ++]);
        data.roll = std::stof(vec[indx ++]);
        data.pitch = std::stof(vec[indx ++]);
        data.drift = std::stoi(vec[indx ++]);

        return ReadWriteResult::Successfully;
    }
    catch(...) {
        return ReadWriteResult::ParseError;
    }

}

ReadWriteResult Loader::parseString(const std::string &str, std::vector<std::string>& vecNavig)
{
    std::stringstream stream(str);
    std::string tmp;
    while(std::getline(stream, tmp, ',')) {
        vecNavig.push_back(tmp);
    }
    if (vecNavig.size() > 10) {
        return ReadWriteResult::ParseError;
    }
    return ReadWriteResult::Successfully;
}
