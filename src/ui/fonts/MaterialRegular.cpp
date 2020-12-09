#include "MaterialRegular.h"
MaterialRegular::MaterialRegular()
{
    int id = QFontDatabase::addApplicationFont(fontLocation);
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    materialRegularFont = QFont(family);
}
QFont MaterialRegular::materialRegular()
{
    return materialRegularFont;
}

