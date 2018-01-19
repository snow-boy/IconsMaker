#include "mainwindow.h"
#include <QFileDialog>
#include <QLabel>
#include "ui_mainwindow.h"
#include "qicnshandler.h"
#include "icoreader.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    layout_(nullptr)
{
    ui->setupUi(this);
    InitUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionLoad_triggered()
{
    QStringList files = QFileDialog::getOpenFileNames(this, tr("Open Image"), QString(), tr("Image Files (*.jpeg *.png *.bmp)"));
    image_list_.clear();
    for(QString file: files){
        QImage image;
        if(image.load(file)){
            image_list_.append(image);
        }
    }

    UpdateImageListView();
}

void MainWindow::on_actionOpen_triggered()
{
    QString file_path = QFileDialog::getOpenFileName(this, tr("Open Icon"), QString(), tr("Icon Files (*.ico *.icns)"));
    if(QFile::exists(file_path)){
        ico_file_path_ = file_path;
        QFileInfo file_info(file_path);
        if(file_info.suffix() == "ico"){
            LoadIco(file_path);
        }
        else if(file_info.suffix() == "icns"){
            LoadIcns(file_path);
        }
        else{
            Q_ASSERT(false);
        }
    }
}

void MainWindow::on_actionSave_triggered()
{
    if(image_list_.size() == 0){
        return;
    }

    QString file_path = QFileDialog::getSaveFileName(this, tr("Save Icon"), QString(),
                                                     tr("Windows Icon (*.ico);;MacOS Icon (*.icns)"));
    QFile file(file_path);
    if(file.open(QIODevice::WriteOnly)){
        QFileInfo file_info(file_path);
        if(file_info.suffix() == "ico"){
            ICOReader::write(&file, image_list_);
        }
        else if(file_info.suffix() == "icns"){
            QICNSHandler handler;
            handler.setDevice(&file);
            handler.write(image_list_);
        }
    }
}

void MainWindow::InitUI()
{
    layout_ = new QVBoxLayout;
    ui->scrollArea->widget()->setLayout(layout_);
}

void MainWindow::LoadIco(const QString &file_path)
{
    QFile file(file_path);
    file.open(QIODevice::ReadOnly);

    image_list_ = ICOReader::read(&file);
    UpdateImageListView();
}

void MainWindow::LoadIcns(const QString &file_path)
{
    QFile file(file_path);
    file.open(QIODevice::ReadOnly);

    image_list_.clear();
    QICNSHandler handler;
    handler.setDevice(&file);
    for(int i = 0; i < handler.imageCount(); ++i){
        handler.jumpToImage(i);
        QImage image;
        handler.read(&image);
        image_list_.append(image);
    }
    UpdateImageListView();
}

void MainWindow::UpdateImageListView()
{
    for(QLabel *label: image_label_list_){
        layout_->removeWidget(label);
        delete label;
    }
    image_label_list_.clear();

    for(QImage image: image_list_){
        QLabel *label = new QLabel;
        image_label_list_.append(label);
        label->setMinimumSize(image.size());
        label->setPixmap(QPixmap::fromImage(image));
        layout_->addWidget(label);
    }
}
