#include "header/mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileDialog>
#include <header/newclassdialog.h>
#include <QDebug>
#include <header/checkmemdialog.h>
#include <QHeaderView>
#include <QFont>
#include <header/deletewarn.h>
#include <header/findforclass.h>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setWindowTitle(tr("面向对象程序项目管理系统"));//设置主页面标题

	QFont font1, font2;
	font1.setPointSize(14);
	font2.setPointSize(14);
	font2.setItalic(true);//斜体

	for(int i = 0 ; i <= 1; ++i)
	{
		tableView[i] = new QTableView(this);
		defaultDelegate[i] = new QStyledItemDelegate(this);
		readOnlyDelegate[i] = new ReadOnlyDelegate(this);
		dateEditDelegate[i] = new DateEditDelegate(this);
		model[i] = new QStandardItemModel(this);
	}
	tabWidget = new QTabWidget(this);
	/*设置标签页信息*/
	tabWidget->setFont(font2);
	tabWidget->addTab(tableView[0], "类信息");
	tabWidget->addTab(tableView[1], "查找");
	tabWidget->setTabEnabled(1, false);

	for(int i = 0; i <= 1; ++i)
	{
		tableView[i]->setFont(font1);
		tableView[i]->setSelectionMode(QAbstractItemView::SingleSelection); // 设置单行选择模式
		tableView[i]->setSelectionBehavior(QAbstractItemView::SelectItems); // 设置选择行为为单元格
		tableView[i]->setModel(model[i]);
		tableView[i]->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//随ui填充
		// 页面修改数据同步vector
		connect(defaultDelegate[i], &QAbstractItemDelegate::closeEditor,
				this, &MainWindow::tableViewUpdate);
		connect(dateEditDelegate[i], &QAbstractItemDelegate::closeEditor,
				this, &MainWindow::tableViewUpdate);
		connect(tableView[i]->selectionModel(), &QItemSelectionModel::selectionChanged,
				this, &MainWindow::onSelectionChanged);
		connect(tableView[i], &QTableView::doubleClicked,
				this, &MainWindow::onDoubleClicked);
	}
	setCentralWidget(tabWidget);

	ui->actionMember->setEnabled(false);//初始为禁用状态
	ui->actionDelete->setEnabled(false);

	connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(onPageChanged()));
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
	m_InfoManager[0].readClassFromFile(fileName);

	showClassInfoTable(0);
}

void MainWindow::on_actionSave_triggered()
{
	QString curPath = QDir::currentPath();
	QString dlgTitle = tr("另存为一个文件");
	QString fileFilter = "文本文件(*.txt);;所有文件(*.*)";
	QString fileName = QFileDialog::getSaveFileName(this, dlgTitle,
													curPath, fileFilter);
	if(fileName.isEmpty()) return;
	m_InfoManager[0].saveClassToFile(fileName);
}

void MainWindow::on_actionNew_triggered()
{
	newClassDialog dlgNew(this, m_InfoManager[0].getAllId());
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
		m_InfoManager[0].addClass(tmpClass);
		showClassInfoTable(0);
	}
}

void MainWindow::showClassInfoTable(int page)//刷新对应页面
{
	model[page]->clear();
	model[page]->setColumnCount(7);
	int rowNum = m_InfoManager[page].getNumber();
	model[page]->setRowCount(rowNum);//设置行、列数

	for(int j = 1; j < 7; ++j)
		tableView[page]->setItemDelegateForColumn(j, defaultDelegate[page]);
	tableView[page]->setItemDelegateForColumn(0, readOnlyDelegate[page]);//除第1,2列外可修改
	tableView[page]->setItemDelegateForColumn(2, readOnlyDelegate[page]);
	tableView[page]->setItemDelegateForColumn(5, dateEditDelegate[page]);

	QStringList header;
	header << "编号" << "类名" << "类成员" << "基类名" << "功能" << "创建日期" << "作者";
	model[page]->setHorizontalHeaderLabels(header);//设置表头

	for(int i = 0; i < rowNum; ++i)//设置相关数据
	{
		classInfo tmpClass = m_InfoManager[page].getClassInfoByRow(i);
		model[page]->setItem(i, 0, new QStandardItem(QString::number(tmpClass.getID())));
		model[page]->setItem(i, 1, new QStandardItem(tmpClass.getName()));
		model[page]->setItem(i, 2, new QStandardItem(tr("[查看详情]")));
		model[page]->item(i, 2)->setTextAlignment(Qt::AlignCenter);
		model[page]->setItem(i, 3, new QStandardItem(tmpClass.getBaseName()));
		model[page]->setItem(i, 4, new QStandardItem(tmpClass.getFunction()));
		model[page]->setItem(i, 5, new QStandardItem(tmpClass.getDate()));
		model[page]->item(i, 5)->setTextAlignment(Qt::AlignCenter);
		model[page]->setItem(i, 6, new QStandardItem(tmpClass.getName()));
	}
}

void MainWindow::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
	Q_UNUSED(deselected);

	if(selected.indexes().isEmpty())
	{
		ui->actionMember->setEnabled(false);
		ui->actionDelete->setEnabled(false);
	}
	else
	{
		ui->actionMember->setEnabled(true);
		ui->actionDelete->setEnabled(true);
	}
}

void MainWindow::onPageChanged()
{
	if(tabWidget->currentIndex() == 0)
	{
		qDebug() << "切换至第一页" <<endl;
		ui->actionMember->setEnabled(false);
		ui->actionDelete->setEnabled(false);
		showClassInfoTable(0);
	}
	else if(tabWidget->currentIndex() == 1)
	{
		qDebug() << "切换至第二页" <<endl;
		ui->actionMember->setEnabled(false);
		ui->actionDelete->setEnabled(false);
		showClassInfoTable(1);
	}
}

void MainWindow::tableViewUpdate()
{
	int page = tabWidget->currentIndex();
	QModelIndex modelIndex = tableView[page]->currentIndex();
	if(!modelIndex.isValid()) return;

	int row = modelIndex.row();
	int col = modelIndex.column();
	classInfo &classUpd = m_InfoManager[page].getClassInfoByRow(row);//获取地址方便修改
	classInfo *classUpdElse = m_InfoManager[!page].findClassById(classUpd.getID());
	QVariant newData = model[page]->data(modelIndex);
	//一次性修改两处
	switch (col) {
		case 1:
			classUpd.setName(newData.toString());
			if(classUpdElse != nullptr)
				classUpdElse->setName(newData.toString());
			break;
		case 3:
			classUpd.setBaseName(newData.toString());
			if(classUpdElse != nullptr)
				classUpdElse->setBaseName(newData.toString());
			break;
		case 4:
			classUpd.setFunction(newData.toString());
			if(classUpdElse != nullptr)
				classUpdElse->setFunction(newData.toString());
			break;
		case 5:
			classUpd.setDate(newData.toDate());
			if(classUpdElse != nullptr)
				classUpdElse->setDate(newData.toDate());
			break;
		case 6:
			classUpd.setAuthor(newData.toString());
			if(classUpdElse != nullptr)
				classUpdElse->setAuthor(newData.toString());
			break;
	}

	qDebug() << "已修改类(Id:" << classUpd.getID() << ")\n";
}

void MainWindow::on_actionMember_triggered()//编辑某个classInfo的类成员
{
	int page = tabWidget->currentIndex();
	QModelIndex modelIndex = tableView[page]->currentIndex();
	if(!modelIndex.isValid()) return;
	classInfo &classChosen = m_InfoManager[page].getClassInfoByRow(modelIndex.row());
	classInfo *classElse = m_InfoManager[!page].findClassById(classChosen.getID());

	checkMemDialog dlgMem(this, classChosen);//打开对应页面
	int res = dlgMem.exec();//展示模态的新增类对话框
	if(res == QDialog::Accepted)
	{
		auto tmpMems = dlgMem.getMems();
		classChosen.setMembers(tmpMems);
		if(classElse != nullptr)
			classElse->setMembers(tmpMems);
	}
/*               已知Bug待修复：
			第二次及以后编辑添加过成员的classInfo检查id唯一性失效
			9-1-14:43 已修复，原因是忘记更新QSet<int>nums
*/
	showClassInfoTable(0);
	showClassInfoTable(1);
}

void MainWindow::onDoubleClicked(const QModelIndex &index)
{
	if(!index.isValid()||index.column() != 2) return;
	int page = tabWidget->currentIndex();
	classInfo &classChosen = m_InfoManager[page].getClassInfoByRow(index.row());
	classInfo *classElse = m_InfoManager[!page].findClassById(classChosen.getID());

	checkMemDialog dlgMem(this, classChosen);//打开对应页面
	int res = dlgMem.exec();//展示模态的新增类对话框
	if(res == QDialog::Accepted)
	{
		auto tmpMems = dlgMem.getMems();
		classChosen.setMembers(tmpMems);
		if(classElse != nullptr)
			classElse->setMembers(tmpMems);
	}
	showClassInfoTable(0);
	showClassInfoTable(1);
}

void MainWindow::on_actionFind_triggered()
{
	FindForClass dlgFind(this);
	int res = dlgFind.exec();
	if(res == QDialog::Accepted)
	{
		int chosen = dlgFind.Chosen();
		if(chosen == 1)
			FindClass(dlgFind.Num(), chosen);
		else
			FindClass(dlgFind.Name(), chosen);
		tabWidget->setTabEnabled(1, true);
		tabWidget->setCurrentIndex(1);//自动跳转第二页
		showClassInfoTable(1);
	}
}

void MainWindow::FindClass(QVariant goal, int chosen)
{
	m_InfoManager[1].clear();
	for(int i = 0; i < m_InfoManager[0].getNumber(); ++i)
	{
		classInfo &tmpClass = m_InfoManager[0].getClassInfoByRow(i);
		switch(chosen)
		{
			case 1:
				if(goal.toInt() == tmpClass.getID())
					m_InfoManager[1].addClass(tmpClass);
				break;
			case 2:
				if(goal.toString() == tmpClass.getName())
					m_InfoManager[1].addClass(tmpClass);
				break;
		}
	}
}

void MainWindow::on_actionDelete_triggered()//删除classInfo
{
	int page = tabWidget->currentIndex();
	QModelIndex modelIndex = tableView[page]->currentIndex();
	if(!modelIndex.isValid()) return;
	classInfo &classChosen = m_InfoManager[page].getClassInfoByRow(modelIndex.row());

	DeleteWarn dlgDel(this);
	int res = dlgDel.exec();
	if(res == QDialog::Accepted)
	{
		int idr = classChosen.getID();
		if(!m_InfoManager[page].removeClass(idr))
			qDebug() << "删除失败！\n";
		else
		{
			qDebug() << "删除成功\n";
			m_InfoManager[!page].removeClass(idr);
			showClassInfoTable(0);
			showClassInfoTable(1);
		}
	}
}
