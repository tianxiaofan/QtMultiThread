/**************************************************************************
 *   文件名	：datamodel.h
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
#pragma once
#include "sample.h"
#include <QAbstractListModel>
#include <QVector>
class DataModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum Roles { Lable = Qt::UserRole, Value };
    explicit DataModel(QObject* parent = nullptr);
    void             clear();
    QVector<Sample>& data();

    // QAbstractItemModel interface
public:
    int                    rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant               data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

public slots:
    void addData(const Sample& data);

private:
    QVector<Sample> m_data;
};
