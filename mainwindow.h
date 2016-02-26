#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>

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
    void on_start_clicked();
    void on_stop_clicked();
    void onReadyReadStandardOutput();
    void onReadyReadStandardError();
    void onStarted();
    void onFinished();

private:
    Ui::MainWindow *ui;
    QProcess *process;
};

#endif // MAINWINDOW_H
