#include "puzzle.h"

QPixmap Puzzle::createMask()
{
    QImage imgMask(QSize(cellSize*1.4, cellSize*1.4), QImage::Format_ARGB32);
    imgMask.fill(Qt::GlobalColor::transparent);

    maskPainter.begin(&imgMask);
    maskPainter.setBrush(QBrush(Qt::black));

    QPainterPath painterPath;

    painterPath.moveTo(cellSize*0.2, cellSize*0.2);
    if (connectors[0] == Variables::NONE)
    {
        painterPath.lineTo(cellSize*1.2, cellSize*0.2);
    } else
    {
        painterPath.lineTo(cellSize*0.5, cellSize*0.2);
        if (connectors[0] == Variables::OUT) painterPath.arcTo(
                    cellSize*0.5, 0, cellSize*0.4, cellSize*0.4, 180, -180);
        else painterPath.arcTo(
                    cellSize*0.5, 0, cellSize*0.4, cellSize*0.4, 180, 180);
        painterPath.lineTo(cellSize*1.2, cellSize*0.2);
    }

    if (connectors[1] == Variables::NONE)
    {
        painterPath.lineTo(cellSize*1.2, cellSize*1.2);
    } else
    {
        painterPath.lineTo(cellSize*1.2, cellSize*0.5);
        if (connectors[1] == Variables::OUT) painterPath.arcTo(
                    cellSize, cellSize*0.5, cellSize*0.4,
                    cellSize*0.4, 90, -180);
        else painterPath.arcTo(
                    cellSize, cellSize*0.5, cellSize*0.4,
                    cellSize*0.4, 90, 180);
        painterPath.lineTo(cellSize*1.2, cellSize*1.2);
    }

    if (connectors[2] == Variables::NONE)
    {
        painterPath.lineTo(cellSize*0.2, cellSize*1.2);
    } else
    {
        painterPath.lineTo(cellSize*0.9, cellSize*1.2);
        if (connectors[2] == Variables::OUT) painterPath.arcTo(
                    cellSize*0.5, cellSize, cellSize*0.4,
                    cellSize*0.4, 0, -180);
        else painterPath.arcTo(
                    cellSize*0.5, cellSize, cellSize*0.4,
                    cellSize*0.4, 0, 180);
        painterPath.lineTo(cellSize*0.2, cellSize*1.2);
    }

    if (connectors[3] == Variables::NONE)
    {
        painterPath.lineTo(cellSize*0.2, cellSize*0.2);
    } else
    {
        painterPath.lineTo(cellSize*0.2, cellSize*0.9);
        if (connectors[3] == Variables::OUT) painterPath.arcTo(
                    0, cellSize*0.5, cellSize*0.4,
                    cellSize*0.4, 270, -180);
        else painterPath.arcTo(
                    0, cellSize*0.5, cellSize*0.4,
                    cellSize*0.4, 270, 180);
        painterPath.lineTo(cellSize*0.2, cellSize*0.2);
    }

    maskPainter.drawPath(painterPath);
    maskPainter.end();

    QPixmap mask;
    mask.convertFromImage(imgMask);

    return mask;
}

Puzzle::Puzzle(Variables::ConnectorType top, Variables::ConnectorType right,
               Variables::ConnectorType bottom, Variables::ConnectorType left,
               int x, int y, QMainWindow* parent)
{
    connectors[0] = top;
    connectors[1] = right;
    connectors[2] = bottom;
    connectors[3] = left;
    this->parent = parent;

    neighbours[0] = nullptr;
    neighbours[1] = nullptr;
    neighbours[2] = nullptr;
    neighbours[3] = nullptr;

    QPixmap mask = createMask();

    QPixmap pieceImage = QPixmap::fromImage(Puzzle::sourceImage.copy(
            QRect((x-0.2)*cellSize, (y-0.2)*cellSize, cellSize*1.4, cellSize*1.4)));

    pieceImage.setMask(mask.mask());
    setPixmap(pieceImage);

    setX(qrand() % 300);
    setY(qrand() % 300);

    sourceImage = sourceImage.scaled(cellSize*maxX, cellSize*maxY);
}

void Puzzle::linkTwoPuzzle(Puzzle* puzzle, int direction)
{
    neighbours[direction] = puzzle;
    puzzle->neighbours[(direction+2) % 4] = this;
    if (!connected.contains(this)) connected.push_back(this);
    if (!connected.contains(puzzle)) connected.push_back(puzzle);
}

void Puzzle::move(int x, int y)
{
    isMove = true;
    setPos(x, y);

    if (neighbours[0] != nullptr && !neighbours[0]->isMove)
        neighbours[0]->move(x, y-cellSize);
    if (neighbours[1] != nullptr && !neighbours[1]->isMove)
        neighbours[1]->move(x+cellSize, y);
    if (neighbours[2] != nullptr && !neighbours[2]->isMove)
        neighbours[2]->move(x, y+cellSize);
    if (neighbours[3] != nullptr && !neighbours[3]->isMove)
        neighbours[3]->move(x-cellSize, y);

    isMove = false;
}

void Puzzle::checkPuzzles(int direction)
{
    int id = y*maxX+x;

    if (direction == 0)
    {
        Puzzle* up = puzzlesList.at(id-maxX);

        if (abs((up->pos()-pos()).x()) < 5 && abs((up->pos()-pos()).y()) < cellSize+5) {
            linkTwoPuzzle(up, 0);
            move(up->pos().x(), up->pos().y()+cellSize);
        }
    } else if (direction == 1)
    {
        Puzzle* right = puzzlesList.at(id+1);

        if (abs((right->pos()-pos()).x()) < cellSize+5 && abs((right->pos()-pos()).y()) < 5) {
            linkTwoPuzzle(right, 1);
            move(right->pos().x()-cellSize, right->pos().y());
        }
    } else if (direction == 2)
    {
        Puzzle* bottom = puzzlesList.at(id+maxX);

        if (abs((bottom->pos()-pos()).x()) < 5 && abs((bottom->pos()-pos()).y()) < cellSize+5) {
            linkTwoPuzzle(bottom, 2);
            move(bottom->pos().x(), bottom->pos().y()-cellSize);
        }
    } else if (direction == 3)
    {
        Puzzle* left = puzzlesList.at(id-1);

        if (abs((left->pos()-pos()).x()) < cellSize+5 && abs((left->pos()-pos()).y()) < 5) {
            linkTwoPuzzle(left, 3);
            move(left->pos().x()+cellSize, left->pos().y());
        }
    }
}

void Puzzle::checkAllPuzzles()
{
    isCheckRun = true;

    if (y*maxX+x >= maxX) checkPuzzles(0);
    if (x % maxX != maxX-1) checkPuzzles(1);
    if (y*maxX+x < (maxY-1)*maxX) checkPuzzles(2);
    if (x % maxX != 0) checkPuzzles(3);

    if (neighbours[0] != nullptr && !neighbours[0]->isCheckRun)
        neighbours[0]->checkAllPuzzles();
    if (neighbours[1] != nullptr && !neighbours[1]->isCheckRun)
        neighbours[1]->checkAllPuzzles();
    if (neighbours[2] != nullptr && !neighbours[2]->isCheckRun)
        neighbours[2]->checkAllPuzzles();
    if (neighbours[3] != nullptr && !neighbours[3]->isCheckRun)
        neighbours[3]->checkAllPuzzles();

    isCheckRun = false;
}

void Puzzle::checkWin()
{
    if (connected.size() == maxX*maxY && !MainWindow::isWin)
    {
        QMessageBox::information(nullptr, "Победа!", "<h3>Победа!</h3>");
        MainWindow::isWin = true;
    }
}

void Puzzle::mouseReleaseEvent(QGraphicsSceneMouseEvent*)
{
    checkAllPuzzles();

    checkWin();
}

void Puzzle::mousePressEvent(QGraphicsSceneMouseEvent*)
{
    diff = QCursor::pos() - parent->mapToGlobal(QPoint(0, 0)) - pos();
}

void Puzzle::mouseMoveEvent(QGraphicsSceneMouseEvent*)
{
    movePuzzle(QCursor::pos(), 0, 0, diff);
}

void Puzzle::movePuzzle(QPoint pos, int x, int y, QPointF diff)
{
    setPos(pos-parent->mapToGlobal(QPoint(0, 0))-diff+QPoint(x*cellSize, y*cellSize));

    isMoved = true;

    if (neighbours[0] != nullptr && !neighbours[0]->isMoved)
        neighbours[0]->movePuzzle(pos, x, y-1, diff);
    if (neighbours[1] != nullptr && !neighbours[1]->isMoved)
        neighbours[1]->movePuzzle(pos, x+1, y, diff);
    if (neighbours[2] != nullptr && !neighbours[2]->isMoved)
        neighbours[2]->movePuzzle(pos, x, y+1, diff);
    if (neighbours[3] != nullptr && !neighbours[3]->isMoved)
        neighbours[3]->movePuzzle(pos, x-1, y, diff);

    isMoved = false;
}
