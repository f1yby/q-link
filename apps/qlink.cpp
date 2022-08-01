#include <QApplication>
#include <QLocale>
#include <QPushButton>
#include <QTranslator>
#include <qpushbutton.h>

#include "widgets/main_window.h"
#include "widgets/menu.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QTranslator translator;
  const QStringList uiLanguages = QLocale::system().uiLanguages();
  for (const QString &locale: uiLanguages) {
    const QString baseName = "helloworld_" + QLocale(locale).name();
    if (translator.load(":/i18n/" + baseName)) {
      QApplication::installTranslator(&translator);
      break;
    }
  }
  MainWindow m;
  m.show();

  return QApplication::exec();
}
