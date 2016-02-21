#include "splash.h"

Splash::Splash(const QPixmap &pixmap)
{
    QSplashScreen::setPixmap(pixmap);
}

Splash::~Splash()
{
}

void Splash::drawContents(QPainter *painter)
{
    painter->setPen(this->color);
    painter->drawText(this->rect, this->alignment, this->message);
}

void Splash::showStatusMessage(const QString &message, const QColor &color)
{
    this->message = message;
    this->color = color;
    this->showMessage(this->message, this->alignment, this->color);
}

void Splash::setMessageRect(QRect rect, int alignment)
{
    this->rect = rect;
    this->alignment = alignment;
}
