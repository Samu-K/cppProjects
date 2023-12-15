#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <cmath>
#include <iostream>

using std::cout;
using std::endl;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::close);
    connect(ui->countButton, &QPushButton::clicked, this, &MainWindow::countPressed);
    connect(ui->weightLineEdit, &QLineEdit::textChanged, this, &MainWindow::weightChanged);
    connect(ui->heightLineEdit, &QLineEdit::textChanged, this, &MainWindow::heightChanged);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::countPressed()
{
    if (height_ == 0 || weight_ == 0) {
        ui->resultLabel->setText("Cannot count");
        return;
    }

    double ph = pow(height_/100,2);
    double bmi = weight_ / ph;

    ui->resultLabel->setText(QString::number(bmi));
    if (bmi < 18.5) {
        ui->infoTextBrowser->setText("You are underweight.");
    } else if (bmi > 25) {
        ui->infoTextBrowser->setText("You are overweight.");
    } else {
        ui->infoTextBrowser->setText("Your weight is normal.");
    }
}

void MainWindow::weightChanged(QString text)
{
    if (!text.isEmpty()) {
        weight_ = stod(text.toStdString());
    } else {
        weight_ = 0;
    }
}

void MainWindow::heightChanged(QString text)
{
    if(!text.isEmpty()) {
        height_ = stod(text.toStdString());
    } else {
        height_ = 0;
    }
}
