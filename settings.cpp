#include "settings.h"

Settings::Settings()
{}

void Settings::chooseImage()
{
    QString path = QFileDialog::getOpenFileName(nullptr,
            tr("Открыть изображение"),
            "", "Images (*.jpg *.png *.gif *.jpeg *.bmp *.tiff)");

    qDebug() << path;

    while(path.isEmpty())
    {
        path = QFileDialog::getOpenFileName(nullptr,
                tr("Открыть изображение"),
                "", "Images (*.jpg *.png *.gif *.jpeg *.bmp *.tiff)");
    }

    imageLineEdit->setText(path);
    panel->imagePath = path;

    panel->repaint();
}

void Settings::start()
{
    resize(400, 300);
    setWindowTitle(tr("Настройки"));

    imageLabel = new QLabel(tr("Файл изображения: "));
    imageLineEdit = new QLineEdit();
    chooseButton = new QPushButton(tr("Обзор..."));

    imageSizeLabel = new QLabel(tr("Размер поля: "));
    panel = new Panel();

    okButton = new QPushButton(tr("Ok"));
    cancelButton = new QPushButton(tr("Отмена"));

    QObject::connect(chooseButton, SIGNAL(clicked()), this, SLOT(chooseImage()));
    QObject::connect(okButton, SIGNAL(clicked()), this, SLOT(startGame()));
    QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout* hLayout1 = new QHBoxLayout();
    hLayout1->addWidget(imageLabel);
    hLayout1->addWidget(imageLineEdit);
    hLayout1->addWidget(chooseButton);

    QHBoxLayout* hLayout = new QHBoxLayout();
    hLayout->addWidget(imageSizeLabel);
    hLayout->addWidget(panel);

    QHBoxLayout* hLayout2 = new QHBoxLayout();
    hLayout2->addWidget(okButton);
    hLayout2->addWidget(cancelButton);

    QVBoxLayout* vLayout = new QVBoxLayout();
    vLayout->addLayout(hLayout1);
    vLayout->addLayout(hLayout);
    vLayout->addLayout(hLayout2);

    setLayout(vLayout);

    show();
}

void Settings::startGame()
{
    if (!panel->imagePath.isEmpty())
    {
        Puzzle::maxX = panel->imageWidth;
        Puzzle::maxY = panel->imageHeight;
        Puzzle::sourceImage = QImage(panel->imagePath);

        MainWindow* w = new MainWindow;
        w->show();
        close();
    } else QMessageBox::information(nullptr, tr("Ошибка"), tr("Не выбрано изображения"));
}

void Settings::resizeEvent(QResizeEvent*)
{
    int width = panel->size().width();
    int height = panel->size().height();

    width = width<height ? width : height;

    panel->width = width;
    panel->height = width;

    imageSizeLabel->setMaximumWidth(size().width()/3);

    int panelSize = width > height ? height : width;
    panel->offsetX = (width-panelSize)/2;
    panel->offsetY = (height-panelSize)/2;
}
