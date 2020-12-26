#include "action.h"

Action::Action(int id)
    : id(id) {}

int Action::getId() {
  return id;
}

QString Action::getCode() const {
  return code;
}

void Action::setCode(const QString &_code) {
  code = _code;
}

QString Action::getUrl() const {
  return url;
}

void Action::setUrl(const QString &_url) {
  url = _url;
}

QString Action::getDescription() const {
  return description;
}

void Action::setDescription(const QString &_desc) {
  description = _desc;
}
