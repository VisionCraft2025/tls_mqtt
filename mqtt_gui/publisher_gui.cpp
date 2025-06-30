#include "publisher_gui.h"
#include <QtMqtt/QMqttTopicName>
#include <QHBoxLayout>
#include <QLabel>
#include <QDateTime>

PublisherGui::PublisherGui(QWidget *parent)
    : CommonWidget(parent)
{
    setWindowTitle("MQTT Publisher");
    
    // 메시지 입력
    QHBoxLayout *messageLayout = new QHBoxLayout;
    messageLayout->addWidget(new QLabel("Message:"));
    m_messageEdit = new QLineEdit;
    m_publishBtn = new QPushButton("Publish");
    m_publishBtn->setEnabled(false);
    messageLayout->addWidget(m_messageEdit);
    messageLayout->addWidget(m_publishBtn);
    m_mainLayout->addLayout(messageLayout);
    
    // 로그 출력
    m_logEdit = new QTextEdit;
    m_logEdit->setReadOnly(true);
    m_logEdit->setMaximumHeight(200);
    m_mainLayout->addWidget(new QLabel("Log:"));
    m_mainLayout->addWidget(m_logEdit);
    
    connect(m_publishBtn, &QPushButton::clicked, this, &PublisherGui::onPublishClicked);
    connect(m_messageEdit, &QLineEdit::returnPressed, this, &PublisherGui::onMessageEnterPressed);
    
    resize(400, 350);
}

void PublisherGui::onConnected()
{
    CommonWidget::onConnected();
    m_publishBtn->setEnabled(true);
    m_logEdit->append(QString("[%1] Connected to broker").arg(QDateTime::currentDateTime().toString("hh:mm:ss")));
}

void PublisherGui::onPublishClicked()
{
    QString message = m_messageEdit->text().trimmed();
    QString topic = m_topicEdit->text().trimmed();
    
    if (message.isEmpty() || topic.isEmpty()) return;
    
    if (m_client->state() == QMqttClient::Connected) {
        if (m_client->publish(QMqttTopicName(topic), message.toUtf8()) != -1) {
            m_logEdit->append(QString("[%1] Published to '%2': %3")
                             .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                             .arg(topic)
                             .arg(message));
            m_messageEdit->clear();
        } else {
            m_logEdit->append(QString("[%1] Failed to publish message")
                             .arg(QDateTime::currentDateTime().toString("hh:mm:ss")));
        }
    }
}

void PublisherGui::onMessageEnterPressed()
{
    onPublishClicked();
}