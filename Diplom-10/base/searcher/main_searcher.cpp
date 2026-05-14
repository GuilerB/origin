#include <QApplication>
#include <QMessageBox>
#include "database.h"
#include "searcherwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QString configPath = QApplication::applicationDirPath() + "/config.ini";

    DB &db = DB::instance();
    if (!db.initializeFromConfig(configPath)) {
        QMessageBox::critical(nullptr, "Ошибка",
                              "Не удалось подключиться к БД.\nПроверьте config.ini");
        return 1;
    }

    SearcherWindow searchWindow;
    searchWindow.show();
    return app.exec();
}