#include "shoppingcart.h"
#include "ui_shoppingcart.h"

#include <QKeyEvent>
#include "deletebutton.h"
#include <iostream>
//#include "checkoutbutton.h"
#include <QPalette>
#include <QColorDialog>

ShoppingCart::ShoppingCart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShoppingCart)
{
    ui->setupUi(this);
    ui->shoppingTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->deleteRowButton->setMainWindow(this);
    ui->outputLabel->setStyleSheet("font-weight: bold; color: red;");
    ui->outputLabel->setVisible(false); // makes label invisible

    ui->shoppingTable->setColumnCount(2);
    ui->shoppingTable->setEditTriggers(QAbstractItemView::NoEditTriggers);


    //distributed collaboration
    connect(ui->deleteRowButton,SIGNAL(clicked()),ui->deleteRowButton,SLOT(deleteRow())); // deletes selection
    connect(ui->checkoutPriceButton,SIGNAL(clicked()),ui->shoppingTable,SLOT(checkout())); // checkout
    connect(ui->shoppingTable,SIGNAL(changeLabel(QString)),ui->outputLabel,SLOT(changeText(QString))); // checkout

}

ShoppingCart::~ShoppingCart()
{
    delete ui;
}


void ShoppingCart::showOrHide(){
    if (isVisible() == false){
        show();
        emit isShown(true);
    }
    else{
        hide();
        emit isShown(false);
    }
}

// workaround to emit a signal whenever window is closed
void ShoppingCart::closeEvent(QCloseEvent *event){
    emit dialogClosed();
    event->accept(); // accepts the closure
}

cartTable* ShoppingCart::returnTable(){
    return this->ui->shoppingTable;
}


