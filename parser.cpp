#include "parser.h"

Parser::Parser(QObject *parent) : QObject{parent}
{
    qInfo(log_Parser()) << "Create Parser";

    python_script_path = "./parser.py";
    python_venv_path = "./venv_python/bin/python";

    qInfo(log_Parser()) << "Set parser script: " << python_script_path;
    qInfo(log_Parser()) << "Set python env: " << python_venv_path;

    parse_process = new QProcess(this);

    input_archive_path = "";

    confirm_message.setText("Configuration has been modified.");

    connect(parse_process, SIGNAL(finished(int)), &(this->confirm_message), SLOT(exec()));

    connect(parse_process, SIGNAL(started()), this, SIGNAL(parse_Started()));
    connect(parse_process, SIGNAL(finished(int)), this, SIGNAL(parse_Finished()));

    connect(parse_process, SIGNAL(errorOccurred(QProcess::ProcessError)), this, SLOT(parse_Error(QProcess::ProcessError)));
}

Parser::~Parser()
{
    disconnect(parse_process, SIGNAL(started()), this, SIGNAL(parse_Started()));
    disconnect(parse_process, SIGNAL(finished(int)), this, SIGNAL(parse_Finished()));

    disconnect(parse_process, SIGNAL(errorOccurred(QProcess::ProcessError)), this, SLOT(parse_Error(QProcess::ProcessError)));

    disconnect(parse_process, SIGNAL(finished(int)), &(this->confirm_message), SLOT(exec()));
}

void Parser::set_InputArchivePath(QString path)
{
    qInfo(log_Parser()) << "Set parse archive path:" << path;

    input_archive_path = path;
}

void Parser::parse_Archive()
{
    qInfo(log_Parser()) << "Start parse process";

    parse_process->start(python_venv_path, QStringList() << python_script_path << "--arch_path" << input_archive_path);
}

void Parser::set_MainPath(QString path)
{
    python_venv_path = path + "/venv_python/bin/python";
    python_script_path = path + "/parser.py";
}

void Parser::parse_Error(QProcess::ProcessError error)
{
    qCritical(log_Parser()) << "Parse process is stoped with " << error << "error code";
}
