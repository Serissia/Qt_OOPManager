#include "header/defaultnotice.h"
#include "ui_defaultnotice.h"

DefaultNotice::DefaultNotice(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DefaultNotice)
{
	ui->setupUi(this);
	setWindowTitle(tr("Notice"));
	setFixedSize(660, 350);
}

DefaultNotice::~DefaultNotice()
{
	delete ui;
}

void DefaultNotice::setContent(QString content)
{
	ui->label->setText(content);
}
