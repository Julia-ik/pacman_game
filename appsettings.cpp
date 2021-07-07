#include "appsettings.h"
#include <QDirIterator>
#include <vector>
#include <algorithm>
#include <array>



static const QString level_Path = "./../../another_pacman/pacman2/levels/";//директория из кот будут уровни
static const QString pics_path = "./../../another_pacman/pacman2/pics/";

static std::array<unsigned int, (int)AppSettings::TexturesId::END> localTextures;

AppSettings::AppSettings()
{

}
AppSettings::~AppSettings()
{
    save();
}

AppSettings &AppSettings::instance()
{
    static AppSettings res;
    return res;
}

void AppSettings::load()
{
    mAvailableLevels.clear();
    QDirIterator it(level_Path);//путь к директориям
    while(it.hasNext())//пока есть следующий элемент в директории
    {
        it.next();//переходим к следующему
        QFileInfo info(it.fileInfo());//информация о файле
        if(info.completeSuffix()=="lvl")
            mAvailableLevels.push_back({info.baseName().toInt(),true});//файл получает имя в циферках и доступность
    }

    sort (mAvailableLevels.begin(), mAvailableLevels.end(),
    [](const auto &a,const auto &b)->bool
    {
        return a.first < b.first;
    });

    load_textures();
}
void AppSettings::save()
{

}

 QString AppSettings::levelsPath() const
{
     return level_Path;
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

const std::vector<std::pair<int, bool>> &AppSettings::availableLevels()
{
   return mAvailableLevels;
}

void AppSettings::setQGLWidget(QGLWidget &aQGlWidget)
{
    mpGLContext=&aQGlWidget;
}

void AppSettings::load_textures()
{
    glEnable(GL_TEXTURE_2D);//загрузка текстур

    auto load_texture = [this](QString aPath)-> unsigned int
    {
        QImage PngImg;
        PngImg.load(aPath);
        return mpGLContext->bindTexture(PngImg);
    };

    localTextures[(int)TexturesId::GHOST] = load_texture(pics_path + "ghost.png");
    localTextures[(int)TexturesId::PACMAN] = load_texture(pics_path + "pacman.png");
    localTextures[(int)TexturesId::COIN] = load_texture(pics_path + "coin.png");
    localTextures[(int)TexturesId::COOKIE] = load_texture(pics_path + "cookie.png");
    localTextures[(int)TexturesId::WALL] = load_texture(pics_path + "wall.png");
    localTextures[(int)TexturesId::EMPTY] = load_texture(pics_path + "transparent.png");

    glDisable(GL_TEXTURE_2D);
}

unsigned int AppSettings::textureID(TexturesId aId)
{
    return localTextures[(int)aId];
}
