#ifndef SPLASH_H
#define SPLASH_H

#include <QWidget>
#include <QSplashScreen>
#include <QPainter>

class Splash : public QSplashScreen
{
public:
    explicit Splash(const QPixmap& pixmap);
    ~Splash();
    virtual void drawContents(QPainter *painter);
    void showStatusMessage(const QString &message, const QColor &color = Qt::black);
    void setMessageRect(QRect rect, int alignment = Qt::AlignLeft);

private:
    QString message;
    int alignment;
    QColor color;
    QRect rect;
};

#endif // SPLASH_H
