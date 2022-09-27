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
#include <QtConcurrent>

struct SubstringMatcher {
    SubstringMatcher(const Sample& match)
        : m_match(match)
    {
    }
    bool operator()(const Sample& test)
    {
        qDebug() << "filtering in" << QThread::currentThread();
        QString str = test.second.toString();
        return str.toLower().contains(m_match.second.toString().toLower());
    }

    Sample m_match;
};

DataController::DataController(QObject* parent)
    : QObject(parent)
    , m_values(new DataModel(this))
    , m_filteredValues(new DataModel(this))
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
    if (m_watchers.count())
        return;
    for (int g = 0; g < 8; g++) {
        QVector<int> ids;
        for (int i = 1; i <= 10; i++) {
            ids << 10 * g + i;
        }

        QFutureWatcher<SampleList>* watcher = new QFutureWatcher<SampleList>;
        connect(watcher, &QFutureWatcher<SampleList>::finished, [=]() {
            qDebug() << "Results read";

            SampleList smples = watcher->future().result();
            for (auto s : smples) {
                m_values->addData(s);
            }
            m_watchers.removeOne(watcher);
            delete watcher;

            find("CCCC");
        });

        QFuture<SampleList> futrue = QtConcurrent::run(&DataCruncher::calculate, ids);
        watcher->setFuture(futrue);
        m_watchers.append(watcher);
    }
}

void DataController::stop()
{
}

void DataController::find(const QString substr)
{
    qDebug() << __func__;
    if (!substr.length())
        return;
    QFutureWatcher<Sample>* watcher = new QFutureWatcher<Sample>;
    m_filteredValues->clear();

    connect(watcher, &QFutureWatcher<Sample>::resultsReadyAt, [=](int i) { m_filteredValues->addData(watcher->resultAt(i)); });
    connect(watcher, &QFutureWatcher<Sample>::finished, this, [=]() {
        delete watcher;
        qDebug() << "All calc done";
        emit matchesFound();
    });

    Sample          tested(-1, substr);
    QFuture<Sample> futrue = QtConcurrent::filtered(m_values->data(), SubstringMatcher(tested));
    watcher->setFuture(futrue);
}

QObject* DataController::filteredValues() const
{
    return m_filteredValues;
}
