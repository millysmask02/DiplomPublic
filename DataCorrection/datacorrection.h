#ifndef DATACORRECTION_H
#define DATACORRECTION_H

#include <vector>
#include <map>
#include "datacorrection_global.h"
#include "navigationdata.h"
#include "dataprocessing.h"
#include "datavalidation.h"

/*
записывать скорректированные данные в этот файл
сравнивать, что данные рил перезаписались или не изменились
(сравнить, что данные в файлах одинаковые/различные)
NAVIGATIONDATASHARED_EXPORT???
20.12
почитать про шапки файла
ВРЕМЯ
дописать возврат ошибок

*/

class DATACORRECTIONSHARED_EXPORT DataCorrection
{

public:
    DataCorrection(const std::vector<NavigationData> &inputRowData); // принимает вектор данных

    void setProcessingType(const DataProcessing &data); // принимает данные о видах обработки данных

    void setDataValidation(const DataValidation &data); // принимает данные о данных валидации данных

    CorrectionResult startCorrection(); // запуск корректировки

    const std::vector<std::map<int, float>> &parseCorrectedData(); // возвращает вектор с мапами данных
    const std::vector<NavigationData> &data(); // возвращает вектор данных

private:
    void stepInterpolation(); // интерполяция ступенек
    void jitterCorrection();  // интерполяция дрожания
    void slipFilter();        // фильтр
    CheckDataValidation parseRowData(); // парсим на вектор мапов
    Validity isValid(const NavigationData &data, std::vector<int> &invalid);
    int countData() const;     // возвращает, сколько у нас отсчетов (колво данных)

    std::vector<std::map<int, float>> _parseData; //распарсили сюда
    std::vector<NavigationData> _rowData;       // изначальные сырые данные
    std::vector<NavigationData> _correctedData; // обработанные данные


    DataProcessing _paramCorrecting; // используемые виды обработки
    DataValidation _paramValidation; // параметры валидации
};

#endif // DATACORRECTION_H
