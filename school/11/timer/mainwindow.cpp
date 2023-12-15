#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::close);
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::startPressed);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::stopPressed);
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::resetPressed);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::update_display);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startPressed()
{
    timer->start(1000);
}

void MainWindow::stopPressed()
{
    int rem = timer->remainingTime();
    timer->stop();
    timer->setInterval(rem);
}

void MainWindow::resetPressed()
{
    timer->stop();
    secs=0;
    mins=0;
    ui->lcdNumberMin->display(0);
    ui->lcdNumberSec->display(0);
}

void MainWindow::update_display() {
    secs += 1;
    if (secs >= 60) {
        mins += 1;
        secs = 0;
    }

    ui->lcdNumberMin->display(mins);
    ui->lcdNumberSec->display(secs);
}


