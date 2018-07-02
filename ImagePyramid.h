#ifndef IMAGEPYRAMID_H
#define IMAGEPYRAMID_H
#include <QMainWindow>
#include "ImagesController.h"
namespace Ui {
class ImagePyramid;
}

class ImagePyramid : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImagePyramid(QWidget *parent = 0);
    ~ImagePyramid();

private slots:
    void on_actionLoad_triggered();

    void on_imagesCB_currentIndexChanged(int index);

    void on_layersCB_currentIndexChanged(int index);

    void on_deleteImageB_clicked();

private:
    ImagesController imageController;
    Ui::ImagePyramid *ui;
};

#endif // IMAGEPYRAMID_H
