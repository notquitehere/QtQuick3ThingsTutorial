#include "datamodel.h"
#include <QDebug>

DataModel::DataModel(QObject *parent) : QAbstractListModel(parent) {
    // empty
}

DataModel::DataModel(DataObject* dataObject, QObject *parent)
    : QAbstractListModel(parent), _dataObjects({dataObject}) {
    // empty
}

DataModel::DataModel(QList<DataObject*> dataObjects, QObject *parent)
    : QAbstractListModel(parent), _dataObjects(dataObjects) {
    // empty
}

DataModel::~DataModel() {
    // empty
}

void DataModel::add() {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    _dataObjects << new DataObject("", false, false);
    endInsertRows();
}

void DataModel::addData( DataObject* dataObject ) {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    _dataObjects << dataObject;
    endInsertRows();
}

void DataModel::addData(QList <DataObject*> dataObjects ) {
    int endAt = rowCount() + dataObjects.count() - 1;

    beginInsertRows(QModelIndex(), rowCount(), endAt);
    for (int i = rowCount(); i < endAt; i++ ) {
        _dataObjects << dataObjects[i];
    }
    endInsertRows();
}

bool DataModel::removeData(const QModelIndex &index) {
    if (index.isValid()) {
        beginRemoveRows(QModelIndex(), index.row(), index.row());
        delete _dataObjects.takeAt(index.row());
        endRemoveRows();
        return true;
    }
    return false;
}

bool DataModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    bool updated = false;

    if (index.isValid() && roleNames().contains(role)) {
        DataObject* d = _dataObjects[index.row()];
        if ( role == ItemNameRole && d->item() != value.toString()) {
            d->setitem(value.toString());
            updated = true;
        } else if ( role == TodayRole && d->today() != value.toBool()) {
            d->setToday(value.toBool());
            updated = true;
        } else if ( role == CompletedRole && d->completed() != value.toBool()) {
            d->setCompleted(value.toBool());
            updated = true;
        } else if ( role == DeleteRole ) {
            updated = removeData(index);
        }
    }

    if (updated) {emit dataChanged(index, index, { role });}
    return updated;
}

int DataModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return _dataObjects.count();
}

QVariant DataModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= _dataObjects.count()) {
        return QVariant();
    }

    DataObject* dataObject = _dataObjects[index.row()];
    if (role == ItemNameRole) {
        return dataObject->item();
    } else if (role == TodayRole) {
        return dataObject->today();
    } else if (role == CompletedRole) {
        return dataObject->completed();
    }
    return QVariant();
}

QHash<int, QByteArray> DataModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[ItemNameRole] = "itemName";
    roles[TodayRole] = "today";
    roles[CompletedRole] = "completed";
    roles[DeleteRole] = "remove";
    return roles;
}
