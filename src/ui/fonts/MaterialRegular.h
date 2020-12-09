#ifndef MATERIALREGULAR_H
#define MATERIALREGULAR_H

#include <QFont>
#include <QFontDatabase>

class MaterialRegular
{
public:
    MaterialRegular();
    QFont materialRegular();

private:
    QFont materialRegularFont;
    const QString fontLocation = ":/fonts/MaterialIcons-Regular.ttf";
};


#endif //MATERIALREGULAR_H
