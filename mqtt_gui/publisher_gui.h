#ifndef PUBLISHER_GUI_H
#define PUBLISHER_GUI_H

#include "common_widget.h"
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>

class PublisherGui : public CommonWidget
{
    Q_OBJECT

public:
    explicit PublisherGui(QWidget *parent = nullptr);

private slots:
    void onPublishClicked();
    void onMessageEnterPressed();

protected slots:
    void onConnected() override;

private:
    QLineEdit *m_messageEdit;
    QPushButton *m_publishBtn;
    QTextEdit *m_logEdit;
};

#endif // PUBLISHER_GUI_H