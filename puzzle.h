#ifndef PUZZLE_H
#define PUZZLE_H

#include <QPaintEvent>
#include <QPainter>
#include <QGraphicsObject>
#include <QBitmap>
#include <QList>
#include <QCursor>
#include <QMessageBox>
#include "mainwindow.h"
#include "variables.h"

class Puzzle : public QGraphicsPixmapItem
{
private:
    QPainter maskPainter;
    static QList<Puzzle*> connected;
    QPointF diff;
    Puzzle* neighbours[4];
    QMainWindow* parent;
    bool isMoved = false;
    bool isCheckRun = false;
    bool isMove = false;

    Variables::ConnectorType connectors[4];

    QPixmap createMask();

    void linkTwoPuzzle(Puzzle*, int);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);

    void checkPuzzles(int);
    void checkAllPuzzles();
    void checkWin();
    void move(int, int);
public:
    static int maxX, maxY;
    static int cellSize;
    int x, y;
    static QList<Puzzle*> puzzlesList;
    static QImage sourceImage;

    Puzzle(Variables::ConnectorType, Variables::ConnectorType,
           Variables::ConnectorType, Variables::ConnectorType,
           int, int, QMainWindow*);
    void movePuzzle(QPoint, int, int, QPointF);

    QGraphicsPixmapItem* getPixmapItem();

public slots:
    void mouseRelease();
};

#endif // PUZZLE_H
