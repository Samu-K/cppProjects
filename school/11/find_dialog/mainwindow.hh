#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onFileLineChanged(QString text);
    void onKeyLineChanged(QString text);
    void matchChanged(bool stat);
    void findPressed();
    void updateText();

signals:
    void searchComplete();

private:
    Ui::MainWindow *ui;

    // file check
    std::string fp_;
    std::string keyword_;

    // text for display
    std::string fs_;

    // matching case
    bool match_ = false;

};
#endif // MAINWINDOW_HH
