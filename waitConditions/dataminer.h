/**************************************************************************
 *   文件名	：dataminer.h
 *   =======================================================================
 *   创 建 者	：田小帆
 *   创建日期	：2022-6-12
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

#include <QThread>

class DataMiner : public QThread {
    Q_OBJECT
public:
    explicit DataMiner(QObject* parent = nullptr);
    virtual ~DataMiner() override;

    void setIds(const QVector<int>& ids);
signals:
    void newData(Sample data);

protected:
    virtual void run() override;

private:
    QVector<int> m_ids;
};
