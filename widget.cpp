#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>

#define COFFEE 100
#define TEA 150
#define MILK 200

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::changeMoney(int count)
{
    money += count;

    if (money <= 10000) {
        ui -> lcdNumber -> display(money);

        checkProduct();
    }
    else {
        changeOut(count);
        customMessageBox("Alert", "You can't insert over than 10,000");
    }
}

void Widget::checkProduct() {
    ui -> pbReset -> setEnabled(money > 0);
    ui -> pbCoffee -> setEnabled(money >= COFFEE);
    ui -> pbTea -> setEnabled(money >= TEA);
    ui -> pbMilk -> setEnabled(money >= MILK);
}

void Widget::productOut(int price, const char *productName) {
    changeMoney(-price);
    customMessageBox("Product Out", productName);
}

void Widget::changeOut(int value) {
    int ch500 = 0;
    int ch100 = 0;
    int ch50 = 0;
    int ch10 = 0;
    int allChange = value;
    while((allChange) >= 500) {
        ch500 = allChange / 500;
        allChange = allChange - 500 * ch500;
    }
    while((allChange) >= 100) {
        ch100 = allChange / 100;
        allChange = allChange - 100 * ch100;
    }
    while(allChange >= 50) {
        ch50 = allChange / 50;
        allChange = allChange - 50 * ch50;
    }
    while(allChange >= 10) {
        ch10 = allChange / 10;
        allChange = allChange - 10 * ch10;
    }
    char changeValue[100];
    sprintf(changeValue, "500: %d, 100: %d, 50: %d, 10: %d", ch500, ch100, ch50, ch10);
    changeMoney(-value);
    customMessageBox("Change Out ", changeValue);
}

void Widget::resetMoney() {
    // while(money >= 500) {
    //     changeOut(500);
    // }
    // while(money >= 100) {
    //     changeOut(100);
    // }
    // while(money >= 50) {
    //     changeOut(50);
    // }
    // while(money >= 10) {
    //     changeOut(10);
    // }
    changeOut(money);
}

void Widget::customMessageBox(const char *title, const char *contents) {
    QMessageBox m;
    m.information(nullptr, title, contents);
}

void Widget::on_pb10_clicked()
{
    changeMoney(10);
}


void Widget::on_pb50_clicked()
{
    changeMoney(50);
}


void Widget::on_pb100_clicked()
{
    changeMoney(100);
}


void Widget::on_pb500_clicked()
{
    changeMoney(500);
}


void Widget::on_pbCoffee_clicked()
{
    productOut(COFFEE, "Coffee");
}


void Widget::on_pbTea_clicked()
{
    productOut(TEA, "Tea");
}


void Widget::on_pbMilk_clicked()
{
    productOut(MILK, "Milk");
}


void Widget::on_pbReset_clicked()
{
    resetMoney();
}

