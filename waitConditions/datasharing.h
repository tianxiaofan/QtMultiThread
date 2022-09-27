/**************************************************************************
 *   文件名	：datasharing.h
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
#pragma once
#include <QMutex>
#include <QWaitCondition>

#include "sample.h"
#define BufferSize 5
#define THROTTLE_AMOUNT 5000000
extern Sample         buffer[BufferSize];
extern QWaitCondition bufferNotEmpty;
extern QWaitCondition bufferNotFull;
extern QMutex         mutex;
extern int            numUsedCells;
