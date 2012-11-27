/**********************************************************************************
 * License notice
 * ------------------------
 * mainwindow.cpp
 * ------------------------
 * Copyright (c) 2012 Alexander Kasper (alexander.limubei.kasper@gmail.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 ***********************************************************************************/

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

    mGUIVizDock = new QDockWidget("GUI Viz", this);
    mGUIVizDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    mRenderWidget = new CRenderWidget(ui->centralWidget);
    mGUIVizDock->setWidget(mRenderWidget);
    mGUIVizDock->setMinimumWidth(400);
    addDockWidget(Qt::RightDockWidgetArea, mGUIVizDock);
}

CMainWindow::~CMainWindow()
{
    delete ui;
    delete mHighlighter;
    delete mRenderWidget;
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

    mRenderWidget->LoadDocument(FileName);
}
