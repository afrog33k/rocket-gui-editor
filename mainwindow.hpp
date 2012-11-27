#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

#include "rmlsyntaxhighlighter.hpp"

namespace Ui {
class CMainWindow;
}

class CMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit CMainWindow(QWidget *parent = 0);
    ~CMainWindow();
    
private:
    Ui::CMainWindow *ui;

    CRMLSyntaxHighlighter* mHighlighter;

private slots:
    void LoadRMLDocument();
};

#endif // MAINWINDOW_HPP
