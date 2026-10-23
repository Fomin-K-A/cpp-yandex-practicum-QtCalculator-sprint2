#pragma once

#include "calculator.h"

#include <QMainWindow>

enum class Operation{
    NO_OPERATION,
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,
    POWER
};

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    void ResetInput();
    void UpdateDisplay();
private slots:
    void SetText(const QString& text);
    void AddText(const QString& suffix);
    void SetOperation(Operation op);
    void Calculate(double number);
    void on_tb_seven_clicked();
    void on_tb_eight_clicked();
    void on_tb_nine_clicked();
    void on_tb_four_clicked();
    void on_tb_five_clicked();
    void on_tb_six_clicked();
    void on_tb_one_clicked();
    void on_tb_two_clicked();
    void on_tb_three_clicked();
    void on_tb_comma_clicked();
    void on_tb_negate_clicked();
    void on_tb_backspace_clicked();
    void on_tb_power_clicked();
    void on_tb_divide_clicked();
    void on_tb_multiplicate_clicked();
    void on_tb_substract_clicked();
    void on_tb_add_clicked();
    void on_tb_equal_clicked();
    void on_tb_reset_clicked();
    void on_tb_zero_clicked();
    void on_tb_ms_clicked();
    void on_tb_mc_clicked();
    void on_tn_mr_clicked();
private:
    Calculator calculator_;
    Ui::MainWindow* ui;
    QString input_number_;
    Number active_number_;
    Operation current_operation_ = Operation::NO_OPERATION;
    bool is_saved_ = false;
    double saved_number_;
    bool is_new_input_ = false;
    bool is_memory_displayed_ = false;
};

QString RemoveTrailingZeroes(const QString &text);
QString NormalizeNumber(const QString &text);
QString OpToString(Operation op);
