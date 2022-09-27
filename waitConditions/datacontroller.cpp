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

DataController::DataController(QObject* parent)
    : QObject(parent)
    , m_values(new DataModel(this))
{
    qRegisterMetaType<Sample>("Sample");
    m_cruncherThread = new CruncherThread(this);
    connect(m_cruncherThread, &CruncherThread::newData, m_values, &DataModel::addData);
}

DataController::~DataController()
{
    qDebug() << "Data controller exited";
    stop();
}

QObject* DataController::values() const
{
    return m_values;
}

void DataController::start()
{
    QVector<int> ids;
    for (int i = 0; i <= 20; i++)
        ids << i;
    m_cruncherThread->setIds(ids);
    m_cruncherThread->start();
}

void DataController::stop()
{
    m_cruncherThread->requestInterruption();
    m_cruncherThread->quit();
    m_cruncherThread->wait();
}
