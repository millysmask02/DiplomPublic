#ifndef NAVIGATIONDATA_H
#define NAVIGATIONDATA_H

#include <QDateTime>
#include "enumerrors.h"
#include <optional>
#include <ctime>

// NAVIGATIONDATASHARED_EXPORT
struct NavigationData
{
    unsigned int idx;   // Порядковый номер [0,1,2...]
    // NOTE переделать под время стл

    std::tm time; // Временная метка отсчета
    //QDateTime time;

    // Местоположение самолета-носителя
    std::optional<float> latitude;     // широта (градусы) [-90; 90]
    std::optional<float> longitude;    // долгота (градусы) [-180; 180]
    std::optional<float> altitude;     // высота (метры) [-500; 20000]

    // Вектор скорости самолета-носителя
    std::optional<float> trackAngle;   // путевой угол (градусы) [0; 360]
    std::optional<float> speed;        // скорость (км/ч) [0; 1000]

    // Углы положения самолета-носителя
    std::optional<float> roll;         // крен (градусы) [-20; 20]
    std::optional<float> pitch;        // тангаж (градусы) [-20; 20]
    std::optional<float> drift;        // снос (градусы) [-20; 20]
};

#endif // NAVIGATIONDATA_H
