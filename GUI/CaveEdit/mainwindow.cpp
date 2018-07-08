#include <QPushButton>
#include <QVBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QCoreApplication>

#include "mainwindow.h"
#include "caveedit/file_editor.hpp"
#include "caveedit/flag.hpp"

#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QWidget *wdg = new QWidget(this);
    QVBoxLayout *lay = new QVBoxLayout;
    QListWidget *list = new QListWidget(wdg);

    auto args = QCoreApplication::arguments();
    if (args.size() < 2)
        return;
    int profile = 1;
    if (args.size() == 3)
        profile = std::stoi(args.at(2).toStdString());
    FileEditor editor(args.at(1).toStdString(), profile);


    lay->addWidget(list);
    wdg->setLayout(lay);

    const auto& flist = flag::list();
    for (auto i = 0u; i < flist.size(); ++i) {
        auto itm = new QListWidgetItem(QString::fromStdString(flist[i].description));
        itm->setFlags(itm->flags() | Qt::ItemIsUserCheckable);
        itm->setCheckState(editor.get_flag(i) ? Qt::Checked : Qt::Unchecked);
        list->addItem(itm);
    }

    setCentralWidget(wdg);
    QObject::connect(list, &QListWidget::itemChanged, this, &MainWindow::panico);
}

void MainWindow::panico(QListWidgetItem *itm) {
    //itm->setText("ao");
}

MainWindow::~MainWindow()
{

}


