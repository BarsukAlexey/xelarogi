#include "qitemdelegateformusiclist.h"

QItemDelegateForMusicList::QItemDelegateForMusicList(QObject *parent) :
    QStyledItemDelegate(parent)
{

}

void QItemDelegateForMusicList::paint(QPainter* painter,
                                      const QStyleOptionViewItem& option,
                                      const QModelIndex& index) const
{

    //QStyledItemDelegate::paint(painter, option, index);

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);

    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index);
    opt.palette.setColor(QPalette::Text, Qt::red);

    const QWidget *widget = option.widget;
    QStyle *style = widget ? widget->style() : QApplication::style();
    style->drawControl(QStyle::CE_ItemViewItem, &opt, painter, widget);

    painter->restore();
}
