#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("Игра Пазлы"));
    resize(500, 500);

    graphicsView = new QGraphicsView();
    graphicsView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QLayout* layout = this->layout();
    layout->addWidget(graphicsView);

    graphicsScene = new QGraphicsScene();
    graphicsScene->setSceneRect(0, 0, size().width(), size().height());
    graphicsView->setScene(graphicsScene);

    setCentralWidget(graphicsView);

    cutImage(QSize(Puzzle::maxX, Puzzle::maxY),
             "/home/sergey/Изображения/forest.jpg", graphicsScene);
}

MainWindow::~MainWindow()
{
}

void MainWindow::resizeEvent(QResizeEvent*)
{
    graphicsScene->setSceneRect(0, 0, size().width(), size().height());
}

Variables::ConnectorType MainWindow::reverse(Variables::ConnectorType pos)
{
    switch(pos)
    {
        case Variables::ConnectorType::NONE:
            return Variables::NONE;

        case Variables::ConnectorType::IN:
            return Variables::ConnectorType::OUT;

        case Variables::ConnectorType::OUT:
            return Variables::ConnectorType::IN;
    }
    return Variables::ConnectorType::NONE;
}

void MainWindow::cutImage(QSize fieldSize, QString fileName, QGraphicsScene* scene)
{
    qsrand(QTime::currentTime().msec());

    //Puzzle::sourceImage.load(fileName);
    Puzzle::sourceImage = Puzzle::sourceImage.scaled(
                Puzzle::cellSize*Puzzle::maxX, Puzzle::cellSize*Puzzle::maxY);

    Variables::ConnectorType storedWest;

    QVector<Variables::ConnectorType> prev(fieldSize.width(), Variables::NONE);
    for(int i = 0; i < fieldSize.height(); i++)
    {
        storedWest = Variables::NONE;
        for(int j = 0; j < fieldSize.width(); j++)
        {
            Variables::ConnectorType curr[4];
            curr[0] = reverse(prev[j]);
            curr[1] = qrand() % 2 ? Variables::IN : Variables::OUT;
            curr[2] = qrand() % 2 ? Variables::IN : Variables::OUT;
            curr[3] = reverse(storedWest);

            if(j == fieldSize.width() - 1) curr[1] = Variables::NONE;
            if(i == fieldSize.height() - 1) curr[2] = Variables::NONE;

            Puzzle* puzzle = new Puzzle(curr[0], curr[1], curr[2], curr[3],
                    j, i, this);
            puzzle->x = j;
            puzzle->y = i;
            scene->addItem(puzzle);
            Puzzle::puzzlesList.append(puzzle);

            storedWest = curr[1];
            prev[j] = curr[2];
        }
    }
}
