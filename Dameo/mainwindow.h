#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dameobordview.h"
#include "dameospel.h"
#include "chaturajibordview.h"
#include "chaturajispel.h"
#include <QMainWindow>
#include <QGraphicsView>
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
    DameoBordView *dameoBord{};
    ChaturajiBordView* chaturajiBord{};
    QGraphicsView *view{};
};
#endif // MAINWINDOW_H
