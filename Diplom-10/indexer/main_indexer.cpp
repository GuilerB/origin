#include <QCoreApplication>
#include <QSettings>
#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <windows.h>
#include "database.h"
#include "indexer.h"

int main(int argc, char *argv[])
{
    SetConsoleOutputCP(CP_UTF8);
    QCoreApplication app(argc, argv);

    QString configPath = QCoreApplication::applicationDirPath() + "/config.ini";

    DB &db = DB::instance();
    if (!db.initializeFromConfig(configPath)) {
        qCritical() << "Failed to initialize database.";
        return 1;
    }

    QString pathsStr;
    QString extensionsStr = "txt";

    QFile configFile(configPath);
    if (configFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&configFile);
        bool inIndexerSection = false;
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            if (line == "[Indexer]") {
                inIndexerSection = true;
                continue;
            }
            if (line.startsWith("[") && line.endsWith("]")) {
                inIndexerSection = false;
                continue;
            }
            if (inIndexerSection && line.startsWith("paths=")) {
                pathsStr = line.mid(6).trimmed();
            }
            if (inIndexerSection && line.startsWith("extensions=")) {
                extensionsStr = line.mid(11).trimmed();
            }
        }
        configFile.close();
    }

    if (pathsStr.isEmpty()) {
        qCritical() << "No paths in config.ini [Indexer] paths=...";
        return 1;
    }

    QStringList paths = pathsStr.split(",", Qt::SkipEmptyParts);
    QStringList extensions = extensionsStr.split(",", Qt::SkipEmptyParts);
    for (auto &p : paths) p = p.trimmed();
    for (auto &e : extensions) e = e.trimmed().toLower();

    QString baseDir = QCoreApplication::applicationDirPath();
    for (auto &p : paths) {
        QFileInfo fi(p);
        if (fi.isRelative()) {
            p = QDir::cleanPath(QDir(baseDir).absoluteFilePath(p));
        }
    }

    qDebug() << "paths:" << paths;
    qDebug() << "extensions:" << extensions;

    Indexer fileIndexer;
    for (const auto &p : paths) fileIndexer.addIndexPath(p);
    fileIndexer.setFileExtensions(extensions);
    fileIndexer.run();

    return 0;
}
