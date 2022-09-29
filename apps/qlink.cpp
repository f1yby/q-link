#include "widget/main_window.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <spdlog/spdlog.h>

using namespace spdlog;

int main(int argc, char *argv[])
{
    info("Enter QApp");
    QApplication q(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale: uiLanguages) {
        const QString baseName = "helloworld_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            QApplication::installTranslator(&translator);
            break;
        }
    }
    info("Enter MainWindow");
    MainWindow m;
    m.show();

    return QApplication::exec();
}
