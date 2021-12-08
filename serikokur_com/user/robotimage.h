#ifndef ROBOTIMAGE_H
#define ROBOTIMAGE_H

#include "BaseClass/containerwiget.h"
#include <Wt/WPaintedWidget.h>



class RobotImage : public Wt::WPaintedWidget
{
public:
    RobotImage();

    inline int getRandom(int begin = 0 , int end = 127 ) const
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist(begin,end);
        return dist(mt);
    }

    void refreshCaptcha();

    const std::string &correctValue() const;

    const std::string &currentColor() const;

    Signal<std::string> &colorClicked();

protected:
  void paintEvent(Wt::WPaintDevice *paintDevice);


private:

  QString mLetterContainer{"qwertyuopasdfghjklizxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890"};

  std::string mCorrectValue = "valueYok";
  std::string mCurrentColor = "renkYok";



  void rePaintText(WPainter *painter, Wt::StandardColor color, const std::string &value);


  Signal<std::string> _colorClicked;

public:
  std::string generateText(){

      QString value = mLetterContainer.at(this->getRandom(0,mLetterContainer.count()-1));
      value += mLetterContainer.at(this->getRandom(0,mLetterContainer.count()-1));
      value += mLetterContainer.at(this->getRandom(0,mLetterContainer.count()-1));
      value += mLetterContainer.at(this->getRandom(0,mLetterContainer.count()-1));

      return value.toStdString();
  }

};

#endif // ROBOTIMAGE_H
