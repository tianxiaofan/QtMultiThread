/**************************************************************************
 *   文件名	：datacruncher.h
 *   =======================================================================
 *   创 建 者	：田小帆
 *   创建日期	：2022-6-6
 *   邮   箱	：499131808@qq.com
 *   Q Q		：499131808
 *   公   司      ：西安英杰伟成航空科技有限公司
 *   功能描述      ：
 *   使用说明 ：任何人或机构要使用、修改、发布本源代码,都必须要获得西安英杰伟成航空科技有限公司的授权
 *   ======================================================================
 *   修改者	：
 *   修改日期	：
 *   修改内容	：
 *   ======================================================================
 *
 ***************************************************************************/

#pragma once
#include "Sample.h"
#include <QThread>
class DataCruncher : public QThread {
    Q_OBJECT
public:
    explicit DataCruncher(QObject* parent = nullptr);
    ~DataCruncher();
    void setIds(const QVector<int>& ids);

signals:
    void newData(Sample data);
    void done();

private:
    QVector<int> m_ids;
    bool         m_calclating = false;
    int          m_index      = 0;

    // QThread interface
protected:
    void run() override;
};
