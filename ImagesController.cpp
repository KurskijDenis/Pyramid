#include "ImagesController.h"

void ImagesController::changeLayer(int layer, QLabel* imageContainer, QLabel* sizeL)
{
    if (currentImage == -1) return;
    images[currentImage]->showLayer(layer, imageContainer, sizeL);
}
void ImagesController::changeCurrentImage(int index, QLabel* imageContainer, QLabel* sizeL, QComboBox* layersCB)
{
    if (index >= (int)images.size() || block) return;
    currentImage = index;
    images[index]->set(imageContainer, layersCB);
    images[index]->showLayer(0, imageContainer, sizeL);
}
void ImagesController::removeImage(QComboBox* imagesCB, QLabel* imageContainer, QLabel* sizeL, QComboBox* layersCB)
{
    if (currentImage > -1) {
        block = true;
        images.erase(images.begin() + currentImage);
        imagesCB->removeItem(currentImage);
        block = false;
        if (images.size() > 0)
        {
            currentImage = 0;
            changeCurrentImage(0, imageContainer, sizeL, layersCB);
        } else {
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
    auto ind = path.lastIndexOf("/");
    auto fileName = path.mid(ind + 1);
    block = true;
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
    block = false;
    changeCurrentImage(i, imageContainer, sizeL, layersCB);
}
