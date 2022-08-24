#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
  class Menu;
}
QT_END_NAMESPACE

class Menu : public QWidget {
  Q_OBJECT

  public:
  explicit Menu(QWidget *parent = nullptr);
  ~Menu() override;

  private:
  Ui::Menu *ui;
  signals:
  void exitButtonPushed();
  void startSingleGameButtonPushed();
  void startContestGameButtonPushed();
};