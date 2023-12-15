#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using std::cout;
using std::endl;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->fileLineEdit, &QLineEdit::textChanged, this, &MainWindow::onFileLineChanged);
    connect(ui->keyLineEdit, &QLineEdit::textChanged, this, &MainWindow::onKeyLineChanged);
    connect(ui->findPushButton, &QPushButton::clicked, this, &MainWindow::findPressed);
    connect(this, &MainWindow::searchComplete, this, &MainWindow::updateText);
    connect(ui->matchCheckBox, &QCheckBox::clicked, this, &MainWindow::matchChanged);
    connect(ui->closePushButton, &QPushButton::clicked, this, &MainWindow::close);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onFileLineChanged(QString text) {
    fp_ = text.toStdString();
}

void MainWindow::onKeyLineChanged(QString text)
{
    keyword_ = text.toStdString();
}

void MainWindow::matchChanged(bool stat)
{
    match_ = stat;
}

void MainWindow::findPressed()
{
    std::ifstream file;
    std::string line;

    // reset status
    fs_ = "";

    // open file for reading
    file.open(fp_);

    if (file.is_open()) {
        if(keyword_.empty()) {
            fs_ = "file found";
        } else {

            // read line by line
            while(getline(file,line)) {
                if (!match_) {
                    std::transform(line.begin(),line.end(),line.begin(),::toupper);
                    std::transform(keyword_.begin(),keyword_.end(),keyword_.begin(),::toupper);
                }

                if (line.find(keyword_) != std::string::npos) {
                    // if we find word set text, status and break
                    fs_ = "Word found";
                    break;
                }
            }
        }
    } else {
        fs_ = "File not found";
    }

    // if nothing changed the value
    // then file was opened, keyword given
    // but keyword was not found
    if (fs_ == "") {
        fs_ = "Word not found";
    }
    file.close();
    emit searchComplete();
}

void MainWindow::updateText()
{
    ui->textBrowser->setText(QString::fromStdString(fs_));
}

