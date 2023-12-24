#ifndef DATAPROCESSING_H
#define DATAPROCESSING_H


class DataProcessing
{
public:
    DataProcessing();
    DataProcessing(bool step, bool jitter, bool flow); // задать все параметры при создании

    // задать один из параметров или все
    void setStep(bool value);
    void setJitter(bool value);
    void setFlow(bool value);
    void useAll();

    // получить значения параметров
    bool getStep() const;
    bool getJitter() const;
    bool getFlow() const;

private:
    bool _step = false;    // Признак интерполяции "ступенек"
    bool _jitter = false;  // Признак корректировки "дрожания"
    bool _flow = false;    // Признак и параметры применения "скользящего" фильтра
};

#endif // DATAPROCESSING_H
