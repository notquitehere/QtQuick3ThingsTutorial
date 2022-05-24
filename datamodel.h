#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QAbstractListModel>
#include "dataobject.h"
#include <QDebug>

class DataModel : public QAbstractListModel {
    Q_OBJECT

public:
    enum DataObejctRoles {
        ItemNameRole = Qt::UserRole + 1,
        TodayRole,
        CompletedRole,
        DeleteRole,
    };


    DataModel(QObject *parent = 0);
    DataModel(DataObject* dataObject, QObject *parent = 0);
    DataModel(QList<DataObject*> dataObjects, QObject *parent = 0);
    ~DataModel();

    Q_INVOKABLE void add();
    void addData(DataObject* dataObject);
    void addData(QList <DataObject*> dataObjects);

    bool removeData(const QModelIndex &index);

    bool setData(const QModelIndex &index, const QVariant &value, int role);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<DataObject*> _dataObjects;
};

#endif
