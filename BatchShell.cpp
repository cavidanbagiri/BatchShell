#include "BatchShell.h"

BatchShell::BatchShell(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

void BatchShell::OpenCMDMainClass()
{
    cmdmainclass_obj = new CMDMainClass();
    cmdmainclass_obj->show();
}

void BatchShell::on_OpenBTN_clicked()
{
    OpenCMDMainClass();
    this->hide();
}



