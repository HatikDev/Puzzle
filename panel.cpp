#include "panel.h"

Panel::Panel()
{
    width = 200;
    height = 300;
    setMinimumSize(QSize(200, 200));
}

void Panel::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    cellSize = width<height ? width/8 : height/8;

    if (imagePath.isEmpty())
    {
        p.setBrush(Qt::gray);
        p.drawRect(offsetX, offsetY, imageWidth*cellSize, imageHeight*cellSize);
    } else
    {
        QImage image(imagePath);
        p.drawImage(offsetX, offsetY, image.scaled(imageWidth*cellSize, imageHeight*cellSize)); //const QSize(imageWidth, imageHeight))
    }

    for (int i = 0; i <= 8; i++)
    {
        p.drawLine(offsetX+i*cellSize, offsetY, offsetX+i*cellSize, offsetY+8*cellSize);
        p.drawLine(offsetX+0, offsetY+i*cellSize, offsetX+8*cellSize, offsetY+i*cellSize);
    }
}

void Panel::mousePressEvent (QMouseEvent*)
{
    QPoint point = QCursor::pos() - mapToGlobal(QPoint(0, 0));

    int x = (point.x()-offsetX) / cellSize + 1;
    int y = (point.y()-offsetY) / cellSize + 1;

    if (x < 2 || y < 2 || x > 8 || y > 8) return;

    imageWidth = x;
    imageHeight = y;

    repaint();
}

void Panel::mouseMoveEvent(QMouseEvent*)
{
    QPoint point = QCursor::pos() - mapToGlobal(QPoint(0, 0));

    int x = (point.x()-offsetX) / cellSize + 1;
    int y = (point.y()-offsetY) / cellSize + 1;

    if (x < 2 || y < 2 || x > 8 || y > 8) return;

    imageWidth = x;
    imageHeight = y;

    repaint();
}
