#include "common_widget.h"
#include <QSslSocket>
#include <QSslCertificate>
#include <QFile>
#include <QDebug>

CommonWidget::CommonWidget(QWidget *parent)
    : QWidget(parent)
    , m_client(nullptr)
    , m_hostname("mqtt.kwon.pics")
    , m_port(8883)
{
    setupUI();
    setupMqttClient();
}

void CommonWidget::setupUI()
{
    m_mainLayout = new QVBoxLayout(this);
    
    // 토픽 입력
    QHBoxLayout *topicLayout = new QHBoxLayout;
    topicLayout->addWidget(new QLabel("Topic:"));
    m_topicEdit = new QLineEdit("test/topic");
    topicLayout->addWidget(m_topicEdit);
    m_mainLayout->addLayout(topicLayout);
    
    // 연결 버튼
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    m_connectBtn = new QPushButton("Connect");
    m_disconnectBtn = new QPushButton("Disconnect");
    m_disconnectBtn->setEnabled(false);
    buttonLayout->addWidget(m_connectBtn);
    buttonLayout->addWidget(m_disconnectBtn);
    m_mainLayout->addLayout(buttonLayout);
    
    // 상태 표시
    m_statusLabel = new QLabel("Disconnected");
    m_statusLabel->setStyleSheet("color: red;");
    m_mainLayout->addWidget(m_statusLabel);
    
    connect(m_connectBtn, &QPushButton::clicked, this, &CommonWidget::onConnectClicked);
    connect(m_disconnectBtn, &QPushButton::clicked, this, &CommonWidget::onDisconnectClicked);
}

void CommonWidget::setupMqttClient()
{
    m_client = new QMqttClient(this);
    m_client->setHostname(m_hostname);
    m_client->setPort(m_port);
    
    connect(m_client, &QMqttClient::connected, this, &CommonWidget::onConnected);
    connect(m_client, &QMqttClient::disconnected, this, &CommonWidget::onDisconnected);
    connect(m_client, &QMqttClient::errorChanged, this, &CommonWidget::onError);
}

QSslConfiguration CommonWidget::loadSslConfig()
{
    QSslConfiguration sslConfig = QSslConfiguration::defaultConfiguration();
    
    QFile caFile("ca.crt");
    if (caFile.open(QIODevice::ReadOnly)) {
        QSslCertificate caCert(&caFile, QSsl::Pem);
        if (!caCert.isNull()) {
            sslConfig.setCaCertificates({caCert});
            qDebug() << "CA certificate loaded successfully";
        }
        caFile.close();
    }
    
    return sslConfig;
}

void CommonWidget::onConnectClicked()
{
    m_client->connectToHostEncrypted(loadSslConfig());
    m_connectBtn->setEnabled(false);
    m_statusLabel->setText("Connecting...");
    m_statusLabel->setStyleSheet("color: orange;");
}

void CommonWidget::onDisconnectClicked()
{
    m_client->disconnectFromHost();
}

void CommonWidget::onConnected()
{
    m_connectBtn->setEnabled(false);
    m_disconnectBtn->setEnabled(true);
    m_statusLabel->setText("Connected");
    m_statusLabel->setStyleSheet("color: green;");
}

void CommonWidget::onDisconnected()
{
    m_connectBtn->setEnabled(true);
    m_disconnectBtn->setEnabled(false);
    m_statusLabel->setText("Disconnected");
    m_statusLabel->setStyleSheet("color: red;");
}

void CommonWidget::onError(QMqttClient::ClientError error)
{
    qDebug() << "MQTT Error:" << error;
    m_statusLabel->setText("Error: " + QString::number(error));
    m_statusLabel->setStyleSheet("color: red;");
}