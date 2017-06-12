#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);                                   // Construtor

    ~MainWindow();                                                              // Destrutor

public slots:
    void putData();                                                             //Escreve a data, a hora e o valor aleatorio

private slots:
    void Connect();                                                        //Conecta ao servidor

    void Disconnect();                                                     //Disconecta do servidor

    void Start();                                                          //Inicia o programa

    void Stop();                                                           //Para o Programa

    void timerEvent(QTimerEvent *e);

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    int temporizador;
};

#endif // MAINWINDOW_H
