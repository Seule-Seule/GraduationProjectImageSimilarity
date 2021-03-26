#ifndef BASECONTROLLER_HPP
#define BASECONTROLLER_HPP

#include "View/baseview.hpp"
#include "Model/basemodel.hpp"

class BaseController
{
public:
    explicit BaseController();

public:

protected:
    BaseView *view;
    BaseController *model;
};

#endif // BASECONTROLLER_HPP
