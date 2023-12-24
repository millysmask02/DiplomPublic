#include "datacorrection.h"

const float maxLatitude = 90;
const float maxLongitude = 180;
const float minAltitude = -500;
const float maxAltitude = 20000;
const float minTrackAngle = 0;
const float maxTrackAngle = 360;
const float minSpeed = 0;
const float maxSpeed = 1000;
const float maxAngles = 20;


DataCorrection::DataCorrection(const std::vector<NavigationData> &inputRowData)
{
    _rowData = inputRowData;
}

void DataCorrection::setProcessingType(const DataProcessing &data)
{
    _paramCorrecting = data;
}

void DataCorrection::setDataValidation(const DataValidation &data)
{
    _paramValidation = data;
}

CorrectionResult DataCorrection::startCorrection()
{
    if (parseRowData() == CheckDataValidation::Valid) {
        if (_paramCorrecting.getStep()) {
            stepInterpolation();
        }
        if (_paramCorrecting.getJitter()) {
            jitterCorrection();
        }
        if (_paramCorrecting.getFlow()) {
            slipFilter();
        }
        return CorrectionResult::Successfully;
    }
    return CorrectionResult::Unsuccessfully;
}

const std::vector<std::map<int, float>>& DataCorrection::parseCorrectedData()
{
    return _parseData;
}

const std::vector<NavigationData>& DataCorrection::data()
{
    unsigned int sizeData = countData();
    _correctedData.reserve(sizeData);
    for (unsigned int i = 0; i < sizeData; ++i) {
        int j = 0;
        NavigationData tmp{i, _rowData[i].time, _parseData[j++][i],
                           _parseData[j++][i], _parseData[j++][i],
                           _parseData[j++][i], _parseData[j++][i],
                           _parseData[j++][i], _parseData[j++][i],
                           _parseData[j++][i]};
        _correctedData[i] = tmp;
    }
    return _correctedData;
}

void DataCorrection::stepInterpolation()
{
    for (auto mapParam : _parseData) {
        for (auto it = mapParam.begin(); it != mapParam.end(); ++it) {
            auto next = it;
            next++;
            for (int i = it->first + 1; i < next->first; ++i) {
                mapParam[i] = mapParam[it->first] + ((i - it->first) *
                             (mapParam[next->first] -  mapParam[it->first]) /
                             (next->first - it->first));
            // y = y1 + (x - x1)(y2 - y1) / (x2 - x1)
            }
        }
    }

}

void DataCorrection::jitterCorrection()
{

}

void DataCorrection::slipFilter()
{

}

CheckDataValidation DataCorrection::parseRowData()
{
    _parseData.reserve(8);
    int maxCountOutOfRange = _paramValidation.getMaxCountOutOfRange();
    std::vector<int> invalidParam(8, 0);

    std::map<int, float> paramLatitude;
    std::map<int, float> paramLongitude;
    std::map<int, float> paramAltitude;
    std::map<int, float> paramTrAngle;
    std::map<int, float> paramSpeed;
    std::map<int, float> paramRoll;
    std::map<int, float> paramPitch;
    std::map<int, float> paramDrift;
    for (auto i : _rowData) {
        std::vector<int> copyInvalid(8, 0);
        if (isValid(i, copyInvalid) == Validity::OutOfRange) {
            for(unsigned int i = 0; i < copyInvalid.size(); ++i) {
                if(copyInvalid[i] == 0) {
                    invalidParam[i] = 0;
                }
                else {
                    invalidParam[i]++;
                }
                if (copyInvalid[i] > maxCountOutOfRange) {
                    return CheckDataValidation::ExcessMaxCountOutOfRange;
                }
            }
        }
        int j = 0;
        if (i.latitude.has_value() && !copyInvalid[j++]) {
            paramLatitude[i.idx] = i.latitude.value();
        }
        if (i.longitude.has_value() && !copyInvalid[j++]) {
            paramLongitude[i.idx] = i.longitude.value();
        }
        if (i.altitude.has_value() && !copyInvalid[j++]) {
            paramAltitude[i.idx] = i.altitude.value();
        }
        if (i.trackAngle.has_value() && !copyInvalid[j++]) {
            paramTrAngle[i.idx] = i.trackAngle.value();
        }
        if (i.speed.has_value() && !copyInvalid[j++]) {
            paramSpeed[i.idx] = i.speed.value();
        }
        if (i.roll.has_value() && !copyInvalid[j++]) {
            paramRoll[i.idx] = i.roll.value();
        }
        if (i.pitch.has_value() && !copyInvalid[j++]) {
            paramPitch[i.idx] = i.pitch.value();
        }
        if (i.drift.has_value() && !copyInvalid[j++]) {
            paramDrift[i.idx] = i.drift.value();
        }
    }

    _parseData.push_back(paramLatitude);
    _parseData.push_back(paramLongitude);
    _parseData.push_back(paramAltitude);
    _parseData.push_back(paramTrAngle);
    _parseData.push_back(paramSpeed);
    _parseData.push_back(paramRoll);
    _parseData.push_back(paramPitch);
    _parseData.push_back(paramDrift);
    return CheckDataValidation::Valid;
}

Validity DataCorrection::isValid(const NavigationData &data, std::vector<int> &invalid)
{
    int j = 0;
    bool flag = true;
    if (!(data.latitude >= -maxLatitude && data.latitude <= maxLatitude)) {
        invalid[j++]++;
        flag = false;
    }
    if (!(data.longitude >= -maxLongitude && data.longitude <= maxLongitude)) {
        invalid[j++]++;
        flag = false;
    }
    if (!(data.altitude >= minAltitude && data.altitude <= maxAltitude)) {
        invalid[j++]++;
        flag = false;
    }
    if (!(data.trackAngle >= minTrackAngle && data.trackAngle <= maxTrackAngle)) {
        invalid[j++]++;
        flag = false;
    }
    if (!(data.speed >= minSpeed && data.speed <= maxSpeed)) {
        invalid[j++]++;
        flag = false;
    }
    if (!(data.roll >= -maxAngles && data.roll <= maxAngles)) {
        invalid[j++]++;
        flag = false;
    }
    if (!(data.pitch >= -maxAngles && data.pitch <= maxAngles)) {
        invalid[j++]++;
        flag = false;
    }
    if (!(data.drift>= -maxAngles && data.drift <= maxAngles)) {
        invalid[j++]++;
        flag = false;
    }

    if (flag) {
        return Validity::Valid;
    }

    return Validity::OutOfRange;
}

int DataCorrection::countData() const
{
    return _rowData.back().idx;
}
