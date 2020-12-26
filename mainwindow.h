#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QList>
#include <QMainWindow>
#include <string>
#include <iostream>
#include <QString>
#include <ctype.h>
#include <QMessageBox>
#include <math.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onButton();
private:
    Ui::MainWindow *ui;
    int status;
    int num1,num2;
    std::string theoperator2;
private slots:
    void doStatus4();
signals:
    void Status4();

};
#endif // MAINWINDOW_H
