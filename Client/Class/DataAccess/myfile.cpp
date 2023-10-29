#include "myfile.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>

MyFile::MyFile()
{
    QDir dir("my");
    if(!dir.exists()){
        dir.mkpath("../my");
    }
}


QString MyFile::ipPort()
{
    QString ipPort = "";
    ipPort = ipPort + "192.168.31.125" + '\n' + "10523";
    QFile file("my/ipPort.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    if(file.isOpen()){
        ipPort = file.readAll();
        file.close();
    }else if(file.exists() == false){
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        file.write(ipPort.toUtf8());
        file.close();
    }
    return ipPort;
}


void MyFile::setIpPort(const QString &ip, const QString &port)
{
    QFile file("my/ipPort.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QString text = ip + '\n' + port;
    file.write(text.toUtf8());
    file.close();
}


void MyFile::initMessageDir(const QString &no)
{
    QString path = "my/" + no + "/Messages";
    QDir dir(path);
    if(!dir.exists()){
        dir.mkpath("../Messages");
    }
}

/*
void MyFile::initMessFile(const QString &myNo, const QVector<NoAName> &noANames)
{
    QString path = "my/" + myNo + "/Messages";
    QDir dir(path);
    if(!dir.exists()){
        dir.mkpath("../Messages");
    }

    //若没有该好友的记事本则创建一个
    QVector<QString> fileNames = dir.entryList(QDir::AllEntries | QDir::NoDotAndDotDot);
    for(int i=0; i<noANames.size(); i++){
        QString path = dir.path() + '/' + noANames.at(i).no() + ".txt";
        QFile file(path);
        if(file.exists() == false){
            file.open(QIODevice::WriteOnly | QIODevice::Text);
            file.close();
        }
        fileNames.removeOne(noANames.at(i).no() + ".txt");
    }

    //若记事本或文件夹多了则删除（ 主要是删除好友时删除聊天记录 ）
    for(int i=0; i<fileNames.size(); i++){
        QString path = dir.path() + '/' + fileNames.at(i);
        QFileInfo fileInfo(path);
        if(fileInfo.isFile()){
            QFile::remove(path);
        }else if(fileInfo.isDir()){
            QDir(path).removeRecursively();
        }
    }
}*/


void MyFile::appendMessage(const QString &myNo, const Message &message)
{
    QString path = "my/" + myNo + "/Messages/";
    QString text = "";
    QString sender = message.sender();
    QString receiver = message.receiver();
    text = text + sender + '\n';
    text = text + receiver + '\n';
    text = text + message.date() + '\n';
    text = text + message.text() + "\n\n";

    QString tmpPath ="";
    if(sender == myNo){
        tmpPath = path + receiver + ".txt";
    }else{
        tmpPath = path + sender + ".txt";
    }
    QFile file(tmpPath);
    if(file.exists() == false){
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        file.close();
    }
    file.open(QIODevice::Append | QIODevice::Text);
    file.write(text.toUtf8());
    file.close();
}


QVector<Message> MyFile::getMessages(const QString &myNo, const QString &no)
{
    QVector<Message> messages;
    QString path = "my/" + myNo + "/Messages/";
    path = path + no + ".txt";
    QFile file(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    while(!file.atEnd()){
        Message message;
        message.setSender(file.readLine().trimmed());
        message.setReceiver(file.readLine().trimmed());
        message.setDate(file.readLine().trimmed());
        message.setText(file.readLine().trimmed());
        QString tmp = file.readLine();
        messages.push_back(message);
    }
    file.close();
    return messages;
}

