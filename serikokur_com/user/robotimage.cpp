#include "robotimage.h"
#include <QImage>


RobotImage::RobotImage()
{
    resize(1024,50);
    setMaximumSize(1024,50);

    setPositionScheme(PositionScheme::Relative);

    decorationStyle().setBorder(WBorder(BorderStyle::Solid,BorderWidth::Thin,WColor(0,0,0)));
    decorationStyle().setCursor(Cursor::PointingHand);


    this->refreshCaptcha();

    this->clicked().connect([=](){
        this->refreshCaptcha();
    });


}

void RobotImage::refreshCaptcha()
{
    QImage img;

    if( img.load("docroot/abstract.jpg") ){
        const int width = 1024;
        const int height = 50;

        int px = this->getRandom(5,img.width()-width-200);
        int py = this->getRandom(5,img.height()-100);
        QImage newImage = img.copy(px,py,width,height);

        auto urlImage = QString("abstractTest%1%2.jpg").arg(px).arg(py);

        if( newImage.save("docroot/"+urlImage) ){
            setAttributeValue(Style::style,Style::background::url(urlImage.toStdString())/*+Style::background::size::cover*/);
        }


    }

    update();

}

void RobotImage::paintEvent(WPaintDevice *paintDevice)
{



    Wt::WPainter painter(paintDevice);
    WFont font(FontFamily::Monospace);
    font.setSize(24);
    font.setWeight(FontWeight::Bold);
    painter.setFont(font);

    bool currentValueGenerated = false;

    auto _value = this->getRandom();
    auto __mCorrectValue = this->generateText();
    this->rePaintText(&painter,StandardColor::Red,__mCorrectValue);
    if( _value%3 == 0 && !currentValueGenerated ){
        mCorrectValue = __mCorrectValue;
        currentValueGenerated = true;
        mCurrentColor = "Kırmızı";
        _colorClicked.emit(mCurrentColor);

    }


    _value = this->getRandom();
    __mCorrectValue = this->generateText();
    this->rePaintText(&painter,StandardColor::Blue,__mCorrectValue);
    if( _value%3 == 0 && !currentValueGenerated ){
        mCorrectValue = __mCorrectValue;
        currentValueGenerated = true;
        mCurrentColor = "Mavi";
        _colorClicked.emit(mCurrentColor);

    }

    _value = this->getRandom();
    __mCorrectValue = this->generateText();
    this->rePaintText(&painter,StandardColor::Green,__mCorrectValue);
    if( _value%3 == 0 && !currentValueGenerated ){
        mCorrectValue = __mCorrectValue;
        currentValueGenerated = true;
        mCurrentColor = "Yeşil";
        _colorClicked.emit(mCurrentColor);

    }



    _value = this->getRandom();
    __mCorrectValue = this->generateText();
    this->rePaintText(&painter,StandardColor::Black,__mCorrectValue);
    if( _value%3 == 0 && !currentValueGenerated ){
        mCorrectValue = __mCorrectValue;
        currentValueGenerated = true;
        mCurrentColor = "Siyah";
        _colorClicked.emit(mCurrentColor);

    }


    if( !currentValueGenerated ){
        mCorrectValue = __mCorrectValue;
        currentValueGenerated = true;
        mCurrentColor = "Siyah";
        _colorClicked.emit(mCurrentColor);
    }






//    this->rePaintText(&painter,StandardColor::Black,"value");

}

const std::string &RobotImage::currentColor() const
{
    return mCurrentColor;
}

Signal<std::string> &RobotImage::colorClicked()
{
    return _colorClicked;
}

void RobotImage::rePaintText(WPainter *painter, StandardColor color, const std::string &value)
{
    painter->setPen(WPen(WColor(color)));

    const int width = 1024;
    const int height = 50;

    int px = this->getRandom(5,500);
    int py = this->getRandom(5,20);


    painter->drawText(px,py,width,height,AlignmentFlag::Left,WString("{1}").arg(value));
}



const std::string &RobotImage::correctValue() const
{
    return mCorrectValue;
}
