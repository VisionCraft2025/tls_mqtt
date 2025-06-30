#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <QObject>
#include <QtMqtt/QMqttClient>
#include <QSslConfiguration>

class Subscriber : public QObject
{
    Q_OBJECT

public:
    explicit Subscriber(QObject *parent = nullptr);
    void connectToBroker();

private slots:
    void onConnected();
    void onDisconnected();
    void onMessageReceived(const QByteArray &message, const QMqttTopicName &topic);

private:
    QMqttClient *m_client;
    QSslConfiguration m_sslConfig;
};

#endif // SUBSCRIBER_H