#ifndef READONLYDELEGATE_H
#define READONLYDELEGATE_H

#include <QItemDelegate>

class ReadOnlyDelegate : public QItemDelegate
{
public:
    explicit ReadOnlyDelegate(QWidget *parent = NULL);

	QWidget *createEditor(QWidget *parent,
						  const QStyleOptionViewItem &option, const QModelIndex &index)
    const override;
	void paint(QPainter *painter, const QStyleOptionViewItem &option,
			   const QModelIndex &index) const override;
};




#endif // READONLYDELEGATE_H
