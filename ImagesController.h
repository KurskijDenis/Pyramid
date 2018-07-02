#ifndef IMAGESCONTROLLER_H
#define IMAGESCONTROLLER_H
#include "Pyramid.h"

class ImagesController
{
public:
    ImagesController() {}
    void addImage(QString path, QComboBox* imagesCB, QLabel* imageConstainer, QLabel* sizeL, QComboBox* layersCB);
    void changeLayer(int layer, QLabel* imageConstainer, QLabel* sizeL);
    void changeCurrentImage(int index, QLabel* imageConstainer, QLabel* sizeL, QComboBox* layersCB);
    void removeImage(QComboBox* imagesCB, QLabel* imageConstainer, QLabel* sizeL, QComboBox* layersCB);
private:
    bool block = false;
    int currentImage = -1;
    std::vector<std::shared_ptr<Pyramid>> images;
};

#endif // IMAGESCONTROLLER_H
