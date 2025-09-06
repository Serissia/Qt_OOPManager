#include "header/findformember.h"
#include "ui_findformember.h"

FindForMember::FindForMember(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::FindForMember)
{
	ui->setupUi(this);
	setWindowTitle(tr("查找类成员"));
	setFixedSize(600, 600);
	ui->radioButton->setChecked(true);
	ui->lineEdit->setEnabled(false);
	ui->comboBox->setEnabled(false);
	ui->comboBox_2->setEnabled(false);
}

FindForMember::~FindForMember()
{
	delete ui;
}

void FindForMember::on_pushButton_clicked()
{
	accept();
}

void FindForMember::on_pushButton_2_clicked()
{
	reject();
}

int FindForMember::getChosen()
{
	if(ui->radioButton->isChecked()) return 0;
	else if(ui->radioButton_2->isChecked()) return 1;
	else if(ui->radioButton_3->isChecked()) return 2;
	else return 3;
}

int FindForMember::Num()
{
	return ui->spinBox->value();
}

QString FindForMember::Name()
{
	return ui->lineEdit->text();
}

QString FindForMember::MemType()
{
	return ui->comboBox->currentText();
}

QString FindForMember::Acc()
{
	return ui->comboBox_2->currentText();
}

void FindForMember::on_radioButton_toggled(bool checked)
{
	if(checked) ui->spinBox->setEnabled(true);
	else ui->spinBox->setEnabled(false);
}

void FindForMember::on_radioButton_2_toggled(bool checked)
{
	if(checked) ui->lineEdit->setEnabled(true);
	else ui->lineEdit->setEnabled(false);
}

void FindForMember::on_radioButton_3_toggled(bool checked)
{
	if(checked) ui->comboBox->setEnabled(true);
	else ui->comboBox->setEnabled(false);
}

void FindForMember::on_radioButton_4_toggled(bool checked)
{
	if(checked) ui->comboBox_2->setEnabled(true);
	else ui->comboBox_2->setEnabled(false);
}
