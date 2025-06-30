#include "publisher.h"
#include <QDebug>
#include <QCoreApplication>
#include <QtMqtt/QMqttTopicName>
#include <QSslSocket>
#include <QSslConfiguration>
#include <QSslCertificate>
#include <QFile>
#include <iostream>

Publisher::Publisher(QObject *parent)
    : QObject(parent)
    , m_client(new QMqttClient(this))
    , m_stdin(new QTextStream(stdin))
    , m_notifier(new QSocketNotifier(fileno(stdin), QSocketNotifier::Read, this))
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
    
    connect(m_client, &QMqttClient::connected, this, &Publisher::onConnected);
    connect(m_client, &QMqttClient::disconnected, this, &Publisher::onDisconnected);
    connect(m_client, &QMqttClient::errorChanged, this, &Publisher::onError);
    connect(m_client, &QMqttClient::stateChanged, this, &Publisher::onStateChanged);
    connect(m_notifier, &QSocketNotifier::activated, this, &Publisher::readInput);
}

void Publisher::connectToBroker()
{
    qDebug() << "Publisher connecting to MQTT broker:" << m_client->hostname();
    m_client->connectToHostEncrypted(m_sslConfig);
}

void Publisher::onConnected()
{
    qDebug() << "Publisher connected to MQTT broker";
    std::cout << "Enter messages to publish (type 'quit' to exit):" << std::endl;
    std::cout << "> " << std::flush;
}

void Publisher::onDisconnected()
{
    qDebug() << "Publisher disconnected from MQTT broker";
    QCoreApplication::quit();
}

void Publisher::onError(QMqttClient::ClientError error)
{
    qDebug() << "MQTT Client Error:" << error;
}

void Publisher::onStateChanged(QMqttClient::ClientState state)
{
    qDebug() << "MQTT Client State:" << state;
}

void Publisher::readInput()
{
    QString input = m_stdin->readLine().trimmed();
    
    if (input == "quit") {
        m_client->disconnectFromHost();
        return;
    }
    
    if (!input.isEmpty()) {
        if (m_client->state() == QMqttClient::Connected) {
            if (m_client->publish(QMqttTopicName("test/topic"), input.toUtf8()) != -1) {
                qDebug() << "Published:" << input;
            } else {
                qDebug() << "Failed to publish message";
            }
        } else {
            qDebug() << "Not connected to broker. Current state:" << m_client->state();
        }
    }
    
    std::cout << "> " << std::flush;
}