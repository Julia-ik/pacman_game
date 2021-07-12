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
    static void save();

    void setQGLWidget(QGLWidget &);

    [[nodiscard]] QString levelsPath() const;
    [[nodiscard]]static unsigned screenWidth();
    [[nodiscard]]static unsigned screenHeight();


    static unsigned int textureID(TexturesId);

     const std::vector<std::pair<int, bool>> &availableLevels();



private:
   void load_textures();

private:
    AppSettings();
    ~AppSettings();

 private:
    const QString level_Path = "./../../another_pacman/pacman2/levels/";
    const QString pics_path = "./../../another_pacman/pacman2/pics/";

    QGLWidget *mpGLContext{nullptr};

    std::vector<std::pair<int, bool>> mAvailableLevels;
};

#endif // APPSETTINGS_H
