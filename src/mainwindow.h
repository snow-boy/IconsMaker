#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QList>
#include <QVBoxLayout>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionLoad_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

private:
    void InitUI();
    void LoadIco(const QString &file_path);
    void LoadIcns(const QString &file_path);

    void UpdateImageListView();

    QString ico_file_path_;

    QList<QImage> image_list_;

    Ui::MainWindow *ui;

    QVBoxLayout *layout_;
    QList<QLabel *> image_label_list_;
};

#endif // MAINWINDOW_H
