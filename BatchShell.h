#pragma once

#include <QtWidgets/QMainWindow>
#include <qpushbutton.h>
#include <QDebug>
#include <qwidget.h>
#include <qtabwidget.h>
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


    //***************************************************** User Defined Member ********************************
    CMDMainClass* cmdmainclass_obj = nullptr;//For Opening Batch Class                                     //***
    //**********************************************************************************************************
    
    //***************************************************** User Defined Method ********************************
    void startBatchClassAsDefault();                                                                       //***
    //**********************************************************************************************************

private slots:

    //***************************************************** User Defined Method ********************************
    void closeTab(const int& index);//for closing tab widget											   //***
    void on_actionBatch_triggered();//for opening batch class from menu                                    //*** 
    //**********************************************************************************************************


};
