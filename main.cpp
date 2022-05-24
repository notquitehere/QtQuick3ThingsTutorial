#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "datamodel.h"
#include "dataobject.h"
#include "filtermodel.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setAttribute(Qt::AA_DontUseNativeMenuBar, false);

    DataModel* dataList = new DataModel({
        new DataObject("Do 30 minutes of exercise", true, false),
        new DataObject("Write blog post", true, false),
        new DataObject("Bake a cake", true, false),
        new DataObject("Get the car cleaned", false, false),
        new DataObject("Learn how to knit", false, false),
    });

    FilterModel filterModel;
    filterModel.setSourceModel(dataList);
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
