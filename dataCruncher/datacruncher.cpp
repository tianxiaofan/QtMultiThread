/**************************************************************************
 *   文件名	：datacruncher.cpp
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
#include "datacruncher.h"
#include <QDebug>

#include <QRandomGenerator>

#define THROTTLE_AMOUNT 5000000

DataCruncher::DataCruncher(QObject* parent)
    : QObject(parent)
{
}

void DataCruncher::setIds(const QVector<int>& ids)
{
    m_ids = ids;
}

void DataCruncher::start()
{
    qDebug() << "calc start";
    m_calclating = true;
    calculate();
}

void DataCruncher::stop()
{
    qDebug() << "calc stoped";
    m_calclating = false;
    emit done();
}

void DataCruncher::calculate()
{
    const char*      nucleobases = "CGAT";
    QRandomGenerator rand;
    for (int i = 0; i < m_ids.length() && m_calclating; i++) {
        QString dna;
        for (int i = 0; i < 80; i++) {
            int idx = rand.bounded(0, 4);
            dna.append(nucleobases[idx]);
            for (int j = 0; j < THROTTLE_AMOUNT; j++)
                ;
        }
        emit newData(Sample(m_ids.at(i), dna));
    }
    stop();
}
