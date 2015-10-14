#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"slmui.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    new SlmUi(this);
    ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
}

MainWindow::~MainWindow()
{
    delete ui;
}
