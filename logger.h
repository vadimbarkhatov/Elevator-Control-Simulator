#ifndef LOGGER_H
#define LOGGER_H

#include <QtWidgets>

extern QTextEdit* qInfoRedirectTarget;

void setRedirect(QTextEdit* label);
void msgHandler(QtMsgType msgType, const QMessageLogContext &context, const QString &msg);

#endif // LOGGER_H
