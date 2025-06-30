#ifndef SUBSCRIBER_GUI_H
#define SUBSCRIBER_GUI_H

#include "common_widget.h"
#include <QTextEdit>
#include <QPushButton>

class SubscriberGui : public CommonWidget
{
    Q_OBJECT

public:
    explicit SubscriberGui(QWidget *parent = nullptr);

private slots:
    void onSubscribeClicked();
    void onMessageReceived(const QByteArray &message, const QMqttTopicName &topic);

protected slots:
    void onConnected() override;

private:
    QPushButton *m_subscribeBtn;
    QTextEdit *m_messagesEdit;
    bool m_subscribed;
};

#endif // SUBSCRIBER_GUI_H