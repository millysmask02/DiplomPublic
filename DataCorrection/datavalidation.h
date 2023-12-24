#ifndef DATAVALIDATION_H
#define DATAVALIDATION_H


class DataValidation
{
public:

    DataValidation();

    // задать значение параметру
    void setMaxCountOmissions(int omissions);
    void setMaxCountOutOfRange(int outOfRange);
    void setLimitJump(float jump);
    void setMaxCountJump(int countJump);

    // получить значение параметра
    int getMaxCountOmissions() const;
    int getMaxCountOutOfRange() const;
    float getLimitJump() const;
    int getMaxCountJump() const;

private:

    int _maxCountOmissions; // Максимальное число идущих подряд "пропусков" данных
    int _maxCountOutOfRange; // Максимальное число идущих подряд "выпадений" значений параметра за границы диапазона значений
    float _limitJump;       // Пороговое значение "прыжка"
    int _maxCountJump;      // Максимальное число идущих подряд "прыжков" значений параметра относительно его предыдущего значения

};

#endif // DATAVALIDATION_H
