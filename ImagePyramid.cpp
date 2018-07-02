#include "ImagePyramid.h"
#include "ui_ImagePyramid.h"

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
