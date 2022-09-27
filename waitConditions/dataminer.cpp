/**************************************************************************
 *   文件名	：dataminer.cpp
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
#include "dataminer.h"
#include "datasharing.h"
#include <QDebug>
#include <QRandomGenerator>

Sample         buffer[BufferSize];
QWaitCondition bufferNotEmpty;
QWaitCondition bufferNotFull;
QMutex         mutex;
int            numUsedCells = 0;

DataMiner::DataMiner(QObject* parent)
    : QThread { parent }
{
    mutex.lock();
    numUsedCells = 0;
    mutex.unlock();
}

DataMiner::~DataMiner()
{
    qDebug() << __func__ << "DataMiner thread deleted";
}

void DataMiner::setIds(const QVector<int>& ids)
{
    m_ids = ids;
}

void DataMiner::run()
{
    qDebug() << __func__ << QThread::currentThread()->objectName();

    const char*      nucleobases = "CGAT";
    QRandomGenerator rand;
    for (int i = 0; i < m_ids.length(); i++) {
        QString dna;
        for (int i = 0; i < 80; i++) {
            int idx = rand.bounded(0, 4);
            dna.append(nucleobases[idx]);
            for (int j = 0; j < THROTTLE_AMOUNT; j++)
                ;
        }
        mutex.lock();
        if (numUsedCells == BufferSize) {
            qDebug() << "Buffer full,Waiting for more space";
            bufferNotFull.wait(&mutex);
        }
        mutex.unlock();

        buffer[i % BufferSize] = Sample(m_ids.at(i), dna);
        mutex.lock();
        ++numUsedCells;
        bufferNotEmpty.wakeAll();
        mutex.unlock();

        if (isInterruptionRequested())
            break;
    }
}
