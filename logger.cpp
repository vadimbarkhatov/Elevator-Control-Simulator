#include "logger.h"

QTextEdit* qInfoRedirectTarget = nullptr;

//this is a global class used to redirect qinfo

void msgHandler(QtMsgType msgType, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(msgType)
    Q_UNUSED(context)

    if(qInfoRedirectTarget) {
        QMetaObject::invokeMethod(qInfoRedirectTarget, "append", Qt::QueuedConnection, Q_ARG(QString, msg));
    }
}

void setRedirect(QTextEdit* textEdit)
{
    qInfoRedirectTarget = textEdit;
}
