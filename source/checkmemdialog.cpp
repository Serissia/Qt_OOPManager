#include "header/checkmemdialog.h"
#include "ui_checkmemdialog.h"
#include <header/newmemberdialog.h>
#include <QDebug>
#include <QLayout>
#include <header/deletewarn.h>

checkMemDialog::checkMemDialog(QWidget *parent, const classInfo& classEdit) :
	QDialog(parent),
	ui(new Ui::checkMemDialog),
	m_class(classEdit)//最后要返回m_class!!!
{
	ui->setupUi(this);
	setWindowTitle(m_class.getName() + "的类成员");

	// 创建按钮布局
	QHBoxLayout *buttonLayout = new QHBoxLayout;
	buttonLayout->addStretch(); // 添加弹性空间
	buttonLayout->addWidget(ui->ButtonNew);
	buttonLayout->addSpacing(60); // 按钮间距
	buttonLayout->addWidget(ui->ButtonDel);
	buttonLayout->addSpacing(60);
	buttonLayout->addWidget(ui->ButtonRe);
	buttonLayout->addStretch();

	// 创建主布局
	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(ui->tableView);
	mainLayout->addLayout(buttonLayout);

	// 设置拉伸因子，使tableView获得更多空间
	mainLayout->setStretchFactor(ui->tableView, 5);
	mainLayout->setStretchFactor(buttonLayout, 1);

	// 设置布局边距和间距
	mainLayout->setContentsMargins(10, 10, 10, 10);
	mainLayout->setSpacing(40);

	// 设置对话框属性
	setMinimumSize(800, 800); // 设置最小大小
	ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);// 使表格列自动填充可用空间

	model = new QStandardItemModel(this);
	readOnlyDelegate = new ReadOnlyDelegate(this);
	defaultDelegate = new QStyledItemDelegate(this);
	spinBoxDelegate = new SpinBoxDelegate(this);
	comboBoxDelegate_Acc = new ComboBoxDelegate(this, {"公有","私有","保护"});
	comboBoxDelegate_Mem = new ComboBoxDelegate(this, {"数据","函数"});

	ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection); // 设置单行选择模式
	ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems); // 设置选择行为为单元格
	ui->tableView->setModel(model);

	// 页面修改数据同步vector
	connect(defaultDelegate, &QAbstractItemDelegate::closeEditor,
			this, &checkMemDialog::tableViewUpdate);
	connect(comboBoxDelegate_Acc, &QAbstractItemDelegate::closeEditor,
			this, &checkMemDialog::tableViewUpdate);
	connect(comboBoxDelegate_Mem, &QAbstractItemDelegate::closeEditor,
			this, &checkMemDialog::tableViewUpdate);

	ui->ButtonDel->setEnabled(false);//初始设为禁用
	connect(ui->tableView->selectionModel(), &QItemSelectionModel::selectionChanged,
			this, &checkMemDialog::onSelectionChanged);

	if(m_class.getNum() != 0) showClassMemInfoTable();
}

checkMemDialog::~checkMemDialog()
{
	delete ui;
}

QVector<classMemberInfo>& checkMemDialog::getMems()
{
	return m_class.getMems();
}

void checkMemDialog::showClassMemInfoTable()
{
	model->clear();
	model->setColumnCount(6);
	int rowNum = m_class.getNum();
	model->setRowCount(rowNum);//设置行、列数

	for(int j = 0; j < 6; ++j)
		ui->tableView->setItemDelegateForColumn(j, defaultDelegate);
	ui->tableView->setItemDelegateForColumn(0, readOnlyDelegate);//除第一列外可修改
	ui->tableView->setItemDelegateForColumn(3, spinBoxDelegate);
	ui->tableView->setItemDelegateForColumn(2, comboBoxDelegate_Mem);
	ui->tableView->setItemDelegateForColumn(5, comboBoxDelegate_Acc);

	QStringList header;
	header << "成员编号" << "成员名称" << "成员类型" << "内存字节数" << "数据类型" << "可访问性";
	model->setHorizontalHeaderLabels(header);//设置表头

	for(int i = 0; i < rowNum; ++i)//设置相关数据
	{
		classMemberInfo tmpMember = m_class.getClassMemInfoByRow(i);
		model->setItem(i, 0, new QStandardItem(QString::number(tmpMember.getID())));
		model->setItem(i, 1, new QStandardItem(tmpMember.getName()));
		model->setItem(i, 2, new QStandardItem(tmpMember.getMemType()));
		model->setItem(i, 3, new QStandardItem(QString::number(tmpMember.getSize())));
		model->setItem(i, 4, new QStandardItem(tmpMember.getDataType()));
		model->setItem(i, 5, new QStandardItem(tmpMember.getAcc()));
	}
}

void checkMemDialog::tableViewUpdate()//更新类成员的tableView
{
	QModelIndex modelIndex = ui->tableView->currentIndex();
	if(!modelIndex.isValid()) return;

	int row = modelIndex.row();
	int col = modelIndex.column();
	classMemberInfo &classMemUpd = m_class.getClassMemInfoByRow(row);
	QVariant newData = model->data(modelIndex);

	switch (col) {
		case 1:
			classMemUpd.setName(newData.toString());
			break;
		case 2:
			classMemUpd.setMemType(newData.toString());
			break;
		case 3:
			classMemUpd.setSize(newData.toInt());
			break;
		case 4:
			classMemUpd.setDataType(newData.toString());
			break;
		case 5:
			classMemUpd.setAcc(newData.toString());
			break;
	}

	qDebug() << "已修改类(Id:" << m_class.getID() << ")的类成员(Id:"
			 << classMemUpd.getID() << ")\n";
}

void checkMemDialog::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
	Q_UNUSED(deselected);

	if(selected.indexes().isEmpty())
		ui->ButtonDel->setEnabled(false);
	else
		ui->ButtonDel->setEnabled(true);
}

void checkMemDialog::on_ButtonNew_clicked()//新增类成员
{
	newmemberdialog dlgNew(this, m_class.getAllId());
	int ret = dlgNew.exec();//展示模态的新增类对话框
	if(ret == QDialog::Accepted)
	{
		classMemberInfo tmpMember;
		tmpMember.setAcc(dlgNew.Acc());
		tmpMember.setDataType(dlgNew.DataType());
		tmpMember.setID(dlgNew.Number());
		tmpMember.setMemType(dlgNew.MemType());
		tmpMember.setName(dlgNew.Name());
		tmpMember.setSize(dlgNew.Size());
		m_class.addMember(tmpMember);
		showClassMemInfoTable();
	}
}

void checkMemDialog::on_ButtonRe_clicked()
{
	accept();
}

void checkMemDialog::on_ButtonDel_clicked()
{
	QModelIndex modelIndex = ui->tableView->currentIndex();
	if(!modelIndex.isValid()) return;
	classMemberInfo &memberChosen = m_class.getClassMemInfoByRow(modelIndex.row());

	DeleteWarn dlgDel(this);
	int res = dlgDel.exec();
	if(res == QDialog::Accepted)
	{
		int idr = memberChosen.getID();
		if(!m_class.removeMember(idr))
			qDebug() << "删除失败！\n";
		else
		{
			qDebug() << "删除成功\n";
			showClassMemInfoTable();
		}
	}
}
