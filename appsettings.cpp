#include "appsettings.h"

AppSettings::AppSettings()
{

}
AppSettings::~AppSettings()
{

}

AppSettings &AppSettings::instance()
{
    static AppSettings res;
    return res;
}

void AppSettings::load()
{

}
void AppSettings::save()
{

}

unsigned AppSettings::screenWidth() const
{
    static unsigned res{800};
    return  res;
}
unsigned AppSettings::screenHeight() const
{
    static unsigned res{600};
    return res;
}
