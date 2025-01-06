#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "drawarea.h"
#include "QTimer"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto button = ui->start_button;
    auto layout = ui->verticalLayout;


    this->draw_area = new DrawArea();
    layout->addWidget(draw_area);

    // Connexions pour les sliders
    connect(ui->slider_vx, &QSlider::valueChanged, this, &MainWindow::updateVx);
    connect(ui->slider_vy, &QSlider::valueChanged, this, &MainWindow::updateVy);
    connect(ui->slider_r, &QSlider::valueChanged, this, &MainWindow::updateR);
    connect(ui->slider_m, &QSlider::valueChanged, this, &MainWindow::updateM);

    // Connexions pour les zones de texte
    connect(ui->input_vx, &QLineEdit::textChanged, this, &MainWindow::updateVxFromInput);
    connect(ui->input_vy, &QLineEdit::textChanged, this, &MainWindow::updateVyFromInput);
    connect(ui->input_r, &QLineEdit::textChanged, this, &MainWindow::updateRFromInput);
    connect(ui->input_m, &QLineEdit::textChanged, this, &MainWindow::updateMFromInput);


    draw_area->setM(20);
    draw_area->setR(10);
    draw_area->setVx(0);
    draw_area->setVy(0);
}

void MainWindow::updateVx(int value) {
    float vx = value;
    ui->input_vx->setText(QString::number(vx));
    draw_area->setVx(vx);
}

void MainWindow::updateVy(int value) {
    float vy = value;
    ui->input_vy->setText(QString::number(vy));
    draw_area->setVy(vy);
}

void MainWindow::updateR(int value) {
    float r = value ;
    ui->input_r->setText(QString::number(r));
    draw_area->setR(r);
}

void MainWindow::updateM(int value) {
    float m = value;
    ui->input_m->setText(QString::number(m));
    draw_area->setM(m);
}

void MainWindow::updateVxFromInput(const QString &text) {
    float vx = text.toFloat();
    ui->slider_vx->setValue(static_cast<int>(vx));
    draw_area->setVx(vx);
}

void MainWindow::updateVyFromInput(const QString &text) {
    float vy = text.toFloat();
    ui->slider_vy->setValue(static_cast<int>(vy));
    draw_area->setVy(vy);
}

void MainWindow::updateRFromInput(const QString &text) {
    float r = text.toFloat();
    ui->slider_r->setValue(static_cast<int>(r));
    draw_area->setR(r);
}

void MainWindow::updateMFromInput(const QString &text) {
    float m = text.toFloat();
    ui->slider_m->setValue(static_cast<int>(m));
    draw_area->setM(m);
}



MainWindow::~MainWindow()
{
    delete ui;
}
