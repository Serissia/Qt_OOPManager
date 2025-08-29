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

	tableView = new QTableView(this);
	defaultDelegate = new QStyledItemDelegate(this);
	readOnlyDelegate = new ReadOnlyDelegate(this);
	model = new QStandardItemModel(this);

	tableView->setSelectionMode(QAbstractItemView::SingleSelection); // 设置单行选择模式
	tableView->setSelectionBehavior(QAbstractItemView::SelectItems); // 设置选择行为为单元格
	tableView->setModel(model);
	setCentralWidget(tableView);

	// 页面修改数据同步vector
	connect(defaultDelegate, &QAbstractItemDelegate::closeEditor, this, &MainWindow::tableViewUpdate);

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
	showClassInfoTable();
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
	newClassDialog dlgNew(this, m_InfoManager.getAllId());
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
		showClassInfoTable();
	}
}

void MainWindow::showClassInfoTable()
{
	model->clear();
	model->setColumnCount(7);
	int rowNum = m_InfoManager.getNumber();
	model->setRowCount(rowNum);//设置行列数

	for(int j = 0; j < 7; ++j)
		tableView->setItemDelegateForColumn(j, defaultDelegate);
	tableView->setItemDelegateForColumn(0, readOnlyDelegate);//除第一列外可修改

	QStringList header;
	header << "编号" << "类成员" << "类名" << "基类名" << "功能" << "创建日期" << "作者";
	model->setHorizontalHeaderLabels(header);//设置表头

	for(int i = 0; i < rowNum; ++i)//设置相关数据
	{
		classInfo tmpClass = m_InfoManager.getClassInfoByRow(i);
		model->setItem(i, 0, new QStandardItem(QString::number(tmpClass.getID())));
		model->setItem(i, 1, new QStandardItem(tmpClass.getName()));
		model->setItem(i, 2, new QStandardItem(tr("[点击详情]")));
		model->setItem(i, 3, new QStandardItem(tmpClass.getBaseName()));
		model->setItem(i, 4, new QStandardItem(tmpClass.getFunction()));
		model->setItem(i, 5, new QStandardItem(tmpClass.getDate()));
		model->setItem(i, 6, new QStandardItem(tmpClass.getName()));
	}
}

void MainWindow::tableViewUpdate()
{

}
