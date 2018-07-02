#include "Pyramid.h"
#include <QMessageBox>
Pyramid::Pyramid(QString file)
{
    QImage image(file);
    if (image.isNull())
    {
        QMessageBox msgBox;
        msgBox.setText("Can't load image");
        msgBox.exec();
        valid = false;
    } else {
        auto log2 = log(2);
        auto log5 = log(5);
        auto logw = log(image.width());
        auto logh = log(image.height());
        int countLayers = (int) std::max(1.0, (std::min(logw, logh) - log5) / log2);
        pyramid.resize(countLayers);
        pyramid[0].reset(new ImageS(image));
      //  formPyramid(countLayers);
    }
}
Pyramid& Pyramid::operator=(const Pyramid& source)
{
    init(source);
    return *this;
}
void Pyramid::showLayer(int layer, QLabel* imageContainer, QLabel* sizeL)
{
    if (layer >= (int)pyramid.size() || block) return;
    if (pyramid[layer] == nullptr) formLayer(layer);
    auto pixmap = QPixmap::fromImage(pyramid[layer]->image);
    auto size = pixmap.size();
    pixmap = pixmap.scaled(pyramid[0]->size());
    imageContainer->setPixmap(pixmap);
    sizeL->setText(QString::fromStdString("Size: " + std::to_string(size.width()) + "x" + std::to_string(size.height())));
}
void Pyramid::set(QLabel* imageContainer, QComboBox * layerCB)
{
    auto size = pyramid[0]->size();
    imageContainer->setMinimumWidth(size.width());
    imageContainer->setMinimumHeight(size.height());
    block = true;
    layerCB->clear();
    for (size_t i = 0; i < pyramid.size(); i++)
        layerCB->addItem(QString::fromStdString(std::to_string(i)));
    block = false;
    layerCB->setCurrentIndex(0);
}
void Pyramid::init(const Pyramid& source)
{
    pyramid.resize(source.pyramid.size());
    for (size_t i = 0; i < pyramid.size(); i++)
        if (source.pyramid[i] != nullptr)
            pyramid[i].reset(source.pyramid[i]->copy());
        else
            pyramid[i] = nullptr;
}
void Pyramid::formLayer(size_t layer)
{
    size_t existingLayer = 1;
    for (size_t i = layer; i > 0; i--)
        if(pyramid[i - 1] != nullptr)
        {
            existingLayer = i;
            break;
        }
    QImage prevLayer = pyramid[existingLayer - 1]->image;
    for (size_t l = existingLayer; l < layer + 1; l++)
    {
        QImage image(prevLayer.width() / 2, prevLayer.height() / 2, QImage::Format_ARGB32 );
        formNewImage(image, prevLayer);
        prevLayer = image;
    }
    pyramid[layer].reset(new ImageS(prevLayer));
}
void Pyramid::formNewImage(QImage& newImage, const QImage& oldImage)
{
    double a = 0.4;
    double w[5] = {0.25 - a / 2, 0.25, a, 0.25, 0.25 - a / 2};
    auto calculateIndex = [] (int count, int index) { return index >= count ? ( 2 * (count - 1) - index) : index; };

    for (int i = 0; i < newImage.width(); ++i )
        for (int j = 0; j < newImage.height(); ++j )
        {
            double colorr = 0, colorg = 0, colorb = 0, colora = 0;
            for (int p = -2; p <= 2 ; p++)
            {
                int ip =  calculateIndex(oldImage.width(), abs(2 * i + p));
                for (int q = -2; q <= 2 ; q++)
                {
                    int iq =  calculateIndex(oldImage.height(), abs(2 * j + q));
                    auto pixelColor = oldImage.pixelColor(ip, iq);
                        colorr += w[p + 2] * w[q + 2] * pixelColor.red();
                        colorg += w[p + 2] * w[q + 2] * pixelColor.green();
                        colorb += w[p + 2] * w[q + 2] * pixelColor.blue();
                        colora += w[p + 2] * w[q + 2] * pixelColor.alpha();
                }
            }
            newImage.setPixel(i, j, qRgba(colorr, colorg, colorb, colora));
        }
}
void Pyramid::formPyramid(size_t countLayers)
{
    for (size_t l = 1; l < countLayers; l++)
    {
        const QImage& prevLayer = pyramid[l - 1]->image;
        QImage image(prevLayer.width() / 2, prevLayer.height() / 2, QImage::Format_ARGB32 );
        formNewImage(image, prevLayer);
        pyramid[l].reset(new ImageS(image));
    }
}
