#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H
#include <vector>
#include <QGLWidget>

class pacman_game : public QGLWidget
{
public:
    enum class eState//(текущее состояние)
    {
        MENU,
        NEW_GAME,
        SELECT_LEVEL,
        CONTINUE_GAME,
        BEST_SCORE,
        EXIT
    };
    enum class eMenu//(состояние в момент игры)
    {
        BEGIN = -1,
        PLAY,
        SELECT_LEVEL,
        BEST_SCORE,
        START,
        EXIT,
        END
    };
public:
    pacman_game();
    pacman_game(QWidget *parent);

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL()              override;
    void keyReleaseEvent(QKeyEvent *) override;

 private:
    void proccesing();
    void draw();

    void draw_menu();
    void draw_menu_new_game();
    void draw_menu_select_level();
    void draw_best_score();
    void draw_menu_continue_game();

    void key_released_menu(int);
    void key_released_new_game(int);
    void key_released_menu_select_lvl(int);
    void key_released_best_score(int);
    void key_released_continue_game(int);


private:
    int mSelectLevelIndex;

    eState mState{eState::MENU};
    eMenu mCurrentMenu{eMenu::PLAY};

    std::vector<std::pair<eMenu, std::string>> mvMenu;
    int menuStateToInt(const pacman_game::eMenu &aMenu);

};

#endif // PACMAN_GAME_H
