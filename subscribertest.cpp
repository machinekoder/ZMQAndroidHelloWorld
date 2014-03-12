#include "subscribertest.h"
#include "testmsg.pb.h"

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
    QString topic;
    QByteArray data;
    pb::Container container;

    if (message.size() != 2)    // we should receive topic and encoded protobuf string
    {
        return;
    }

    topic = QString(message.at(0));
    data = message.at(1);

    container.ParseFromArray(data.data(), data.size());

    int pinCount;
    int noteCount;

    pinCount = container.pin_size();
    noteCount = container.note_size();

    for (int i = 0; i < pinCount; ++i)
    {
        newMessage.append(QString("Pin: %1\n").arg(QString::fromStdString(container.pin(i).name())));
        switch (container.pin(i).type())
        {
            case pb::HAL_BIT:   newMessage.append(QString("bit: %1\n").arg(container.pin(i).halbit())); break;
            case pb::HAL_FLOAT: newMessage.append(QString("float: %1\n").arg(container.pin(i).halfloat())); break;
            case pb::HAL_S32:   newMessage.append(QString("s32: %1\n").arg(container.pin(i).hals32())); break;
            case pb::HAL_U32:   newMessage.append(QString("u32: %1\n").arg(container.pin(i).halu32())); break;
        }
    }

    for (int i = 0; i < noteCount; ++i)
    {
        newMessage.append(QString("Note: %1\n").arg(QString::fromStdString(container.note(i))));
    }
    qDebug() << newMessage;

    m_message = newMessage;
    emit messageChanged(m_message);
}
