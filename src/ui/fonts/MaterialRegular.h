#ifndef MATERIALREGULAR_H
#define MATERIALREGULAR_H

#include <QFont>
#include <QColor>
#include <QPalette>
#include <fonts/QFontIcon.h>
#include <QFontDatabase>

class MaterialRegular
{
public:
    MaterialRegular();
    QIcon icon(const QChar &code, const QColor &baseColor);
    QIcon boltIcon(const QColor &baseColor);
    QIcon visibilityIcon(const QColor &baseColor = Qt::lightGray);
    QIcon visibilityOffIcon(const QColor &baseColor = Qt::darkGray);
    QIcon powerIcon(const QColor &baseColor = Qt::lightGray);
    QIcon powerOffIcon(const QColor &baseColor = Qt::lightGray);

private:
    const QString familyName = "Material Design";
    const QString fontLocation = ":/fonts/MaterialIcons-Regular.ttf";

    const QChar boltIconCode = 0xE932;
    const QChar visibilityIconCode = 0xe8f4;
    const QChar visibilityOffIconCode = 0xe8f5;
    const QChar powerIconCode = 0xe63c;
    const QChar powerOffIconCode = 0xe646;
};


#endif //MATERIALREGULAR_H
