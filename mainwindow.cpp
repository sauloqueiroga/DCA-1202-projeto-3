#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);

    connect(ui->Connect,
            SIGNAL(clicked(bool)),
            this,
            SLOT(Connect()));

    connect(ui->Disconnect,
            SIGNAL(clicked(bool)),
            this,
            SLOT(Disconnect()));

    connect(ui->Start,
            SIGNAL(clicked(bool)),
            this,
            SLOT(Start()));

    connect(ui->Stop,
            SIGNAL(clicked(bool)),
            this,
            SLOT(Stop()));

}
void MainWindow::putData(){
    int Max = ui->slider_Max->value();
    int Min = ui->slider_Min->value();
    QDateTime datetime;
    QString str;

    if(socket->state() == QAbstractSocket::ConnectedState){
        datetime = QDateTime::currentDateTime();
        str = "Set: "+
            datetime.toString(Qt::ISODate)+
            " '"+
            QString::number(qrand()%(Max-Min)+Min)+"'\r\n";

        qDebug() << str;
        qDebug() << socket->write(str.toStdString().c_str()) << "bytes escritos";
        if(socket->waitForBytesWritten(3000)){
            qDebug() << "wrote";
        }
        ui->textBrowser->append(str);
    }
}

MainWindow::~MainWindow(){
    delete ui;
    delete socket;
}

void MainWindow::Connect(){
    QString estado;
    socket->connectToHost(ui->ip_Servidor->text(), 1234);

    if(socket->waitForConnected(3000)){
        estado = "connected.\n";
        qDebug() << "connected.";
        ui->textBrowser->append(estado);
    }
    else{
        qDebug() << "disconnected.";
    }
}


void MainWindow::Disconnect(){
    QString estado;
    estado = "Disconnected.\n";
    ui->textBrowser->append(estado);

    socket->close();
}


void MainWindow::Start(){

    QString estado;
    estado = "Started.\n";
    ui->textBrowser->append(estado);

    temporizador = startTimer((ui->slider_Timing->value())*1000);
}


void MainWindow::Stop(){

    QString estado;
    estado = "Stoped.\n";
    ui->textBrowser->append(estado);

    killTimer(temporizador);
}


void MainWindow::timerEvent(QTimerEvent *e)
{
    putData();
}
