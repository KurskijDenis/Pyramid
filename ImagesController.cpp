#include "ImagesController.h"

void ImagesController::changeLayer(int layer, QLabel* imageContainer, QLabel* sizeL)
{
    if (currentImage == -1) return;
    images[currentImage]->showLayer(layer, imageContainer, sizeL);
}
void ImagesController::changeCurrentImage(int index, QLabel* imageContainer, QLabel* sizeL, QComboBox* layersCB)
{
    if (index >= (int)images.size() || blocked) return;
    currentImage = index;
    images[index]->set(imageContainer, layersCB, sizeL);
}
void ImagesController::removeImage(QComboBox* imagesCB, QLabel* imageContainer, QLabel* sizeL, QComboBox* layersCB)
{
    if (currentImage > -1) {
        blocked = true;
        images.erase(images.begin() + currentImage);
        imagesCB->removeItem(currentImage);
        blocked = false;
        if (images.size() > 0)
            changeCurrentImage(0, imageContainer, sizeL, layersCB);
        else {
            currentImage = -1;
            imageContainer->clear();
            layersCB->clear();
            sizeL->setText("Size: 0x0");
        }
    }
}
void ImagesController::addImage(QString path, QComboBox* imagesCB, QLabel* imageContainer, QLabel* sizeL, QComboBox* layersCB)
{
    std::shared_ptr<Pyramid> image(new Pyramid(path));
    if (!image->isValid()) return;
    auto fileName = path.mid(path.lastIndexOf("/") + 1);
    blocked = true;
    size_t i = 0;
    for (; i < images.size(); i++)
    {
        if (images[i]->getDiagonalLength() > image->getDiagonalLength())
        {
              images.insert(images.begin() + i, image);
              imagesCB->insertItem(i, fileName);
              break;
        }
    }
    if (i == images.size())
    {
        i = images.size();
        images.push_back(image);
        imagesCB->addItem(fileName);
    }
    imagesCB->setCurrentIndex(i);
    blocked = false;
    changeCurrentImage(i, imageContainer, sizeL, layersCB);
}
