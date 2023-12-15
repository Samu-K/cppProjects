#ifndef SNAKE_HH
#define SNAKE_HH

#include <QGraphicsScene>
#include "settings.hh"
#include "game.hh"
#include <QMainWindow>

namespace Ui {
class Snake;
}

class Snake : public QMainWindow
{
    Q_OBJECT

public:
    explicit Snake(QWidget *parent = nullptr);
    ~Snake();

    void run_game();
    void drawSnake();

private slots:
    void onSubmitted(stData st);

private:
    // funcs
    Point getSnakeHead();
    void drawField();

    // vars
    Ui::Snake *ui;
    stData st_;
    QGraphicsScene* fieldScene_;

    Game gm_ = Game();
};

#endif // SNAKE_HH
