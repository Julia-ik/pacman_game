#ifndef APPSETTINGS_H
#define APPSETTINGS_H
#include <QString>

class AppSettings
{
public:
    AppSettings(const AppSettings &)=delete;
    AppSettings & operator =(const AppSettings &)= delete;
    static AppSettings & instance();

    void load();
    void save();


    unsigned screenWidth() const;
    unsigned screenHeight() const;
    static const QString levels_path;

private:
    AppSettings();
    ~AppSettings();

 private:
    unsigned nScreenWidth{0};
    unsigned nScreenHeight{0};
};

#endif // APPSETTINGS_H
