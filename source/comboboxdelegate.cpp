#include "header/comboboxdelegate.h"
#include <QComboBox>
#include <QDateEdit>

ComboBoxDelegate::ComboBoxDelegate(QObject *parent,
								   const QStringList lists) :
	QItemDelegate(parent),
	choice(lists)
{
}

// 创建编辑器
QWidget *ComboBoxDelegate::createEditor(QWidget *parent,
									   const QStyleOptionViewItem &/* option */,
									   const QModelIndex &/* index */) const
{
	QComboBox *editor = new QComboBox(parent);
	editor->addItems(choice);
	editor->setEditable(false);//不可自主编辑
	return editor;
}

// 为编辑器设置数据
void ComboBoxDelegate::setEditorData(QWidget *editor,
									const QModelIndex &index) const
{
	QString value = index.model()->data(index, Qt::EditRole).toString();
	QComboBox *comboEdit = static_cast<QComboBox*>(editor);
	comboEdit->setCurrentText(value);
}

// 将数据写入到模型
void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
								   const QModelIndex &index) const
{
	QComboBox *comboEdit = static_cast<QComboBox*>(editor);
//	interpretText(); ?
	QString value = comboEdit->currentText();
	model->setData(index, value, Qt::EditRole);
}

// 更新编辑器几何布局
void ComboBoxDelegate::updateEditorGeometry(QWidget *editor,
										   const QStyleOptionViewItem &option,
										   const QModelIndex &/* index */) const
{
	editor->setGeometry(option.rect);
}
