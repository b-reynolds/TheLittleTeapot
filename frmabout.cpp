#include "frmabout.h"
#include "ui_frmabout.h"

FrmAbout::FrmAbout(QWidget *parent) : QMainWindow(parent), ui(new Ui::FrmAbout)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
}

FrmAbout::~FrmAbout()
{
    delete ui;
}

void FrmAbout::on_btnClose_clicked()
{
    close();
}
