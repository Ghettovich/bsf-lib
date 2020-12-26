#include "QFontIcon.h"
#include <QDebug>
#include <QFontDatabase>
QFontIcon *QFontIcon::mInstance = Q_NULLPTR;

bool QFontIcon::addFont(const QString &filename) {
  int id = QFontDatabase::addApplicationFont(filename);

  if (id == -1) {
    qWarning() << "Cannot load font";
    return false;
  }

  QString family = QFontDatabase::applicationFontFamilies(id).first();
  instance()->addFamily(family);
  return true;
}

QFontIcon *QFontIcon::instance() {
  if (!mInstance)
    mInstance = new QFontIcon;

  return mInstance;
}

QIcon QFontIcon::icon(const QChar &code, const QColor &baseColor, const QString &family) {
  if (instance()->families().isEmpty()) {
    qWarning() << Q_FUNC_INFO << "No font family installed";
    return QIcon();
  }

  QString useFamily = family;
  if (useFamily.isEmpty())
    useFamily = instance()->families().first();

  auto engine = new QFontIconEngine;
  engine->setFontFamily(useFamily);
  engine->setLetter(code);
  engine->setBaseColor(baseColor);
  return QIcon(engine);

}

const QStringList &QFontIcon::families() const {
  return mfamilies;
}

void QFontIcon::addFamily(const QString &family) {
  mfamilies.append(family);
}

QFontIcon::QFontIcon(QObject *parent)
    : QObject(parent) {

}

QFontIcon::~QFontIcon() {

}

//=======================================================================================================


QFontIconEngine::QFontIconEngine()
    : QIconEngine() {

}

QFontIconEngine::~QFontIconEngine() {
}

void QFontIconEngine::paint(QPainter *painter, const QRect &rect, QIcon::Mode mode, QIcon::State state) {
  Q_UNUSED(state);
  QFont font = QFont(mFontFamily);
  int drawSize = qRound(rect.height() * 0.8);
  font.setPixelSize(drawSize);

  QColor penColor;
  if (!mBaseColor.isValid())
    penColor = QApplication::palette("QWidget").color(QPalette::Normal, QPalette::ButtonText);
  else
    penColor = mBaseColor;

  if (mode == QIcon::Disabled)
    penColor = QApplication::palette("QWidget").color(QPalette::Disabled, QPalette::ButtonText);

  if (mode == QIcon::Selected)
    penColor = QApplication::palette("QWidget").color(QPalette::Active, QPalette::ButtonText);

  painter->save();
  painter->setPen(QPen(penColor));
  painter->setFont(font);
  painter->drawText(rect, Qt::AlignCenter | Qt::AlignVCenter, mLetter);

  painter->restore();
}

QPixmap QFontIconEngine::pixmap(const QSize &size, QIcon::Mode mode, QIcon::State state) {
  QPixmap pix(size);
  pix.fill(Qt::transparent);

  QPainter painter(&pix);
  paint(&painter, QRect(QPoint(0, 0), size), mode, state);
  return pix;

}

void QFontIconEngine::setFontFamily(const QString &family) {
  mFontFamily = family;
}

void QFontIconEngine::setLetter(const QChar &letter) {
  mLetter = letter;
}

void QFontIconEngine::setBaseColor(const QColor &baseColor) {
  mBaseColor = baseColor;
}

QIconEngine *QFontIconEngine::clone() const {
  auto engine = new QFontIconEngine;
  engine->setFontFamily(mFontFamily);
  engine->setBaseColor(mBaseColor);
  return engine;
}