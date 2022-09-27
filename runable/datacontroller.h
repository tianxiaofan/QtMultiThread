/**************************************************************************
 *   文件名	：datacontroller.h
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
#include "datacruncher.h"
#include "datamodel.h"
#include <QObject>

class DataController : public QObject {
    Q_OBJECT
    Q_PROPERTY(QObject* values READ values CONSTANT)
public:
    explicit DataController(QObject* parent = nullptr);
    virtual ~DataController() override;
    QObject* values() const;

public slots:
    void start();
    void stop();
    void handleData(const Sample& sample);

private:
    DataModel*    m_values;
    DataCruncher* m_cruncher;
};
