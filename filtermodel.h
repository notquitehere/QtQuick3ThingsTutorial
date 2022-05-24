#ifndef FILTERMODEL_H
#define FILTERMODEL_H

#include <QSortFilterProxyModel>

class FilterModel : public QSortFilterProxyModel {
    Q_OBJECT

public:
    FilterModel(QObject *parent = nullptr);
    bool showTodayOnly();

    Q_INVOKABLE void setShowTodayOnly(const bool &today);

private:
    bool _showTodayOnly;
};

#endif
