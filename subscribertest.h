#ifndef SUBSCRIBERTEST_H
#define SUBSCRIBERTEST_H

#include <QQuickItem>
#include <QDebug>
#include <nzmqt/nzmqt.hpp>

class SubscriberTest : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString message READ message NOTIFY messageChanged)
    QString m_message;

public:
    explicit SubscriberTest(QQuickItem *parent = 0);

QString message() const
{
    return m_message;
}

signals:

void messageChanged(QString arg);

public slots:
    void pingReceived(const QList<QByteArray>& message);

};

#endif // SUBSCRIBERTEST_H
