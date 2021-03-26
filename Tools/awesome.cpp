#include "awesome.hpp"

Awesome *Awesome::awesome = nullptr;

Awesome::Awesome()
{
}

Awesome *Awesome::getInstace()
{
    if (!awesome){
        awesome = new Awesome();
        awesome->initFontAwesome();
        awesome->options.insert( "color" , QColor(176,124,227));
    }
    return awesome;
}

QColor Awesome::getUiEmementColor()
{
    return QColor(176,124,227);
}

//(214,236,240)
QColor Awesome::getUiBackgroundColor()
{
    return QColor(214,236,240);
}
