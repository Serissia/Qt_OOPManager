#include "header/readonlydelegate.h"
#include <QPainter>

ReadOnlyDelegate::ReadOnlyDelegate(QWidget *parent)
    :QItemDelegate(parent)
{

}


 QWidget *ReadOnlyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
 {
     Q_UNUSED(parent);
     Q_UNUSED(option);
	 Q_UNUSED(index);//标注未使用去除编辑器warning
	 return NULL;//不可修改
 }


 void ReadOnlyDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
 {
     painter->save();

     QColor backgroundColor(173, 216, 230);

     // 绘制背景
     painter->fillRect(option.rect, backgroundColor);

     painter->restore();

     // 调用基类绘制默认内容（文本等）
     QItemDelegate::paint(painter, option, index);
 }

