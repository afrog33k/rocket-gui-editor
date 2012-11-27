#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QFile>
#include <QTextCodec>
#include <QFileDialog>

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMainWindow)
{
    ui->setupUi(this);
    mHighlighter = new CRMLSyntaxHighlighter(ui->MainTextEdit->document());

}

CMainWindow::~CMainWindow()
{
    delete ui;
}

void CMainWindow::LoadRMLDocument()
{
    QString FileName = QFileDialog::getOpenFileName(this, tr("Open File..."),
                                                    QString(), tr("RML-Files (*.rml);;All Files (*)"));
    if (!QFile::exists(FileName))
    {
        ui->LogBrowser->append("File does not exist!");
        return;
    }
     QFile File(FileName);
     if (!File.open(QFile::ReadOnly))
     {
         ui->LogBrowser->append("Couldn't open file!");
         return;
     }

     QByteArray Data = File.readAll();
     QTextCodec *Codec = Qt::codecForHtml(Data);
     QString Str = Codec->toUnicode(Data);
     Str = QString::fromLocal8Bit(Data);
     ui->MainTextEdit->setPlainText(Str);
}
