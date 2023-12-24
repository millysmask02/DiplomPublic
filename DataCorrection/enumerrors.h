#ifndef ENUMERRORS_H
#define ENUMERRORS_H

enum class Validity
{
    Valid,
    OutOfRange
};

enum class CheckDataValidation
{
    Valid,
    ExcessMaxCountOutOfRange
};


enum class CorrectionResult
{
    Successfully,
    Unsuccessfully
};

enum class ReadWriteResult
{
    Successfully,
    ErrorReadFile,
    ErrorWriteFile,
    ParseError
};

#endif // ENUMERRORS_H
