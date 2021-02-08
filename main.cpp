#include <QApplication>
#include <QVBoxLayout>
#include <QImage>
#include "puzzle.h"
#include "settings.h"
#include "mainwindow.h"

int Puzzle::maxX = 4;
int Puzzle::maxY = 3;
int Puzzle::cellSize = 100;
QImage Puzzle::sourceImage = QImage("");
QList<Puzzle*> Puzzle::puzzlesList = QList<Puzzle*>();
QList<Puzzle*> Puzzle::connected = QList<Puzzle*>();
bool MainWindow::isWin = false;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Settings* settings = new Settings();
    settings->start();
    return a.exec();
}
