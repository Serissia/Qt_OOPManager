#include "header/newclassdialog.h"
#include "ui_newclassdialog.h"

newClassDialog::newClassDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::newClassDialog)
{
	ui->setupUi(this);
	setWindowTitle(tr("新建类"));
}

newClassDialog::~newClassDialog()
{
	delete ui;
}

int newClassDialog::number()
{
	return ui->spinBox->value();
}

QString newClassDialog::className()
{
	return ui->lineClass->text();
}

QString newClassDialog::baseClassName()
{
	return ui->lineBase->text();
}

QDate newClassDialog::createdDate()
{
	return ui->dateEdit->date();
}

QString newClassDialog::function()
{
	return ui->lineFunc->text();
}

QString newClassDialog::author()
{
	return ui->lineAuth->text();
}

void newClassDialog::on_pushButton_2_clicked()//cancel按钮
{
	reject();
}
