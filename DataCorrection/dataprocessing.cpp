#include "dataprocessing.h"

DataProcessing::DataProcessing()
{

}

DataProcessing::DataProcessing(bool step, bool jitter, bool flow)
{
    _step = step;
    _jitter = jitter;
    _flow = flow;
}

void DataProcessing::setStep(bool value)
{
    _step = value;
}

void DataProcessing::setJitter(bool value)
{
    _jitter = value;
}

void DataProcessing::setFlow(bool value)
{
    _flow = value;
}

void DataProcessing::useAll()
{
    _step = true;
    _jitter = true;
    _flow = true;
}

bool DataProcessing::getStep() const
{
    return _step;
}

bool DataProcessing::getJitter() const
{
    return _jitter;
}

bool DataProcessing::getFlow() const
{
    return _flow;
}





