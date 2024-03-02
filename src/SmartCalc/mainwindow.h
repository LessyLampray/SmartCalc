#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <credit.h>

#include <QMainWindow>

extern "C" {
#include "s21_SmartCalc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
 private slots:
  void digit_numbers();
  void math_operations();
  void functions();
  void delete_string();
  void dot_cond();
  void pushString();

  void on_pushButton_credit_cal_clicked();

 private:
  Ui::MainWindow *ui;
  double xBegin, xEnd, yEnd, yBegin, h, X;
  QVector<double> x, y;
  credit *sCredit;
};
#endif  // MAINWINDOW_H
