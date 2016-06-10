#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "random.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Default setting
    //srand(time(NULL));
    gamma = 1.0;
    nbeta = 100;
    noiseLevel = 0.2;

    loadImage(QString("./Lena.dat"));

    addNoise();

    ui->setupUi(this);

    // Set default manual run instead of auto run
    ui->manual_run_check->setChecked(true);
    autorun = false;

    ui->nbeta_box->setText(QString::number(nbeta));
    ui->gamma_box->setText(QString::number(gamma));
    ui->gamma_slider->setRange(0, 300);
    ui->gamma_slider->setValue(gamma * 100.0);
    ui->noise_level_box->setRange(0.01, 0.8);
    ui->noise_level_box->setSingleStep(0.01);
    ui->noise_level_box->setValue(noiseLevel);

    renderNoisy();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_nbeta_box_editingFinished()
{
    nbeta = ui->nbeta_box->text().toInt();
    if(autorun){
       imageRestore();
       renderRestoration();
    }
}

void MainWindow::on_gamma_box_editingFinished()
{
    gamma = ui->gamma_box->text().toDouble();
    ui->gamma_slider->setValue(gamma * 100.0);
    if(autorun){
        imageRestore();
        renderRestoration();
    }
}

void MainWindow::on_gamma_slider_valueChanged(int value)
{
    gamma = ui->gamma_slider->value() / 100.0;
    ui->gamma_box->setText(QString::number(gamma));
}

void MainWindow::on_gamma_slider_sliderReleased()
{
    qDebug() << "test" << endl;
    if(autorun){
        imageRestore();
        renderRestoration();
    }
}

void MainWindow::loadImage(QString filepath){
    QFile file(filepath);
    qDebug() << file.exists() << endl;
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    unsigned int rowCount = 0;
    while(!in.atEnd()){
        QString line = in.readLine();
        QStringList fields = line.split(",");
        for(int j = 0; j < fields.size(); j++){
            image[rowCount][j] = fields.at(j).toDouble();
        }
        rowCount++;
    }
    file.close();
}


double MainWindow::ising(int i, int j){
    if(i == 0){
        if(j == 0){
            if(restored[0][1] == restored[1][0]){
                return restored[i][j]*(4*restored[0][0]*restored[0][1]);
            }
            else return 0;
        }
        else if(j == NT-1){
            if(restored[0][NT-2] == restored[1][NT-1]){
                return restored[i][j]*(4*restored[0][NT-2]*restored[0][NT-1]);
            }
            else return 0;
        }
        else{
            if(restored[0][j-1] + restored[0][j+1] + restored[1][j] > 1.0){
                return restored[i][j]*(restored[0][j-1] + restored[0][j+1] + restored[1][j] + 1.0);
            }
            return restored[i][j]*(restored[0][j-1] + restored[0][j+1] + restored[1][j] - 1.0);
        }
    }
    else if(i == NT-1){
        if(j == 0){
            if(restored[NT-1][1] == restored[NT-2][0]){
                return restored[i][j]*(4*restored[NT-1][0]*restored[NT-1][1]);
            }
            else return 0;
        }
        else if(j == NT-1){
            if(restored[NT-1][NT-2] == restored[NT-2][NT-1]){
                return restored[i][j]*(4*restored[NT-1][NT-2]*restored[NT-1][NT-1]);
            }
            else return 0;
        }
        else{
            if(restored[NT-1][j-1] + restored[NT-1][j+1] + restored[NT-2][j] > 1.0){
                return restored[i][j]*(restored[NT-1][j-1] + restored[NT-1][j+1] + restored[NT-2][j] + 1.0);
            }
            return restored[i][j]*(restored[0][j-1] + restored[0][j+1] + restored[1][j] - 1.0);
        }
    }
    else if(j == 0){
        if(restored[i-1][0] + restored[i+1][0] + restored[i][1] > 1.0){
            return restored[i][j]*(restored[i-1][0] + restored[i+1][0] + restored[i][1] + 1.0);
        }
        return restored[i][j]*(restored[i-1][0] + restored[i+1][0] + restored[i][1] - 1.0);
    }
    else if(j == NT-1){
        if(restored[i-1][NT-1] + restored[i+1][NT-1] + restored[i][NT-2] > 1.0){
            return restored[i][j]*(restored[i-1][NT-1] + restored[i+1][NT-1] + restored[i][NT-2] + 1.0);
        }
        return restored[i][j]*(restored[i-1][NT-1] + restored[i+1][NT-1] + restored[i][NT-2] - 1.0);
    }
    return restored[i][j]*(restored[i-1][j] + restored[i+1][j] + restored[i][j-1] + restored[i][j+1]);
}

double MainWindow::gaussian(int i, int j){
  //return -0.42*(y[i][j] - restored[i][j])*(y[i][j] - restored[i][j]);
    return noisy[i][j] * restored[i][j];
}

double MainWindow::energy(int i, int j, double beta){
    return beta * gamma * gaussian(i, j) + beta * ising(i, j);
  //return (-gaussian(x, y, i, j) - beta*gamma*ising(x, i, j));
}

void MainWindow::imageRestore(){
    for(int i = 0; i < NT; i++){
        for(int j = 0; j < NT; j++){
            restored[i][j] = noisy[i][j];
        }
    }

    double beta = beta_max / (double)nbeta, d_action, naccept, nreject;
    for(int count = 0; count < nbeta; count++){
        //naccept = nreject = 0.0;
        for(int i = 0; i < NT; i++){
            for(int j = 0; j < NT; j++){
                restored[i][j] *= -1.0;
                d_action = energy(i,j,beta);
                restored[i][j] *= -1.0;
                d_action -= energy(i,j,beta);
                //if(d_action > 0 || exp(d_action) > rand() / (double) RAND_MAX){

                if(d_action > 0 || exp(d_action) > genrand()){
                    restored[i][j] *= -1.0;
                    //naccept += 1.0;
                }
                //else nreject += 1.0;
            }
        }
        /*
        for(int i = 0; i < NT; i++){
            for(int j = 0; j < NT; j++){
                average[i][j] += beta*restored[i][j];
            }
        }
        */
        beta += beta_max / (double)nbeta;
        //qDebug() << naccept / (naccept + nreject) << endl;
    }
}

void MainWindow::addNoise(){
    for(unsigned int i = 0; i < NT; i++){
        for(unsigned int j = 0; j < NT; j++){
            //noisy[i][j] = image[i][j] * (rand() / (double)RAND_MAX < noiseLevel ? -1.0 : 1.0);
            noisy[i][j] = (genrand() < noiseLevel ? -1.0 : 1.0) * image[i][j];
        }
    }
}

void MainWindow::on_restore_trigger_clicked()
{
    imageRestore();
    renderRestoration();
}

void MainWindow::on_manual_run_check_clicked()
{
    autorun = false;
}

void MainWindow::on_auto_run_check_clicked()
{
    autorun = true;
}


void MainWindow::renderNoisy(){
    QImage img(NT, NT, QImage::Format_Mono);
    for(unsigned int i = 0; i < NT; i++){
        for(unsigned int j = 0; j < NT; j++){
            int bin = noisy[i][j] > 0 ? 1 : 0;
            img.setPixel(QPoint(j, i), bin);
        }
    }
    ui->noisy_image->setPixmap(QPixmap::fromImage(img));
    ui->noisy_image->show();
    ui->original_noise_level->setText(QString::number(getNoiseRatio(noisy) * 100).append("%"));
}

void MainWindow::renderRestoration(){
    QImage img(NT, NT, QImage::Format_Mono);
    for(unsigned int i = 0; i < NT; i++){
        for(unsigned int j = 0; j < NT; j++){
            int bin;
            if(restored[i][j] == 0){
                bin = noisy[i][j] > 0? 1 : 0;
            } else {
                bin = restored[i][j] > 0 ? 1 : 0;
            }
            img.setPixel(QPoint(j, i), bin);
        }
    }
    ui->restore_image->setPixmap(QPixmap::fromImage(img));
    ui->restore_image->show();
    ui->restore_noise_level->setText(QString::number(getNoiseRatio(restored) * 100).append("%"));
}

void MainWindow::on_add_noise_button_clicked()
{
    noiseLevel = ui->noise_level_box->value();
    addNoise();
    renderNoisy();
}

void MainWindow::on_image_path_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Select an image data file"), "./", tr("All Files (*)"));
    ui->path_display->setText(file.split("/").back());
    loadImage(file);
    addNoise();
    renderNoisy();
}

double MainWindow::getNoiseRatio(double x[NT][NT]) const{
    double ratio = 0.0;
    for(unsigned int i = 0; i < NT; i++){
        for(unsigned int j = 0; j < NT; j++){
            if(image[i][j] != x[i][j]){
                ratio++;
            }
        }
    }
    return ratio / NT / NT;
}
