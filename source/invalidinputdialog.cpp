#include "header/invalidinputdialog.h"
#include "ui_invalidinputdialog.h"

invalidInputDialog::invalidInputDialog(QWidget *parent, const int newid) :
	QDialog(parent),
	ui(new Ui::invalidInputDialog),
	recId(newid)
{
	ui->setupUi(this);
	setWindowTitle(tr("Warning!"));
	setFixedSize(660, 350);
}

invalidInputDialog::~invalidInputDialog()
{
	delete ui;
}

void invalidInputDialog::setId(const int id)
{
	recId = id;
	ui->label_2->setText(tr("推荐使用编号：") + QString::number(recId));
}
