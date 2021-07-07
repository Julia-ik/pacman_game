#ifndef APPSETTINGS_H
#define APPSETTINGS_H
#include <QString>
#include <vector>
#include <QGLWidget>


class AppSettings
{
public:

    enum class TexturesId
    {
        WALL=0,
        PACMAN,
        GHOST,
        COOKIE,
        COIN,
        EMPTY,
        END
    };

    AppSettings(const AppSettings &)=delete;
    AppSettings & operator =(const AppSettings &)= delete;
    static AppSettings & instance();

    void load();
    void save();

    void setQGLWidget(QGLWidget &);

    QString  levelsPath() const;
    unsigned screenWidth() const;
    unsigned screenHeight() const;


    unsigned int textureID(TexturesId);

     const std::vector<std::pair<int, bool>> &availableLevels();



private:
   void load_textures();

private:
    AppSettings();
    ~AppSettings();

 private:
    unsigned nScreenWidth{0};
    unsigned nScreenHeight{0};

    QGLWidget *mpGLContext{nullptr};

    std::vector<std::pair<int, bool>> mAvailableLevels;
};

#endif // APPSETTINGS_H
