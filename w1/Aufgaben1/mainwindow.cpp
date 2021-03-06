#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::showMat(const Mat &mat){
    // convert Mat object to QImage object
    QImage image( mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888 );
    image = image.rgbSwapped();

    // convert QImage object to QPixmap object
    QPixmap pixmap = QPixmap::fromImage(image);

    // set QPixmap object for QLabel
    ui->imageLabel->setPixmap(pixmap);
}

void MainWindow::on_actionKreise_triggered()
{
    Mat image(400, 400, CV_8UC3);
    image = Scalar(255,255,255);						// Hintergrundfarbe setzen
    Point center(image.cols/2, image.rows/2);			// Kreismittelpunkt
    const Scalar colorBlack(0,0,0);							// Kreisfarbe
    for(int radius = 20; radius < 200; radius += 20){
        circle(image, center, radius, colorBlack);
    }
    showMat(image);
}

void MainWindow::on_actionPunkte_triggered()
{
    const int anzahlKreise = 1000;
    const int radius = 20;
    Mat image(400, 400, CV_8UC3);
    for(int i = 0; i < anzahlKreise; i++){
        int x = rand() * image.cols / RAND_MAX;
        int y = rand() * image.rows / RAND_MAX;
        Point center(x,y);
        int r = rand() * 255 / RAND_MAX;
        int g = rand() * 255 / RAND_MAX;
        int b = rand() * 255 / RAND_MAX;
        Scalar color(b,g,r);
        circle(image, center, radius, color, CV_FILLED);
    }
    showMat(image);
}

void MainWindow::on_actionZebrastreifen_triggered()
{
    const Scalar colorBlack(0,0,0);
    const Scalar colorWhite(255,255,255);
    const int breite = 20;
    Mat image(400, 400, CV_8UC3);
    image = colorWhite;									// Hintergrund auf weiss
    for(int x = 0; x < image.cols; x += 2*breite){
        Point linksOben(x, 0);
        Point rechtsUnten(x + breite, image.rows);

        rectangle(image, linksOben, rechtsUnten, colorBlack, CV_FILLED);
    }
    showMat(image);
}

void MainWindow::on_actionFarbiges_Schachbrett_triggered()
{
    Mat image(400, 400, CV_8UC3);
    const int breite = image.rows/10;


    for(int x = 0; x < image.cols; x += breite){
        for(int y = 0; y < image.rows; y += breite){
            int r = rand() * 255 / RAND_MAX;
            int g = rand() * 255 / RAND_MAX;
            int b = rand() * 255 / RAND_MAX;
            Scalar color(b,g,r);
            Point linksOben(x, y);
            Point rechtsUnten(x + breite, y + breite);
            rectangle(image, linksOben, rechtsUnten, color, CV_FILLED);
        }
    }
    showMat(image);
 }

void MainWindow::on_actionSchachbrett_triggered()
{
    Mat image(400, 400, CV_8UC3);

    const Scalar colorBlack(0,0,0);
    const Scalar colorWhite(255,255,255);
    const int breite = image.rows/10;

    image = colorWhite;									// Hintergrund auf weiss

    for(int x = 0; x < image.cols; x += breite){
        for(int y = 0; y < image.rows; y += breite){
            if ((x + y) % (2*breite) == 0){
                Point linksOben(x, y);
                Point rechtsUnten(x + breite, y + breite);
                rectangle(image, linksOben, rechtsUnten, colorBlack, CV_FILLED);
            }
        }
    }
    showMat(image);

}
