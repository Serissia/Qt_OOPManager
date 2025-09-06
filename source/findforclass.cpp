#include "header/findforclass.h"
#include "ui_findforclass.h"

FindForClass::FindForClass(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::FindForClass)
{
	ui->setupUi(this);
	setWindowTitle(tr("查找类"));
	setFixedSize(600, 400);
	ui->spinBox->setEnabled(false);
	ui->lineEdit->setEnabled(false);
	ui->radioButton->setChecked(true);
}

FindForClass::~FindForClass()
{
	delete ui;
}

int FindForClass::Num()
{
	return ui->spinBox->value();
}

QString FindForClass::Name()
{
	return ui->lineEdit->text();
}

int FindForClass::Chosen()
{
	return ui->radioButton->isChecked() ? 1 : 2;
}

void FindForClass::on_pushButton_2_clicked()
{
	reject();
}

void FindForClass::on_pushButton_clicked()
{
	accept();
}

//void FindForClass::on_groupBox_toggled(bool arg1)
//{
//	if(arg1) ui->pushButton->setEnabled(true);
//	else ui->pushButton->setEnabled(false);
//}

void FindForClass::on_radioButton_toggled(bool checked)
{
	if(checked) ui->spinBox->setEnabled(true);
	else ui->spinBox->setEnabled(false);
}

void FindForClass::on_radioButton_2_toggled(bool checked)
{
	if(checked) ui->lineEdit->setEnabled(true);
	else ui->lineEdit->setEnabled(false);
}
