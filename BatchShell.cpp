#include "BatchShell.h"

BatchShell::BatchShell(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    startBatchClassAsDefault();
}

//***************************************************** User Slot Defined Method ***************************

void BatchShell::closeTab(const int& index){ui.tabWidget->removeTab(index);}


//***************************************************** User Defined Method ********************************

void BatchShell::startBatchClassAsDefault()
{

    ui.tabWidget->setTabsClosable(true);									//Can Close TabWidget		***
    ui.tabWidget->setMovable(true);											//Can Move Tab Icon			***				
    ui.tabWidget->setMouseTracking(true);								    //Set Highlightes for mouse ***
    connect(ui.tabWidget, SIGNAL(tabCloseRequested(int)),					//						    ***
        this, SLOT(closeTab(int)));//Closing Icon			
    cmdmainclass_obj = new CMDMainClass();
    ui.tabWidget->addTab(cmdmainclass_obj, "BATCH");
}
