#include "datamodel.h"
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
        this->setFilterRole(DataModel::TodayRole);
        this->setFilterFixedString("true");
    } else {
        this->setFilterFixedString("");
    }
}
