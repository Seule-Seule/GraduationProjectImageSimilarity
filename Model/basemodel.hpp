#ifndef BASEMODEL_HPP
#define BASEMODEL_HPP

#include <QString>

class BaseModel
{
public:
    BaseModel();

protected:
    virtual void debugMessage(const QString message) = 0;
};

#endif // BASEMODEL_HPP
