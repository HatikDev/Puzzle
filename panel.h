#ifndef PANEL_H
#define PANEL_H

#include <QObject>
#include <QWidget>
#include <QPainter>

class Panel : public QWidget
{
    Q_OBJECT

public:
    int width;
    int height;
    int imageWidth = 8;
    int imageHeight = 8;
    int cellSize = 0;
    int offsetX;
    int offsetY;
    QString imagePath;

    Panel();

    void paintEvent(QPaintEvent *);

protected:
    virtual void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);

public slots:

};

#endif // PANEL_H
