﻿/**************************************************************************
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
#include <QObject>
typedef QPair<int, QVariant> Sample;
typedef QVector<Sample>      SampleList;

class DataCruncher {
public:
    explicit DataCruncher();
    ~DataCruncher();

public:
    static SampleList calculate(const QVector<int>& ids);
};
