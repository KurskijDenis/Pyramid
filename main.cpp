#include "ImagePyramid.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImagePyramid w;
    w.show();

    return a.exec();
}
