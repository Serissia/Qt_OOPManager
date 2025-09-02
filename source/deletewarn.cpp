#include "header/deletewarn.h"
#include "ui_deletewarn.h"

DeleteWarn::DeleteWarn(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DeleteWarn)
{
	ui->setupUi(this);
	setWindowTitle(tr("Warning!"));
	setFixedSize(660, 350);
}

DeleteWarn::~DeleteWarn()
{
	delete ui;
}

void DeleteWarn::on_pushButton_clicked()
{
	accept();
}

void DeleteWarn::on_pushButton_2_clicked()
{
	reject();
}
