#include "subscribertest.h"

SubscriberTest::SubscriberTest(QQuickItem *parent) :
    QQuickItem(parent)
{
    m_message = "None";

    nzmqt::ZMQContext* context = nzmqt::createDefaultContext(this);

    context->start();

    nzmqt::ZMQSocket *socket = context->createSocket(nzmqt::ZMQSocket::TYP_SUB, this);
    socket->setObjectName("Subscriber.Socket.socket(SUB)");
    connect(socket, SIGNAL(messageReceived(QList<QByteArray>)),
            this, SLOT(pingReceived(QList<QByteArray>)));

    socket->subscribeTo("foo");
    socket->subscribeTo("demo");
    socket->connectTo("tcp://192.168.1.12:4711");
}

void SubscriberTest::pingReceived(const QList<QByteArray> &message)
{
    QString newMessage;

    foreach (QByteArray bytes, message)
    {
        newMessage.append(QString(bytes) + ", ");
    }

    qDebug() << newMessage;

    m_message = newMessage;
    emit messageChanged(m_message);
}
