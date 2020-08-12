#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include<QTcpSocket>
#include<QFile>
namespace Ui {
class clientwidget;
}

class clientwidget : public QWidget
{
    Q_OBJECT

public:
    explicit clientwidget(QWidget *parent = nullptr);
    ~clientwidget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::clientwidget *ui;
    QTcpSocket *tcpSocket;
    QString fileName;
    qint64 fileSize;
    qint64 receiveSize;
    bool isStart;
    QFile file;
};

#endif // CLIENTWIDGET_H
