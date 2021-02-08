#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QLayout>
#include <QSize>
#include <QTime>
#include "gamelogic.h"
#include "puzzle.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QGraphicsView* graphicsView;
    QGraphicsScene* graphicsScene;

public:
    static bool isWin;

    MainWindow(QWidget *parent = nullptr);
    void resizeEvent(QResizeEvent*);

    void cutImage(QSize fieldSize, QString fileName, QGraphicsScene*);
    Variables::ConnectorType reverse(Variables::ConnectorType);
    ~MainWindow();
};
#endif // MAINWINDOW_H
