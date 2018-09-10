#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QFile>
#include <QCoreApplication>
#include <QTextStream>
#include <QTimer>
#include <QtMath>




namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int getfileNum(QString str);
    QTimer *invTimer;
    QTimer *serTimer;
    QTimer *cheTimer;
    QTimer *strTimer;

    void SendMessage(QString server, char* data);



private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

public slots:
    void serslot();
    void invslot();
    void cheslot();
    void strslot();

public slots:



private:
    Ui::MainWindow *ui;




private:
    int nport;
    int ninverter;
    int MessageType;
};




#endif // MAINWINDOW_H
