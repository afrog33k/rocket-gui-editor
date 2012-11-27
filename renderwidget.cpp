/**********************************************************************************
 * License notice
 * ------------------------
 * renderwidget.cpp
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

#include "renderwidget.hpp"

#include <Rocket/Controls.h>
#include <Rocket/Debugger.h>

CRenderWidget::CRenderWidget(QWidget *parent) :
    QGLWidget(parent),
    mRenderInterface(new ShellRenderInterfaceOpenGL()),
    mSystemInterface(new CQtSystemInterface())
{
    setMouseTracking(true);
    Rocket::Core::SetRenderInterface(mRenderInterface);
    Rocket::Core::SetSystemInterface(mSystemInterface);

    Rocket::Core::Initialise();

    qDebug("Creating Rocket context...");
    Rocket::Core::Vector2i size(width(), height());
    mGUIContext = Rocket::Core::CreateContext("Main", size);
    Rocket::Controls::Initialise();
    Rocket::Debugger::Initialise(mGUIContext);
    Rocket::Debugger::SetVisible(true);
    qDebug("done!\n");
}

CRenderWidget::~CRenderWidget()
{
    mGUIContext->RemoveReference();
    Rocket::Core::Shutdown();
    delete mRenderInterface;
    delete mSystemInterface;
}

bool CRenderWidget::LoadDocument(QString FileName)
{

    Rocket::Core::String fn(FileName.toAscii());

    Rocket::Core::ElementDocument* doc = mGUIContext->LoadDocument(fn);
    if(!doc)
    {
        mGUIContext->UnloadAllDocuments();
    }
    else
        doc->Show();

    this->repaint();

    return (doc != NULL);
}

void CRenderWidget::initializeGL()
{
    // Set up the GL state.
    glClearColor(0, 0, 0, 1);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width(), height(), 0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void CRenderWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, h, 0, -1, 1); // set origin to bottom left corner
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    mGUIContext->SetDimensions(Rocket::Core::Vector2i(w,h));

    mGUIContext->Update();
    mGUIContext->Render();
}

void CRenderWidget::paintGL()
{
    mGUIContext->Update();
    mGUIContext->Render();
}

void CRenderWidget::mousePressEvent(QMouseEvent* evt)
{

}

void CRenderWidget::mouseMoveEvent(QMouseEvent* evt)
{

}

void CRenderWidget::keyPressEvent(QKeyEvent* evt)
{

}
