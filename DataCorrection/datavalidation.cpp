#include "datavalidation.h"

DataValidation::DataValidation()
    :   _maxCountOmissions(),
        _maxCountOutOfRange(),
        _limitJump(),
        _maxCountJump()
{

}

void DataValidation::setMaxCountOmissions(int omissions)
{
    _maxCountOmissions = omissions;
}

void DataValidation::setMaxCountOutOfRange(int outOfRange)
{
    _maxCountOutOfRange = outOfRange;
}

void DataValidation::setLimitJump(float jump)
{
    _limitJump = jump;
}

void DataValidation::setMaxCountJump(int countJump)
{
    _maxCountJump = countJump;
}

int DataValidation::getMaxCountOmissions() const
{
    return _maxCountOmissions;
}

int DataValidation::getMaxCountOutOfRange() const
{
    return _maxCountOutOfRange;
}

float DataValidation::getLimitJump() const
{
    return _limitJump;
}

int DataValidation::getMaxCountJump() const
{
    return _maxCountJump;
}

