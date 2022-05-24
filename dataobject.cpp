#include <QDebug>
#include "dataobject.h"

DataObject::DataObject(QObject *parent)
    : QObject(parent) {
//    empty
}

DataObject::DataObject(const QString &item, const bool &today, const bool &completed, QObject *parent)
    : QObject(parent), _item(item), _today(today), _completed(completed) {
//	empty
}

QString DataObject::item() const {
    return _item;
}

void DataObject::setitem(const QString &item) {
    if ( item != _item ) {
        _item = item;
        emit itemChanged();
    }
}

bool DataObject::today() const {
    return _today;
}

void DataObject::setToday(const bool &today) {
    if (today != _today) {
        _today = today;
        emit todayChanged();
    }
}

bool DataObject::completed() const {
    return _completed;
}

void DataObject::setCompleted(const bool &completed) {
    if (completed != _completed) {
        _completed = completed;
        emit completedChanged();
    }
}
