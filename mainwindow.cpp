#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <fstream>
#include <iostream>
#include <QDebug>
#include <QDir>
#include <string>
#include <sstream>
//using namespace std;

#include "databasebuilder.h"
#include "databaseparser.h"
#include "PetDatabase.h"
#include "PetDatabaseSortableByName.h"
#include "BubbleSortDecreasing.h"
#include "BubbleSortIncreasing.h"

// Patterns to use:
//1. You will exercise Abstract Factory Pattern, Composite Pattern,
//    Builder pattern and Visitor Pattern in database construction.

// Abstract factory pattern: Abstract class as
// inteface for concrete algorithm classes

// Composite Pattern (Bundles): Abstract Base class that other
// concrete classes inherit from. Can make bundles which are products of
// other concrete products.

// Builder Pattern:  When you want to build complex data structures
// from some data. Give builder some information and have it build the object

// Visitor Pattern: Make a visitor that the old class accepts to add new functions.
// Old class accepts visitor which lets the visitor do its one role

// For the shopping cart/mainwindow observer pattern
// and distributed collaboration necessary

// To do:
// Load the database and build it with builder pattern?
// Use visitor pattern to calculate bundle prices?
// bundles are composites (composite pattern)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->addCartButton->setEnabled(false);
    ui->showButton->setEnabled(false);

    // SetTable
    ui->mainTable->setColumnCount(4);

    // Current directory
    qDebug() << QDir::currentPath();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadButton_clicked()
{
    // enable other buttons
    ui->addCartButton->setEnabled(true);
    ui->showButton->setEnabled(true);

    // open pets file and read for mainTable
    string file = "Pets.csv";

    // builds a petvector for use in the petdatabase classes
    DatabaseBuilder builder;
    DatabaseParser parser;
    parser.setBuilder(&builder);
    parser.parse(file);
    vector<Pet*> database = builder.getDatabase();
    BubbleSortIncreasing bs;
    PetDatabaseSortableByName petDatabaseSortableByName(database);
    bs.sort(&petDatabaseSortableByName);
    petDatabaseSortableByName.DisplayRecords();

    // returns sorted database
    database = petDatabaseSortableByName.returnDatabase();

    // construct main table
    for (unsigned int i = 0; i < database.size(); i++){
        std::string name = database[i]->GetName();
        std::string animal = database[i]->GetAnimal();

        // need to fix presicion for price *******
        std::ostringstream converter;
        converter << std::setprecision(4) << database[i]->GetPrice();
        std::string price = converter.str();

        std::string type = database[i]->GetType();

        int row_number = ui->mainTable->rowCount();
        ui->mainTable->insertRow(ui->mainTable->rowCount());
        ui->mainTable->setItem(row_number, 0,  new QTableWidgetItem(QString::fromStdString(name)));
        ui->mainTable->setItem(row_number, 1,  new QTableWidgetItem(QString::fromStdString(animal)));
        ui->mainTable->setItem(row_number, 2,  new QTableWidgetItem(QString::fromStdString(price)));
        ui->mainTable->setItem(row_number, 3,  new QTableWidgetItem(QString::fromStdString(type)));
    }


    // Ideas for building table:
    // Could use a visitor with a pointer to the maintable to construct it. It could accept a petDatabase so we could import
    // PetDatabaseSortablebyName into it. Does that follow the pattern exactly?

    // Make another builder that uses a parser to parse petvectors? We could return sorted petvectors from PetDatabaseSortable
    // and then input it into a parser and then into a builder?
    // petVector = PetDatabaseSortableByName->returnVector() --->
    // TableParser(petVector)---->TableBuilder(this would use a pointer to the main table, so not sure if it matches the pattern?)
    // also table->setRowCount(0); will auto delete all rows

    /*
    TableParser Tparser;
    TableBuilder Tbuilder;
    parser.setBuilder(&Tbuilder);
    parser.parse(database);
    */


    ui->loadButton->setEnabled(false);
}




