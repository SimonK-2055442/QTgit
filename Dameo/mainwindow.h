#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QPushButton>
#include "dameobordview.h"
#include "chaturajibordview.h"


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void DameoButtonPressed();
    void ChaturajiButtonPressed();

private:
    DameoBordView *m_dameoBord{};
    ChaturajiBordView *m_chaturajiBord{};
    QGraphicsView *m_view{};
};

#endif // MAINWINDOW_H
