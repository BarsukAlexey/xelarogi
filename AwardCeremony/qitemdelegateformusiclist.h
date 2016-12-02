#ifndef QITEMDELEGATEFORMUSICLIST_H
#define QITEMDELEGATEFORMUSICLIST_H


#include <QItemDelegate>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QDebug>
#include <QApplication>




class QItemDelegateForMusicList : public QStyledItemDelegate
{
public:
    QItemDelegateForMusicList(QObject *parent = Q_NULLPTR);

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const Q_DECL_OVERRIDE;
};

#endif // QITEMDELEGATEFORMUSICLIST_H

