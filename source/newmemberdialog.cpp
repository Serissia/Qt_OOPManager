#include "header/newmemberdialog.h"
#include "ui_newmemberdialog.h"
#include <header/invalidinputdialog.h>

newmemberdialog::newmemberdialog(QWidget *parent,
								 const QSet<int>& dataSet) :
	QDialog(parent),
	ui(new Ui::newmemberdialog),
	m_id(dataSet)
{
	ui->setupUi(this);
}

newmemberdialog::~newmemberdialog()
{
	delete ui;
}

void newmemberdialog::on_lineMem_activated(int index)
{
	if(index == 1)
		ui->lineSpace->setEnabled(false);//函数类型无内存
	else
		ui->lineSpace->setEnabled(true);
}

int newmemberdialog::Number()
{
	return ui->lineNum->value();
}

QString newmemberdialog::Name()
{
	return ui->lineName->text();
}

QString newmemberdialog::MemType()
{
	return ui->lineMem->currentText();
}

int newmemberdialog::Size()
{
	return ui->lineSpace->value();
}

QString newmemberdialog::DataType()
{
	return ui->lineData->text();
}

QString newmemberdialog::Acc()
{
	return ui->lineAcc->currentText();
}

void newmemberdialog::on_pushButton_2_clicked()
{
	reject();
}

void newmemberdialog::on_pushButton_clicked()
{
	if(m_id.contains(ui->lineNum->value()))
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
