/**************************************************************************
 *   文件名	：cruncherthread.h
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
#include "dataminer.h"
#include "sample.h"
#include <QPointer>
#include <QThread>

class CruncherThread : public QThread {
    Q_OBJECT
public:
    explicit CruncherThread(QObject* parent = nullptr);
    virtual ~CruncherThread() override;

    void setIds(const QVector<int>& ids);

signals:
    void newData(Sample data);

private:
    QVector<int>        m_ids;
    QPointer<DataMiner> m_dataMiner;

    // QThread interface
protected:
    void run() override;
};
