#ifndef COMMON_WIDGET_H
#define COMMON_WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QtMqtt/QMqttClient>
#include <QSslConfiguration>

class CommonWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CommonWidget(QWidget *parent = nullptr);
    
protected:
    void setupUI();
    void setupMqttClient();
    QSslConfiguration loadSslConfig();
    
protected slots:
    void onConnectClicked();
    void onDisconnectClicked();
    virtual void onConnected();
    void onDisconnected();
    void onError(QMqttClient::ClientError error);
    
protected:
    QMqttClient *m_client;
    QLineEdit *m_topicEdit;
    QPushButton *m_connectBtn;
    QPushButton *m_disconnectBtn;
    QLabel *m_statusLabel;
    QVBoxLayout *m_mainLayout;
    
    QString m_hostname;
    int m_port;
};

#endif // COMMON_WIDGET_H