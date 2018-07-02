#ifndef IMAGEPYRAMID_H
#define IMAGEPYRAMID_H

#include <QMainWindow>

namespace Ui {
class ImagePyramid;
}

class ImagePyramid : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImagePyramid(QWidget *parent = 0);
    ~ImagePyramid();

private:
    Ui::ImagePyramid *ui;
};

#endif // IMAGEPYRAMID_H
