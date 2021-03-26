#ifndef BASEVIEW_HPP
#define BASEVIEW_HPP

#include <QObject>

class BaseView
{
public:
    explicit BaseView();

public :
    virtual void update() = 0;
    virtual  void debugMessage(QString message) = 0;



protected:

};

#endif // BASEVIEW_HPP
