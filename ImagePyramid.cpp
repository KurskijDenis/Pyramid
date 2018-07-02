#include "ImagePyramid.h"
#include "ui_ImagePyramid.h"
#include <QFileDialog>

ImagePyramid::ImagePyramid(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImagePyramid)
{
    ui->setupUi(this);
}

ImagePyramid::~ImagePyramid()
{
    delete ui;
}

void ImagePyramid::on_actionLoad_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("*.jpg *.png"));
    if(!fileName.isEmpty() && !fileName.isNull())
    {
          QPixmap pixmap(fileName);
          ui->imageContainer->setPixmap(pixmap);
          ui->imageContainer->setMinimumWidth(pixmap.width());
          ui->imageContainer->setMinimumHeight(pixmap.height());
    }
}
