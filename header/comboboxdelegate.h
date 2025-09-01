#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H

#include <QItemDelegate>
#include <QStyleOptionViewItem>
#include <QStringList>

class ComboBoxDelegate : public QItemDelegate
{
	Q_OBJECT
public:
	explicit ComboBoxDelegate(QObject *parent = 0,
							  const QStringList lists = {});

	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
						  const QModelIndex &index) const override;

	void setEditorData(QWidget *editor, const QModelIndex &index) const override;
	void setModelData(QWidget *editor, QAbstractItemModel *model,
					  const QModelIndex &index) const override;

	void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option,
							  const QModelIndex &index) const override;
private:
	QStringList choice;
};

#endif // COMBOBOXDELEGATE_H
