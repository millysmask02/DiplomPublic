#ifndef LOADER_H
#define LOADER_H
#include "navigationdata.h"
#include "enumerrors.h"
#include <fstream>
#include <sstream>
//#include <string>
#include <vector>


class Loader
{
public:
    // ниче не делает
    Loader();
    // принимает файл и читает данные навигации в data, проблемы с файлом - возвр ошибку
    ReadWriteResult readData(const std::string path, std::vector<NavigationData>& data);
    // принимает файл, в который записывать данные и сами данные
    ReadWriteResult writeData(const std::string path, const std::vector<NavigationData>& data);

private:
    // парсит строку из файла на вектор строк, каждая мини-строка - параметр
    ReadWriteResult parseString(const std::string& str, std::vector<std::string>& vecNavig);
    // раскидывает данные из вектора по структуре
    ReadWriteResult parseVector(const std::vector<std::string>& vec, NavigationData &data);
};

#endif // LOADER_H
