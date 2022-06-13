/**************************************************************************
 *   文件名	：datacruncher.h
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
#include "Sample.h"
#include <QObject>
#include <QPointer>
#include <QRunnable>

class DataCruncher : public QRunnable {
public:
    explicit DataCruncher(QObject* observer = nullptr);
    ~DataCruncher();
    void setIds(const QVector<int>& ids);

signals:
    void newData(Sample data);
    void done();

private:
    QVector<int> m_ids;
    QPointer<QObject> m_observer;

    // QThread interface
protected:
    void run() override;

private:
    void calculate();
};
