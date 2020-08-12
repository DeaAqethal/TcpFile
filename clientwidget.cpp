#include "clientwidget.h"
#include "ui_clientwidget.h"
#include <QMessageBox>
#include <QHostAddress>
clientwidget::clientwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::clientwidget)
{
    ui->setupUi(this);
    isStart = true;
    tcpSocket = new QTcpSocket(this);

    connect(tcpSocket,&QTcpSocket::readyRead,
            [=]
            {
                QByteArray buf = tcpSocket->readAll();

                if(true == isStart)
                {
                    isStart = false;

                    fileName = QString(buf).section("##",0,0);
                    fileSize = QString(buf).section("##",1,1).toInt();
                    receiveSize = 0;

                    file.setFileName(fileName);

                    bool isOk = file.open(QIODevice::WriteOnly);
                    if(isOk == false)
                    {
                        qDebug()<<"只读方式打开出错";
                    }
                }
                else
                {
                    qint64 len = file.write(buf);
                    receiveSize +=len;
                    float f = 100.0*receiveSize/fileSize;
                    ui->progressBar->setValue(f);
                    if(receiveSize==fileSize)
                    {
                        file.close();
                        QMessageBox::information(this,"完成","文件接收完成");
                        ui->progressBar->setValue(0);
                        tcpSocket->disconnectFromHost();
                        tcpSocket->close();
                    }
                }
            }
            );
}

clientwidget::~clientwidget()
{
    delete ui;
}

void clientwidget::on_pushButton_clicked()
{
    QString ip = ui->lineEditIP->text();
    quint16 port = ui->lineEditPort->text().toInt();

    tcpSocket->connectToHost(QHostAddress(ip),port);
}
