#pragma once

#include <QtWidgets/QMainWindow>
#include <qpushbutton.h>
#include <QDebug>
#include <qwidget.h>
#include "ui_BatchShell.h"
#include "CMDMainClass.h"

using namespace std;

class BatchShell : public QMainWindow
{
    Q_OBJECT

public:
    BatchShell(QWidget *parent = Q_NULLPTR);

private:
    Ui::BatchShellClass ui;

    //Creating an object CMDMainClass for opening
    CMDMainClass* cmdmainclass_obj = nullptr;

    //Calling func For Opening cmdmainclass
    void OpenCMDMainClass();

private slots:

    //for opening main Command Prompt Window
    void on_OpenBTN_clicked();

};
