#include "subscriber.h"
#include <QDebug>
#include <QCoreApplication>
#include <QtMqtt/QMqttTopicName>
#include <QtMqtt/QMqttTopicFilter>
#include <QSslSocket>
#include <QSslConfiguration>
#include <QSslCertificate>
#include <QFile>
#include <iostream>

Subscriber::Subscriber(QObject *parent)
    : QObject(parent)
    , m_client(new QMqttClient(this))
{
    m_client->setHostname("mqtt.kwon.pics");
    m_client->setPort(8883);
    
    // SSL 설정
    QSslConfiguration sslConfig = QSslConfiguration::defaultConfiguration();
    
    // CA 인증서 로드
    QFile caFile("ca.crt");
    if (caFile.open(QIODevice::ReadOnly)) {
        QSslCertificate caCert(&caFile, QSsl::Pem);
        if (!caCert.isNull()) {
            sslConfig.setCaCertificates({caCert});
            qDebug() << "CA certificate loaded successfully";
        } else {
            qDebug() << "Failed to load CA certificate";
        }
        caFile.close();
    } else {
        qDebug() << "Could not open ca.crt file";
    }
    
    // SSL 설정 저장
    m_sslConfig = sslConfig;
    
    connect(m_client, &QMqttClient::connected, this, &Subscriber::onConnected);
    connect(m_client, &QMqttClient::disconnected, this, &Subscriber::onDisconnected);
    connect(m_client, &QMqttClient::messageReceived, this, &Subscriber::onMessageReceived);
}

void Subscriber::connectToBroker()
{
    qDebug() << "Subscriber connecting to MQTT broker:" << m_client->hostname();
    m_client->connectToHostEncrypted(m_sslConfig);
}

void Subscriber::onConnected()
{
    qDebug() << "Subscriber connected to MQTT broker";
    
    auto subscription = m_client->subscribe(QMqttTopicFilter("test/topic"));
    if (!subscription) {
        qDebug() << "Could not subscribe to topic";
        return;
    }
    
    qDebug() << "Subscribed to test/topic";
    std::cout << "Waiting for messages..." << std::endl;
}

void Subscriber::onDisconnected()
{
    qDebug() << "Subscriber disconnected from MQTT broker";
    QCoreApplication::quit();
}

void Subscriber::onMessageReceived(const QByteArray &message, const QMqttTopicName &)
{
    std::cout << "[broker] " << message.toStdString() << std::endl;
}