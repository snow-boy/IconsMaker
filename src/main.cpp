#include "mainwindow.h"
#include <QApplication>
#include <QImage>
#include <QImageWriter>
#include <QtDebug>
#include <QFile>
#include "qicnshandler.h"
#include "icoreader.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    {
        QFile file(":/stylesheet/resource/qss/ntdark.qss");
        file.open(QIODevice::ReadOnly);
        a.setStyleSheet(QString::fromStdString(file.readAll().toStdString()));
    }

    MainWindow w;
    w.show();

//        QList<QImage> image_list;
//        {
//            QImage img;
//            img.load(R"(G:\my_projects\IconsMaker\test\icon-16.png)");

//            image_list.append(img);
//        }

//        {
//            QImage img;
//            img.load(R"(G:\my_projects\IconsMaker\test\icon-32.png)");

//            image_list.append(img);
//        }

//    {
//        QImage img;
//        img.load(R"(G:\my_projects\IconsMaker\test\icon-48.png)");

//        image_list.append(img);
//    }

//    {
//        QImage img;
//        img.load(R"(G:\my_projects\IconsMaker\test\icon-64.png)");

//        image_list.append(img);
//    }

//    {
//        QFile file("G:/test.ico");
//        file.open(QIODevice::WriteOnly);

//        ICOReader::write(&file, image_list);
//        file.close();
//    }

//    {
//        QFile file(R"(G:\axis\AxisBaseBranch\QtAxis\AppInfo\Axis_legacy.icns)");
//        file.open(QIODevice::ReadOnly);

//        QICNSHandler icns_handler;
//        icns_handler.setDevice(&file);
//        int image_count = icns_handler.imageCount();
//    }

//    {
//        QFile file("G:/test.icns");
//        file.open(QIODevice::WriteOnly);

//        QICNSHandler icns_handler;
//        icns_handler.setDevice(&file);

//        bool ret = icns_handler.write(image_list);
//        Q_ASSERT(ret);

//        file.close();
//    }

    return a.exec();
}
