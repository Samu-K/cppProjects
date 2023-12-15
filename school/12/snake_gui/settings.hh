#ifndef SETTINGS_HH
#define SETTINGS_HH

#include <QDialog>

struct stData {
    int width, height, seed;
};

namespace Ui {
class settings;
}

class settings : public QDialog
{
    Q_OBJECT

public:
    explicit settings(QWidget *parent = nullptr);
    ~settings();

signals:
    void accepted();
    void submitted(stData st);

private slots:
    void okClicked();

    // capture value input
    void heightChanged(int val);
    void widthChanged(int val);
    void seedChanged(int val);

private:
    Ui::settings *ui;

    stData st_;
};

#endif // SETTINGS_HH
