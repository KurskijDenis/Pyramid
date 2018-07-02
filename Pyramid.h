#ifndef PYRAMID_H
#define PYRAMID_H
#include <QImage>
#include <QComboBox>
#include <QLabel>
#include <vector>
#include <string>
#include <QDebug>
#include <memory>

struct ImageS {
    QImage image;

    ImageS() {}
    ImageS(QImage _image): image(_image) {}
    ImageS(const ImageS& source) { init(source); }
    ImageS(ImageS&& source) { init(source); }
    ImageS& operator=(const ImageS& source) {  init(source); return *this; }
    ImageS(const ImageS&& source) { init(source); }
    ImageS* copy() const { return new ImageS(*this); }
    QSize size() const { return image.size(); }
    int getDiagonalLength() const { return sqrt(pow(size().width(), 2) + pow(size().height(), 2)); }
    void init(const ImageS& source) { image = source.image; }
};

class Pyramid
{
public:
    Pyramid(const Pyramid& source) { init(source); }
    Pyramid(Pyramid&& source) { init(source); }
    Pyramid& operator=(const Pyramid& source);
    Pyramid(QString file);

    void showLayer(int layer, QLabel* imageContainer, QLabel* sizeL);
    void set(QLabel* imageContainer, QComboBox* layerCB);
    int getDiagonalLength() const { return pyramid[0]->getDiagonalLength(); }
    inline int pyramidSize() const { return pyramid.size(); }
    inline bool isValid() const { return valid; }
private:
    void formNewImage(QImage& newImage, const QImage& oldImage);
    void init(const Pyramid& source);
    void formPyramid(size_t countLayers);
    bool valid = true;
    bool block = false;
    std::vector<std::shared_ptr<ImageS>> pyramid;
};

#endif // PYRAMID_H
