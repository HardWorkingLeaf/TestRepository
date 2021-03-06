#include <QCoreApplication>
#include <QDebug>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QString>
#include <iostream>

using namespace std;

void sslPost(string url, string strData)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager;
    QNetworkRequest request;
    QByteArray line;
    QEventLoop eventLoop;
    QSslConfiguration conf = request.sslConfiguration();
    conf.setPeerVerifyMode(QSslSocket::VerifyNone); //证书选项
    conf.setProtocol(QSsl::TlsV1SslV3); //协议，建议用这个TLS与SSL通用的
    request.setSslConfiguration(conf);
    request.setUrl(QUrl(url.c_str()));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("X-AUTH-OID", "3DzedgMnCc1Vtys9t");
    QByteArray append(strData.c_str());
    QNetworkReply* reply = manager->post(request,append);
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    eventLoop.exec();
    line = reply->readAll();

    qDebug() << "response:" << line;

//    reply->deleteLater();
//    delete manager;

//return line.toStdString();
}

QJsonObject sslGetConfig(string url)
{
//    string data = sslPost(url, "");

//    cout << data << endl;

}

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    sslPost("https://192.168.100.88:8089/pdio_collect/iansConfig/query","");



    exit(0);
    return a.exec();
}
