#include "BatchShell.h"

BatchShell::BatchShell(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    startBatchClassAsDefault();
}

//***************************************************** User Slot Defined Method ***************************

void BatchShell::closeTab(const int& index){ui.tabWidget->removeTab(index);}

void BatchShell::on_actionBatch_triggered()
{//clicked from item menu for opening Batch Class
    delete cmdmainclass_obj;
    cmdmainclass_obj = new CMDMainClass();
    ui.tabWidget->addTab(cmdmainclass_obj, "BATCH");
}

//***************************************************** User Defined Method ********************************

void BatchShell::startBatchClassAsDefault()
{//this func will work first time in this class
    ui.tabWidget->setTabsClosable(true);									//Can Close TabWidget		 ***
    ui.tabWidget->setMovable(true);											//Can Move Tab Icon			 ***				
    ui.tabWidget->setMouseTracking(true);								    //Set Highlightes for mouse  ***
    connect(ui.tabWidget, SIGNAL(tabCloseRequested(int)),					//When CLicked this func work***
        this, SLOT(closeTab(int)));//Closing Icon			
    cmdmainclass_obj = new CMDMainClass();
    ui.tabWidget->addTab(cmdmainclass_obj, "BATCH");
}


