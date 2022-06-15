#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFile>


namespace dbhelper {
    QSqlDatabase connectDB(bool test = false);
    void removeDB();
}
