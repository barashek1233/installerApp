#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QScopedPointer>
#include <QTextStream>
#include <QDateTime>
#include <QLoggingCategory>

QScopedPointer<QFile>   logFile;

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    logFile.reset(new QFile("./tia.log"));
    logFile.data()->open(QFile::Append | QFile::Text | QFile::Truncate);

    qInstallMessageHandler(messageHandler);

    MainWindow w;
    w.show();

    return a.exec();
}

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QTextStream out(logFile.data());

    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");

    switch (type)
    {
        case QtInfoMsg:     out << "INF "; break;
        case QtDebugMsg:    out << "DBG "; break;
        case QtWarningMsg:  out << "WRN "; break;
        case QtCriticalMsg: out << "CRT "; break;
        case QtFatalMsg:    out << "FTL "; break;
    }

#ifdef UBUNTU
    out << context.category << ": " << msg << endl;
#else
    out << context.category << ": " << msg << Qt::endl;
#endif

    out.flush();    // Clear the buffered data
}
