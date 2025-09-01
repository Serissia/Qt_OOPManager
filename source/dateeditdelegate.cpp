#include "header/dateeditdelegate.h"
#include <QDateEdit>
#include <QSpinBox>

DateEditDelegate::DateEditDelegate(QObject *parent) :
	QItemDelegate(parent)
{
}

// 创建编辑器
QWidget *DateEditDelegate::createEditor(QWidget *parent,
									   const QStyleOptionViewItem &/* option */,
									   const QModelIndex &/* index */) const
{
	QDateEdit *editor = new QDateEdit(parent);
	editor->setCalendarPopup(true);//日历形式
	editor->setDisplayFormat("yyyy/M/d");//设置日期格式
	editor->setDateTime(QDateTime::currentDateTime());//默认显示系统时间
	return editor;
}

// 为编辑器设置数据
void DateEditDelegate::setEditorData(QWidget *editor,
									const QModelIndex &index) const
{
	QDate value = index.model()->data(index, Qt::EditRole).toDate();
	QDateEdit *dateEdit = static_cast<QDateEdit*>(editor);
	dateEdit->setDate(value);
}

// 将数据写入到模型
void DateEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
								   const QModelIndex &index) const
{
	QDateEdit *dateEdit = static_cast<QDateEdit*>(editor);
	dateEdit->interpretText();
	QDate value = dateEdit->date();
	model->setData(index, value, Qt::EditRole);
}

// 更新编辑器几何布局
void DateEditDelegate::updateEditorGeometry(QWidget *editor,
										   const QStyleOptionViewItem &option,
										   const QModelIndex &/* index */) const
{
	editor->setGeometry(option.rect);
}
