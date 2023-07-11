#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->treeWidget->setHeaderLabel(tr("Sockets"));

    QTreeWidgetItem *clientItem = new QTreeWidgetItem(QStringList(tr("Client")));
    QTreeWidgetItem *serverItem = new QTreeWidgetItem(QStringList(tr("Server")));
    ui->treeWidget->addTopLevelItem(clientItem);
    ui->treeWidget->addTopLevelItem(serverItem);
}

MainWindow::~MainWindow()
{
    delete ui;
}

