#include <QApplication>
#include <QLocale>
#include <QPushButton>
#include <QTranslator>
#include <qpushbutton.h>
#include <spdlog/spdlog.h>
#include "widgets/main_window.h"
#include "widgets/menu.h"

using namespace spdlog;

int main(int argc, char *argv[]) {
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
