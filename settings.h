#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include <QFileDialog>
#include "panel.h"
#include "mainwindow.h"
#include "puzzle.h"

class Settings : public QWidget
{
    Q_OBJECT

    QLabel* imageLabel;
    QLabel* imageSizeLabel;
    QLineEdit* imageLineEdit;
    QPushButton* chooseButton;
    Panel* panel;

    QPushButton* okButton;
    QPushButton* cancelButton;

public:
    Settings();

    void start();
    void resizeEvent(QResizeEvent*);

public slots:

    void chooseImage();
    void startGame();
};

#endif // SETTINGS_H
