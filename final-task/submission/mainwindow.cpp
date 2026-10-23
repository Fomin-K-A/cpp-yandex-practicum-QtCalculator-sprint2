#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    input_number_ = "0";
    active_number_ = 0;
    current_operation_ = Operation::NO_OPERATION;
    is_saved_ = false;
    saved_number_ = 0;
    is_memory_displayed_ = false;

    ui->l_result->setText("0");
    ui->l_memory->setText("");
    ui->l_formula->setText("");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::ResetInput() {
    input_number_ = "0";
    active_number_ = 0;
    is_memory_displayed_ = false;
    SetText(input_number_);
}

void MainWindow::SetText(const QString& text){
    input_number_ = text;
    RemoveTrailingZeroes(input_number_);
    input_number_ = NormalizeNumber(input_number_);
    active_number_ = input_number_.toDouble();
    ui->l_result->setText(input_number_);
}

void MainWindow::AddText(const QString& suffix){
    if (is_memory_displayed_) {
        ResetInput();
        is_memory_displayed_ = false;
    }

    if (is_new_input_) {
        input_number_ = "0";
        ui->l_formula->setText("");
        is_new_input_ = false;
    }

    if (input_number_ == "0" && suffix != ".") {
        input_number_.clear();
    }
    input_number_ += suffix;
    SetText(input_number_);
}

QString RemoveTrailingZeroes(const QString &text) {
    if (text.isEmpty()){
        return "0";
    }
    if (text.startsWith('-')) {
        return "-" + RemoveTrailingZeroes(text.mid(1));
    }
    if (text.contains('.')) {
        QString integerPart = text.section('.', 0, 0);
        QString decimalPart = text.section('.', 1, 1);
        while (decimalPart.endsWith('0')) {
            decimalPart.chop(1);
        }

        if (decimalPart.isEmpty()) {
            return integerPart;
        } else {
            return integerPart + "." + decimalPart;
        }
    }
    return text;
}

QString NormalizeNumber(const QString &text) {
    if (text.isEmpty()) {
        return "0";
    }
    QString result = text;
    if (result.startsWith('.')) {
        result = "0" + result;
    }
    if (result.startsWith("-.")) {
        result = "-0" + result.mid(1);
    }
    if (result.startsWith('0') && result.length() > 1 && !result.startsWith("0.")) {
        result = RemoveTrailingZeroes(result);
    }
    if (result.isEmpty() || result == "-") {
        return "0";
    }
    return result;
}

void MainWindow::SetOperation(Operation op) {
    is_new_input_ = false;
    is_memory_displayed_ = false;
    if (current_operation_ != Operation::NO_OPERATION) {
        on_tb_equal_clicked();
    }
    calculator_.Set(active_number_);
    QString text = QString::number(calculator_.GetNumber()) + " " + OpToString(op) + " ";
    ui->l_formula->setText(text);
    input_number_.clear();
    current_operation_ = op;
}

QString OpToString(Operation op) {
    switch(op) {
    case Operation::NO_OPERATION: return "";
    case Operation::ADDITION: return "+";
    case Operation::DIVISION: return "÷";
    case Operation::MULTIPLICATION: return "×";
    case Operation::SUBTRACTION: return "−";
    case Operation::POWER: return "^";
    default: return "";
    }
}

void MainWindow::Calculate(double number) {
    switch (current_operation_) {
    case Operation::ADDITION:
        calculator_.Add(number);
        break;
    case Operation::SUBTRACTION:
        calculator_.Sub(number);
        break;
    case Operation::MULTIPLICATION:
        calculator_.Mul(number);
        break;
    case Operation::DIVISION:
        if (number != 0) {
            calculator_.Div(number);
        }
        break;
    case Operation::POWER:
        calculator_.Pow(number);
        break;
    default:
        break;
    }
}

void MainWindow::on_tb_backspace_clicked()
{
    if (is_memory_displayed_ || is_new_input_) {
        return;
    }

    if(input_number_.size()==0){
        return;
    }
    else{
        input_number_.chop(1);
    }
    SetText(input_number_);
}

void MainWindow::on_tb_comma_clicked()
{
    if (is_memory_displayed_) {
        ResetInput();
        is_memory_displayed_ = false;
    }

    if (input_number_.contains(".")) {
        return;
    }
    else{
        AddText(".");
    }
}

void MainWindow::on_tb_negate_clicked()
{
    if(input_number_.startsWith("0")){
        return;
    }
    if (input_number_.startsWith("-")){
        input_number_ = input_number_.mid(1);
    }
    else{
        input_number_.prepend("-");
    }
    SetText(input_number_);
}

void MainWindow::on_tb_seven_clicked()
{
    AddText("7");
}

void MainWindow::on_tb_eight_clicked()
{
    AddText("8");
}

void MainWindow::on_tb_nine_clicked()
{
    AddText("9");
}

void MainWindow::on_tb_four_clicked()
{
    AddText("4");
}

void MainWindow::on_tb_five_clicked()
{
    AddText("5");
}

void MainWindow::on_tb_six_clicked()
{
    AddText("6");
}

void MainWindow::on_tb_one_clicked()
{
    AddText("1");
}

void MainWindow::on_tb_two_clicked()
{
    AddText("2");
}

void MainWindow::on_tb_three_clicked()
{
    AddText("3");
}

void MainWindow::on_tb_zero_clicked()
{
    AddText("0");
}

void MainWindow::on_tb_power_clicked()
{
    Operation op = Operation::POWER;
    SetOperation(op);
}

void MainWindow::on_tb_divide_clicked()
{
    Operation op = Operation::DIVISION;
    SetOperation(op);
}

void MainWindow::on_tb_multiplicate_clicked()
{
    Operation op = Operation::MULTIPLICATION;
    SetOperation(op);
}

void MainWindow::on_tb_substract_clicked()
{
    Operation op = Operation::SUBTRACTION;
    SetOperation(op);
}

void MainWindow::on_tb_add_clicked()
{
    Operation op = Operation::ADDITION;
    SetOperation(op);
}

void MainWindow::on_tb_equal_clicked() {
    if (current_operation_ == Operation::NO_OPERATION) {
        return;
    }
    Calculate(active_number_);
    QString text = ui->l_formula->text() + QString::number(active_number_) + " =";
    ui->l_formula->setText(text);
    active_number_ = calculator_.GetNumber();
    input_number_ = QString::number(active_number_);
    SetText(input_number_);
    current_operation_ = Operation::NO_OPERATION;
    is_new_input_ = true;
    is_memory_displayed_ = false;
}

void MainWindow::on_tb_reset_clicked() {
    calculator_.Set(0);
    current_operation_ = Operation::NO_OPERATION;
    ui->l_formula->setText("");
    is_new_input_ = false;
    is_memory_displayed_ = false;
    ResetInput();
}

void MainWindow::on_tb_ms_clicked()
{
    saved_number_ = active_number_;
    is_saved_ = true;
    ui->l_memory->setText("M");
}

void MainWindow::on_tb_mc_clicked()
{
    saved_number_ = 0.0;
    is_saved_ = false;
    is_memory_displayed_ = false;
    ui->l_memory->clear();
}

void MainWindow::on_tn_mr_clicked()
{
    if(!is_saved_){
        return;
    }
    active_number_ = saved_number_;
    input_number_ = QString::number(saved_number_);
    SetText(input_number_);
    is_memory_displayed_ = true;
}
