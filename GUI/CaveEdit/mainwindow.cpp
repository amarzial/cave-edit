#include "mainwindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QWidget *wdg = new QWidget(this);
    QVBoxLayout *lay = new QVBoxLayout;
    QListWidget *list = new QListWidget(wdg);

    lay->addWidget(list);
    wdg->setLayout(lay);

    list->addItem("forise");
    QListWidgetItem *itm;
    itm = list->item(0);
    itm->setFlags(itm->flags() | Qt::ItemIsUserCheckable);
    itm->setCheckState(Qt::Unchecked);

    setCentralWidget(wdg);
    QObject::connect(list, &QListWidget::itemChanged, this, &MainWindow::panico);
}

void MainWindow::panico(QListWidgetItem *itm) {
    itm->setText("ao");
}

MainWindow::~MainWindow()
{

}


