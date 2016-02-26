#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->start->setDisabled(false);
    ui->stop->setDisabled(true);
    process = new QProcess(parent);
    connect (process, SIGNAL(readyReadStandardOutput()), this, SLOT(onReadyReadStandardOutput()));
    connect (process, SIGNAL(readyReadStandardError()), this, SLOT(onReadyReadStandardError()));
    connect (process, SIGNAL(started()), this, SLOT(onStarted()));
    connect (process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(onFinished()));
}

void MainWindow::on_start_clicked()
{
    process->start(ui->command->text());
}

void MainWindow::on_stop_clicked()
{
    process->terminate();
}

void MainWindow::onStarted()
{
    ui->progress->setMaximum(0);
    ui->start->setDisabled(true);
    ui->stop->setDisabled(false);
    ui->output->clear();
}

void MainWindow::onFinished()
{
    ui->progress->setMaximum(100);
    ui->start->setDisabled(false);
    ui->stop->setDisabled(true);
}

void MainWindow::onReadyReadStandardOutput()
{
    ui->output->appendPlainText(process->readAllStandardOutput());
}

void MainWindow::onReadyReadStandardError()
{
    ui->output->appendPlainText(process->readAllStandardError());
}

MainWindow::~MainWindow()
{
    process->kill();
    delete process;
    delete ui;
}
