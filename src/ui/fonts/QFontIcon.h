
#ifndef QFONTICON_H
#define QFONTICON_H

#include <QObject>
#include <QPainter>
#include <QIconEngine>
#include <QApplication>
#include <QtCore>
#include <QPalette>

class QFontIcon;
class QFontIconEngine;
#define FIcon(code) QFontIcon::icon(code)

class QFontIconEngine : public QIconEngine
{
public:
    QFontIconEngine();
    ~QFontIconEngine();
    virtual void paint(QPainter * painter, const QRect& rect, QIcon::Mode mode, QIcon::State state)Q_DECL_OVERRIDE ;
    virtual QPixmap pixmap(const QSize &size, QIcon::Mode mode, QIcon::State state)Q_DECL_OVERRIDE;
    void setFontFamily(const QString& family);
    // define icon code using QChar or implicit using ushort ...
    void setLetter(const QChar& letter);
    // You can set a base color. I don't advice. Keep system color
    void setBaseColor(const QColor& baseColor);
    virtual QIconEngine* clone() const;

private:
    QString mFontFamily;
    QChar mLetter;
    QColor mBaseColor;
};

class QFontIcon : public QObject
{
Q_OBJECT

public:
    // add Font. By default, the first one is used
    static bool addFont(const QString& filename);
    static QFontIcon * instance();
    // main methods. Return icons from code
    static QIcon icon(const QChar& code, const QColor& baseColor = QColor(),const QString& family = QString());
    // return added fonts
    const QStringList& families() const;

protected:
    void addFamily(const QString& family);


private:
    explicit QFontIcon(QObject *parent = 0);
    ~QFontIcon();
    static QFontIcon * mInstance;
    QStringList mfamilies;


};

#endif //QFONTICON_H
