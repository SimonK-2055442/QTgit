#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "bordview.h"
#include "dameospel.h"
#include "chaturajibordview.h"
#include "chaturajispel.h"
#include <QMainWindow>
#include <QGraphicsView>
#include <QMenuBar>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
private slots:
    void DameoButtonPressed();
    void ChaturajiButtonPressed();
private:
    BordView *dameoBord{};
    ChaturajiBordView* chaturajiBord{};
    QGraphicsView *view{};
    void menuToevoegen();
};
#endif // MAINWINDOW_H
