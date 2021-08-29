#include "MaterialRegular.h"

MaterialRegular::MaterialRegular() {
  QFontIcon::addFont(fontLocation);
}

QIcon MaterialRegular::icon(const QChar &code, const QColor &baseColor) {
  return QFontIcon::icon(code, baseColor, familyName);
}

QIcon MaterialRegular::boltIcon(const QColor &baseColor) {
  return QFontIcon::icon(boltIconCode, baseColor, familyName);
}

QIcon MaterialRegular::visibilityIcon(const QColor &baseColor) {
  return QFontIcon::icon(visibilityIconCode, baseColor, familyName);
}

QIcon MaterialRegular::visibilityOffIcon(const QColor &baseColor) {
  return QFontIcon::icon(visibilityOffIconCode, baseColor, familyName);
}

QIcon MaterialRegular::powerIcon(const QColor &baseColor) {
  return QFontIcon::icon(powerIconCode, baseColor, familyName);
}

QIcon MaterialRegular::powerOffIcon(const QColor &baseColor) {
  return QFontIcon::icon(powerOffIconCode, baseColor, familyName);
}

QIcon MaterialRegular::highlightOffIcon(const QColor &baseColor) {
  return QFontIcon::icon(highlightOff, baseColor, familyName);
}

QIcon MaterialRegular::checkCircleOutlineIcon(const QColor &baseColor) {
  return QFontIcon::icon(checkCircleOutline, baseColor, familyName);
}

QIcon MaterialRegular::arrowCircleDownIcon(const QColor &baseColor) {
  return QFontIcon::icon(arrowCircleDown, baseColor, familyName);
}

QIcon MaterialRegular::arrowCircleUpIcon(const QColor &baseColor) {
  return QFontIcon::icon(arrowCircleUp, baseColor, familyName);
}

QIcon MaterialRegular::updateIcon(const QColor &baseColor) {
  return QFontIcon::icon(update, baseColor, familyName);
}

QIcon MaterialRegular::updateDisabledIcon(const QColor &baseColor) {
  return QFontIcon::icon(updateDisabled, baseColor, familyName);
}

QIcon MaterialRegular::syncIcon(const QColor &baseColor) {
  return QFontIcon::icon(sync, baseColor, familyName);
}

QIcon MaterialRegular::syncProblemIcon(const QColor &baseColor) {
  return QFontIcon::icon(syncProblem, baseColor, familyName);
}

QIcon MaterialRegular::clearIcon(const QColor &baseColor) {
  return QFontIcon::icon(clear, baseColor, familyName);
}
