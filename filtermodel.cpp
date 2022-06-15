#include "sqlmodel.h"
#include "filtermodel.h"

FilterModel::FilterModel(QObject *parent) : QSortFilterProxyModel(parent) {
    // empty
}

bool FilterModel::showTodayOnly() {
    return _showTodayOnly;
}

void FilterModel::setShowTodayOnly(const bool &today) {
    _showTodayOnly = today;
    if (today) {
        this->setFilterRole(SqlModel::TodayRole);
        this->setFilterFixedString("true");
    } else {
        this->setFilterFixedString("");
    }
}
