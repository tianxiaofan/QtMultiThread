/**************************************************************************
 *   文件名	：cruncherthread.cpp
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
#include "cruncherthread.h"
#include "datasharing.h"
#include <QDebug>

CruncherThread::CruncherThread(QObject* parent)
    : QThread(parent)
{
    m_dataMiner = new DataMiner(this);
    m_dataMiner->setObjectName("Data miner thread");
    QVector<int> ids;
    for (int i = 0; i <= 20; i++)
        ids << i;

    m_dataMiner->setIds(ids);
    m_dataMiner->start();
}

CruncherThread::~CruncherThread()
{
    m_dataMiner->wait();
}

void CruncherThread::setIds(const QVector<int>& ids)
{
    m_ids = ids;
}

void CruncherThread::run()
{
    qDebug() << __func__ << QThread::currentThread()->objectName();
    for (int i = 0; i < m_ids.size(); ++i) {
        mutex.lock();
        if (numUsedCells == 0) {
            qDebug() << "Buffer empty,Waiting for more data";
            bufferNotEmpty.wait(&mutex);
        }
        mutex.unlock();

        Sample sample = buffer[i % BufferSize];
        qDebug() << "Id received from the miner" << sample.first;
        emit newData(sample);
        qDebug() << sample.first << "----------";

        for (int j = 0; j < THROTTLE_AMOUNT; j++)
            ;

        mutex.lock();
        --numUsedCells;
        bufferNotFull.wakeAll();
        mutex.unlock();

        if (isInterruptionRequested()) {
            m_dataMiner->requestInterruption();
            break;
        }
    }
}
