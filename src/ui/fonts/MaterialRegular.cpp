#include "MaterialRegular.h"
MaterialRegular::MaterialRegular()
{
    QFontIcon::addFont(fontLocation);
}
QIcon MaterialRegular::icon(const QChar &code, const QColor &baseColor)
{
    return QFontIcon::icon(code, baseColor, familyName);
}
QIcon MaterialRegular::boltIcon(const QColor &baseColor)
{
    return QFontIcon::icon(boltIconCode, baseColor, familyName);
}
QIcon MaterialRegular::visibilityIcon(const QColor &baseColor)
{
    return QFontIcon::icon(visibilityIconCode, baseColor, familyName);
}
QIcon MaterialRegular::visibilityOffIcon(const QColor &baseColor)
{
    return QFontIcon::icon(visibilityOffIconCode, baseColor, familyName);
}
QIcon MaterialRegular::powerIcon(const QColor &baseColor)
{
    return QFontIcon::icon(powerIconCode, baseColor, familyName);
}
QIcon MaterialRegular::powerOffIcon(const QColor &baseColor)
{
    return QFontIcon::icon(powerOffIconCode, baseColor, familyName);
}
QIcon MaterialRegular::highlightOffIcon(const QColor &baseColor)
{
    return QFontIcon::icon(highlightOff, baseColor, familyName);
}
QIcon MaterialRegular::checkCircleOutlineIcon(const QColor &baseColor)
{
    return QFontIcon::icon(checkCircleOutline, baseColor, familyName);
}

