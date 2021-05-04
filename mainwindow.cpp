#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "yscene.h"
#include   <QPushButton>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPushButton w(this);
    this->show();
   dayScene d(this);
   d.show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

