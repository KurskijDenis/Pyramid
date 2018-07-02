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
        imageController.addImage(fileName, ui->imagesCB, ui->imageContainer, ui->sizeL, ui->layersCB);
}

void ImagePyramid::on_imagesCB_currentIndexChanged(int index)
{
    imageController.changeCurrentImage(index, ui->imageContainer, ui->sizeL, ui->layersCB);
}

void ImagePyramid::on_layersCB_currentIndexChanged(int index)
{
    imageController.changeLayer(index, ui->imageContainer, ui->sizeL);
}

void ImagePyramid::on_deleteImageB_clicked()
{
    imageController.removeImage(ui->imagesCB, ui->imageContainer, ui->sizeL, ui->layersCB);
}
