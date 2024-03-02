#ifndef CREDIT_H
#define CREDIT_H

#include <QDialog>
extern "C" {
#include "calc_credit.h"
}

namespace Ui {
class credit;
}

class credit : public QDialog {
  Q_OBJECT

 public:
  explicit credit(QWidget *parent = nullptr);
  ~credit();

 signals:
  void secondWindow();  // Сигнал для второго окна на открытие

 private slots:
  void on_pushButton_clicked();

  void on_calculate_clicked();

 private:
  Ui::credit *ui;
};

#endif  // CREDIT_H
