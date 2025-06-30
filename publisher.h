#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <QObject>
#include <QtMqtt/QMqttClient>
#include <QTextStream>
#include <QSocketNotifier>
#include <QSslConfiguration>

class Publisher : public QObject
{
    Q_OBJECT

public:
    explicit Publisher(QObject *parent = nullptr);
    void connectToBroker();

private slots:
    void onConnected();
    void onDisconnected();
    void onError(QMqttClient::ClientError error);
    void onStateChanged(QMqttClient::ClientState state);
    void readInput();

private:
    QMqttClient *m_client;
    QTextStream *m_stdin;
    QSocketNotifier *m_notifier;
    QSslConfiguration m_sslConfig;
};

#endif // PUBLISHER_H