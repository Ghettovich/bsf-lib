#include "statecode.h"
#include <QMetaEnum>

StateCode::StateCode(int id)
    : id(id)
{
}

int StateCode::getId() const
{
    return id;
}

const QString &StateCode::getMessage() const
{
    return message;
}
void StateCode::setMessage(const QString &_message)
{
    message = _message;
}

const QString &StateCode::getStatusMessage() const
{
    return statusMessage;
}

void StateCode::setStatusMessage(const QString &_statusMessage)
{
    statusMessage = _statusMessage;
}
