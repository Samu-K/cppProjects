#include "settings.hh"
#include "ui_settings.h"

#include <iostream>
using std::cout;
using std::endl;

settings::settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settings)
{

    ui->setupUi(this);

    // connnections
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &settings::okClicked);
    connect(ui->heightBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &settings::heightChanged);
    connect(ui->widthBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &settings::widthChanged);
    connect(ui->seedBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &settings::seedChanged);

    // defaults
    ui->heightBox->setValue(5);
    ui->widthBox->setValue(6);
    ui->seedBox->setValue(1);
}

settings::~settings()
{
    delete ui;
}

void settings::okClicked() {
    emit submitted(st_);
}

void settings::heightChanged(int val)
{
    st_.height = val;
}

void settings::widthChanged(int val)
{
    st_.width = val;
}

void settings::seedChanged(int val)
{
    st_.seed = val;
}
