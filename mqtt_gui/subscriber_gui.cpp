#include "subscriber_gui.h"
#include <QtMqtt/QMqttTopicFilter>
#include <QHBoxLayout>
#include <QLabel>
#include <QDateTime>

SubscriberGui::SubscriberGui(QWidget *parent)
    : CommonWidget(parent)
    , m_subscribed(false)
{
    setWindowTitle("MQTT Subscriber");
    
    // 구독 버튼
    QHBoxLayout *subscribeLayout = new QHBoxLayout;
    m_subscribeBtn = new QPushButton("Subscribe");
    m_subscribeBtn->setEnabled(false);
    subscribeLayout->addWidget(m_subscribeBtn);
    subscribeLayout->addStretch();
    m_mainLayout->addLayout(subscribeLayout);
    
    // 메시지 출력
    m_messagesEdit = new QTextEdit;
    m_messagesEdit->setReadOnly(true);
    m_mainLayout->addWidget(new QLabel("Received Messages:"));
    m_mainLayout->addWidget(m_messagesEdit);
    
    connect(m_subscribeBtn, &QPushButton::clicked, this, &SubscriberGui::onSubscribeClicked);
    connect(m_client, &QMqttClient::messageReceived, this, &SubscriberGui::onMessageReceived);
    
    resize(400, 400);
}

void SubscriberGui::onConnected()
{
    CommonWidget::onConnected();
    m_subscribeBtn->setEnabled(true);
    m_subscribed = false;
    m_messagesEdit->append(QString("[%1] Connected to broker").arg(QDateTime::currentDateTime().toString("hh:mm:ss")));
}

void SubscriberGui::onSubscribeClicked()
{
    QString topic = m_topicEdit->text().trimmed();
    if (topic.isEmpty()) return;
    
    if (!m_subscribed && m_client->state() == QMqttClient::Connected) {
        auto subscription = m_client->subscribe(QMqttTopicFilter(topic));
        if (subscription) {
            m_subscribed = true;
            m_subscribeBtn->setText("Unsubscribe");
            m_messagesEdit->append(QString("[%1] Subscribed to: %2")
                                 .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                                 .arg(topic));
        }
    } else if (m_subscribed) {
        m_client->unsubscribe(QMqttTopicFilter(topic));
        m_subscribed = false;
        m_subscribeBtn->setText("Subscribe");
        m_messagesEdit->append(QString("[%1] Unsubscribed from: %2")
                             .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                             .arg(topic));
    }
}

void SubscriberGui::onMessageReceived(const QByteArray &message, const QMqttTopicName &topic)
{
    m_messagesEdit->append(QString("[%1] %2: %3")
                          .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                          .arg(topic.name())
                          .arg(QString::fromUtf8(message)));
}