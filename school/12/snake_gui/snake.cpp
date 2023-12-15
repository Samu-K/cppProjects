#include "snake.hh"
#include "ui_snake.h"
#include "settings.hh"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>

#include <iostream>

using std::endl;
using std::cout;


Snake::Snake(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Snake)
{
    ui->setupUi(this);

    // first window for settings
    settings *sts = new settings();

    // connections for settings
    connect(sts, &settings::submitted, this, &Snake::onSubmitted);

    // show setting dialog
    sts->show();
    fieldScene_ = new QGraphicsScene(this);
    ui->gameView->setScene(fieldScene_);
}

Snake::~Snake()
{
    delete ui;
}

void Snake::run_game() {
     GameBoard field = GameBoard(st_.seed,st_.width,st_.height);

     show();
     drawField();

}

void Snake::onSubmitted(stData st)
{
    st_.width = st.width;
    st_.height = st.height;
    st_.seed = st.seed;

    run_game();

}

Point Snake::getSnakeHead()
{
    return gm_.getSnakeHead();
}

void Snake::drawField()
{
    QPen pen = QPen(Qt::black);
    for (int x=0; x<=100; x+=10) {
        fieldScene_->addLine(x,0,x,100,pen);
    }

    for (int y=0; y<=100; y+=5) {
        fieldScene_->addLine(0,y,100,y,pen);
    }
    ui->gameView->fitInView(fieldScene_->itemsBoundingRect());
}

void Snake::drawSnake()
{
    Point snakeHead = getSnakeHead();
    std::pair<int,int> cords = snakeHead.getCords();
    cout << cords.first;
    cout << endl << cords.second << endl;
}
