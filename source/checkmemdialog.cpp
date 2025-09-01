#include "header/checkmemdialog.h"
#include "ui_checkmemdialog.h"
#include <header/newmemberdialog.h>
#include <QDebug>

checkMemDialog::checkMemDialog(QWidget *parent, const classInfo& classEdit) :
	QDialog(parent),
	ui(new Ui::checkMemDialog),
	m_class(classEdit)//最后要返回m_class!!!
{
	ui->setupUi(this);
	setWindowTitle(m_class.getName() + "的类成员");

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

	showClassMemInfoTable();
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
void checkMemDialog::on_pushButton_clicked()//新增类成员
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

void checkMemDialog::on_pushButton_2_clicked()
{
	accept();
}
