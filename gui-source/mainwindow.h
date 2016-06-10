#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFileDialog>


#define NT 512
#define beta_max 10.0

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    unsigned int nbeta;
    double gamma;
    double image[NT][NT];
    double noisy[NT][NT];
    double restored[NT][NT];
    double noiseLevel;

private slots:
    void on_nbeta_box_editingFinished();

    void on_gamma_box_editingFinished();

    void on_gamma_slider_valueChanged(int value);

    void on_gamma_slider_sliderReleased();

    void on_restore_trigger_clicked();

    void on_manual_run_check_clicked();

    void on_auto_run_check_clicked();

    void on_add_noise_button_clicked();

    void on_image_path_clicked();

private:
    Ui::MainWindow *ui;
    bool autorun;

    void readImage();

    double ising(int i, int j);
    double gaussian(int i, int j);
    double energy(int i, int j, double beta);
    void loadImage(QString filepath);
    void addNoise();
    void imageRestore();
    void renderNoisy();
    void renderRestoration();
    double getNoiseRatio(double x[NT][NT]) const;
};

#endif // MAINWINDOW_H
