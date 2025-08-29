#include "header/newclassdialog.h"
#include "ui_newclassdialog.h"
#include <header/invalidinputdialog.h>

newClassDialog::newClassDialog(QWidget *parent, const QSet<int>& dataSet) :
	QDialog(parent),
	ui(new Ui::newClassDialog),
	m_id(dataSet)
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

void newClassDialog::on_pushButton_clicked()//Ok按钮
{
	 if(m_id.contains(ui->spinBox->value()))
	 {
		 invalidInputDialog dlgInval;
		 for(int i = 1; i <= m_id.size() + 1; ++i)//暴力筛选推荐编号
			 if(!m_id.contains(i))
			 {
				 dlgInval.setId(i);
				 dlgInval.exec();
				 break;
			 }
	 }
	 else accept();
}
