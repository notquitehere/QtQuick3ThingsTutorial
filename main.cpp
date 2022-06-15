#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include <QSqlDatabase>

#include "filtermodel.h"
#include "sqlmodel.h"
#include "dbhelper.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setAttribute(Qt::AA_DontUseNativeMenuBar, false);

    QSqlDatabase db = dbhelper::connectDB(false);

    SqlModel* data(new SqlModel(&app, db));
    data->setTable("todoTable");
    data->setEditStrategy(QSqlTableModel::OnManualSubmit);
    data->select();

    FilterModel filterModel;
    filterModel.setSourceModel(data);
    filterModel.setShowTodayOnly(true);


    QQmlApplicationEngine engine;

    QQmlContext *context = engine.rootContext();
    context->setContextProperty("dataModel", &filterModel);

    const QUrl url(u"qrc:/ThreeThings/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
