#include "iodevice.h"
#include <QMetaEnum>

IODevice::IODevice(int id) : id(id) {
    deviceState = IO_DEVICE_HIGH_LOW::LOW;
}

IODevice::IODevice(int id, IODevice::IO_DEVICE_HIGH_LOW _deviceState) :
        id(id), deviceState(_deviceState) {
}

int IODevice::getId() const {
    return id;
}

QString IODevice::getDescription() const {
    return description;
}

void IODevice::setDescription(const QString &_description) {
    description = _description;
}

Arduino *IODevice::getArduino() {
    return arduino;
}

void IODevice::setArduino(Arduino *_arduino) {
    arduino = _arduino;
}

Action IODevice::getAction() const {
    return action;
}

void IODevice::setAction(const Action &_action) {
    action = _action;
}

IODeviceType IODevice::getIoDeviceType() const {
    return ioDeviceType;
}

void IODevice::setIoDeviceType(const IODeviceType &_ioDeviceType) {
    ioDeviceType = _ioDeviceType;
}

IODevice::IO_DEVICE_HIGH_LOW IODevice::getDeviceState() const {
    return deviceState;
}

void IODevice::setDeviceState(IODevice::IO_DEVICE_HIGH_LOW _deviceState) {
    deviceState = _deviceState;
}

void IODevice::setRecipe(const Recipe &_recipe) {
    recipe = _recipe;
}

Recipe IODevice::getRecipe() const {
    return recipe;
}
