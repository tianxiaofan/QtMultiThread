/**************************************************************************
 *   文件名	：datacontroller.cpp
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
#include "datacontroller.h"
#include <QDebug>
#include <QThreadPool>

DataController::DataController(QObject* parent)
    : QObject(parent)
    , m_values(new DataModel(this))
{
}

DataController::~DataController()
{
    qDebug() << "Data controller exited";
}

QObject* DataController::values() const
{
    return m_values;
}

void DataController::start()
{
    for (int i = 0; i < 80; i++) {
        DataCruncher* runable = new DataCruncher(this);
        runable->setIds(QVector<int>() << i);
        //创建线程池，自动管理线程，且自动释放资源，
        QThreadPool::globalInstance()->start(runable);
    }
}

void DataController::stop()
{
}

void DataController::handleData(const Sample& sample)
{
    m_values->addData(sample);
}
