#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QMainWindow>
#include "candidat.h"
#include "qrcode.h"
#include <QCameraViewfinder>
#include <QCameraInfo>
#include <QCamera>
#include <QCameraImageCapture>
#include <QMediaMetaData>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateQRImage();
void setCamera(const QCameraInfo &cameraInfo);
void readyForCapture(bool ready);
void updateChart(QVBoxLayout *layout);

private slots:

    void on_pushButton_2_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_3_clicked();

    void on_pb_ajouter_clicked();

    void on_lineEdit_textChanged(const QString &arg1);


    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_takeImageButton_clicked();


    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pb_ajouter_2_clicked();

    void on_pushButton_8_clicked();

    void on_comboBox_2_currentTextChanged(const QString &arg1);

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_tableView_2_clicked(const QModelIndex &index);

private:
QString ref;

    bool successfulEncoding;
    int encodeImageSize;
    QPoint lastPos;
    CQR_Encode qrEncode;
    bool isCapturingImage = false;
    Ui::MainWindow *ui;
    QCamera *Camera = nullptr;
    QCameraImageCapture *imageCapture = nullptr;

};

#endif // MAINWINDOW_H
