#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "gradecounter.hh"
#include <QSpinBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->countPushButton, &QPushButton::clicked, this, &MainWindow::countPressed);

    ui->spinBoxN->setRange(0,780);
    ui->spinBoxG->setRange(0,120);
    ui->spinBoxP->setRange(0,250);
    ui->spinBoxE->setRange(1,5);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::countPressed()
{

    unsigned int grade = count_final_grade(n_,g_,p_,e_);
    QString disptext = "Total grade: " + QString::number(grade);

    ui->textBrowser->setText(disptext);
}


void MainWindow::on_spinBoxN_valueChanged(int arg1)
{
    n_ = arg1;
}


void MainWindow::on_spinBoxG_valueChanged(int arg1)
{
    g_ = arg1;
}


void MainWindow::on_spinBoxP_valueChanged(int arg1)
{
    p_ = arg1;
}


void MainWindow::on_spinBoxE_valueChanged(int arg1)
{
   e_ = arg1;
}

