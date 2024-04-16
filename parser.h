#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QProcess>
#include <QMessageBox>
#include <QDebug>

#include "loger.h"

class Parser : public QObject
{
    Q_OBJECT

public:
    explicit Parser(QObject *parent = nullptr);
    ~Parser();

    void set_InputArchivePath(QString path);
    void parse_Archive();

signals:
    void parse_Started();
    void parse_Finished();

public slots:
    void set_MainPath(QString path);

private slots:
    void parse_Error(QProcess::ProcessError);

private:
    QString python_script_path;
    QString python_venv_path;

    QProcess* parse_process;

    QString input_archive_path;
    QString folder_path;

    QMessageBox confirm_message;
};

#endif // PARSER_H
