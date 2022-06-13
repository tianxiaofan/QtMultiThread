/**************************************************************************
 *   文件名	：datamodel.cpp
 *   =======================================================================
 *   创 建 者	：田小帆
 *   创建日期	：2022-6-6
 *   邮   箱	：499131808@qq.com
 *   Q Q		：499131808
 *   公   司      ：
 *   功能描述      ：
 *   使用说明 ：
 *   ======================================================================
 *   修改者	：
 *   修改日期	：
 *   修改内容	：
 *   ======================================================================
 *
 ***************************************************************************/
#include "datamodel.h"
#include <QDebug>

DataModel::DataModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

void DataModel::clear()
{
    m_data.clear();
}

QVector<Sample>& DataModel::data()
{

    return m_data;
}

int DataModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;
    return m_data.count();
}

QVariant DataModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (role == Lable)
        return QString("%1: ").arg(m_data.at(index.row()).first);
    if (role == Value)
        return m_data.at(index.row()).second;
    else
        return QVariant();
}

QHash<int, QByteArray> DataModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Lable] = "label";
    roles[Value] = "value";
    return roles;
}

void DataModel::addData(const Sample& data)
{
    qDebug() << data.second;
    beginInsertRows(QModelIndex(), 0, 0);
    m_data.prepend(data);
    endInsertRows();
}
