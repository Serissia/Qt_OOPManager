#include "header/mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileDialog>
#include <header/newclassdialog.h>
#include <QDebug>
#include <header/checkmemdialog.h>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setWindowTitle(tr("面向对象程序项目管理系统"));//设置主页面标题

	tableView = new QTableView(this);
	defaultDelegate = new QStyledItemDelegate(this);
	readOnlyDelegate = new ReadOnlyDelegate(this);
	dateEditDelegate = new DateEditDelegate(this);
	model = new QStandardItemModel(this);

	tableView->setSelectionMode(QAbstractItemView::SingleSelection); // 设置单行选择模式
	tableView->setSelectionBehavior(QAbstractItemView::SelectItems); // 设置选择行为为单元格
	tableView->setModel(model);
	setCentralWidget(tableView);
	tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//随ui填充

	// 页面修改数据同步vector
	connect(defaultDelegate, &QAbstractItemDelegate::closeEditor,
			this, &MainWindow::tableViewUpdate);
	connect(dateEditDelegate, &QAbstractItemDelegate::closeEditor,
			this, &MainWindow::tableViewUpdate);

	ui->actionMember->setEnabled(false);//初始为禁用状态
	connect(tableView->selectionModel(), &QItemSelectionModel::selectionChanged,
			this, &MainWindow::onSelectionChanged);

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
	model->setRowCount(rowNum);//设置行、列数

	for(int j = 0; j < 7; ++j)
		tableView->setItemDelegateForColumn(j, defaultDelegate);
	tableView->setItemDelegateForColumn(0, readOnlyDelegate);//除第一列外可修改
	tableView->setItemDelegateForColumn(5, dateEditDelegate);

	QStringList header;
	header << "编号" << "类名" << "类成员" << "基类名" << "功能" << "创建日期" << "作者";
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

void MainWindow::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
	Q_UNUSED(deselected);

	if(selected.indexes().isEmpty())
		ui->actionMember->setEnabled(false);
	else
		ui->actionMember->setEnabled(true);
}

void MainWindow::tableViewUpdate()
{
	QModelIndex modelIndex = tableView->currentIndex();
	if(!modelIndex.isValid()) return;

	int row = modelIndex.row();
	int col = modelIndex.column();
	classInfo &classUpd = m_InfoManager.getClassInfoByRow(row);//获取地址方便修改
	QVariant newData = model->data(modelIndex);

	switch (col) {
		case 1:
			classUpd.setName(newData.toString());
			break;
		case 3:
			classUpd.setBaseName(newData.toString());
			break;
		case 4:
			classUpd.setFunction(newData.toString());
			break;
		case 5:
			classUpd.setDate(newData.toDate());
			break;
		case 6:
			classUpd.setAuthor(newData.toString());
			break;
	}

	qDebug() << "已修改类(Id:" << classUpd.getID() << ")\n";
}

void MainWindow::on_actionMember_triggered()//编辑某个classInfo的类成员
{
	QModelIndex modelIndex = tableView->currentIndex();
	if(!modelIndex.isValid()) return;
	classInfo &classChosen = m_InfoManager.getClassInfoByRow(modelIndex.row());

	checkMemDialog dlgMem(this, classChosen);//打开对应页面
	int res = dlgMem.exec();//展示模态的新增类对话框
	if(res == QDialog::Accepted)
		classChosen.setMembers(dlgMem.getMems());
/*               已知Bug待修复：
			第二次及以后编辑添加过成员的classInfo检查id唯一性失效
			9-1-14:43 已修复，原因是忘记更新QSet<int>nums
*/
	showClassInfoTable();
}
