#include "header/mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileDialog>
#include <header/newclassdialog.h>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setWindowTitle(tr("面向对象程序项目管理系统"));//设置主页面标题
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
	QString curPath = QDir::currentPath();
	QString dlgTitle = tr("请选择一个文件");
	QString fileFilter = "文本文件(*.txt);;所有文件(*.*)";
	QString fileName = QFileDialog::getOpenFileName(this, dlgTitle,
													curPath, fileFilter);
	if(fileName.isEmpty()) return;
	m_InfoManager.readClassFromFile(fileName);

}

void MainWindow::on_actionSave_triggered()
{
	QString curPath = QDir::currentPath();
	QString dlgTitle = tr("另存为一个文件");
	QString fileFilter = "文本文件(*.txt);;所有文件(*.*)";
	QString fileName = QFileDialog::getSaveFileName(this, dlgTitle,
													curPath, fileFilter);
	if(fileName.isEmpty()) return;
	m_InfoManager.saveClassToFile(fileName);
}

void MainWindow::on_actionNew_triggered()
{
	newClassDialog dlgNew(this);
	int ret = dlgNew.exec();//展示模态的新增类对话框
	if(ret == QDialog::Accepted)
	{
		classInfo tmpClass;
		tmpClass.setAuthor(dlgNew.author());
		tmpClass.setBaseName(dlgNew.baseClassName());
		tmpClass.setDate(dlgNew.createdDate());
		tmpClass.setFunction(dlgNew.function());
		tmpClass.setId(dlgNew.number());
		tmpClass.setName(dlgNew.className());
		m_InfoManager.addClass(tmpClass);
	}
}
