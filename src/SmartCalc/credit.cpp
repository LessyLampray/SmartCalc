#include "credit.h"

#include "ui_credit.h"

credit::credit(QWidget *parent) : QDialog(parent), ui(new Ui::credit) {
  ui->setupUi(this);
}

credit::~credit() { delete ui; }

void credit::on_pushButton_clicked() {
  this->close();
  emit secondWindow();
}

void credit::on_calculate_clicked() {
  std::string str_sum = ui->am_numb->text().toStdString();
  char *sum = &str_sum[0];
  std::string str_month = ui->term_2->text().toStdString();
  char *month = &str_month[0];
  std::string str_procent = ui->rate_num->text().toStdString();
  char *procent = &str_procent[0];

  double overpayment = 0;
  double totalSum = 0;
  double sums = atof(sum);
  double months = atoi(month);
  double procents = (atof(procent) / 100) / 12;
  QString new_label = "";

  if (ui->differentiated->isChecked()) {
    double d = sums / months;
    double S = 0.0;
    int n = months;
    int numberMonth = n;

    for (int i = 0; i < n; i++) {
      S = differentiatedСredit(&sums, &months, &procents, &d);
      months--;
      QString num1 = QString::number(S, 'f', 2);
      QString qw = QString::number(numberMonth);
      totalSum = totalSum + S;
      new_label = new_label + num1 + " | " + qw + "month" + '\n';
      numberMonth--;
    }

    overpayment = totalSum - sums;
    QString num2 = QString::number(overpayment, 'f', 2);
    QString num3 = QString::number(totalSum, 'f', 2);

    ui->ii->setText(new_label);
    ui->over_l->setText(num2);
    ui->total_l->setText(num3);
  }
  if (ui->annuity->isChecked()) {
    sums = annuityСredit(&sums, &months, &procents, &overpayment, &totalSum);

    QString num1 = "\n\n" + QString::number(sums, 'f', 2);
    QString num2 = QString::number(overpayment, 'f', 2);
    QString num3 = QString::number(totalSum, 'f', 2);

    ui->ii->setText(num1);
    ui->over_l->setText(num2);
    ui->total_l->setText(num3);
  }
}
