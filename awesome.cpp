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
