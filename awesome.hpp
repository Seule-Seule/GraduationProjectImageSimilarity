#ifndef AWESOME_HPP
#define AWESOME_HPP

#include "tool.hpp"

#include "QtAwesome.h"

#include "QVariantMap"

class Awesome : public QtAwesome
{
private:
    Awesome();

public:
    static Awesome *getInstace();

private:
    static Awesome *awesome;

public:
    QVariantMap options;
};

#endif // AWESOME_HPP
