#include "CASBinaryStringBuilder.h"
#include "CASSQLGrid.h"

CASSQLGrid::CASSQLGrid()
{
}

CASSQLGrid::~CASSQLGrid()
{
    //Set() 接管 CSQLItem 的引用所有权，析构时必须归还
    //ReleaseReferences() 走 GC 路径时会先释放并置空，此处对 nullptr 跳过
    for (auto iter = m_aryData.begin(); iter != m_aryData.end(); iter++)
    {
        for (auto iter2 = (*iter).begin(); iter2 != (*iter).end(); iter2++)
        {
            if (*iter2 != nullptr)
            {
                (*iter2)->Release();
                *iter2 = nullptr;
            }
        }
    }
}

void CASSQLGrid::EnumReferences(asIScriptEngine* engine)
{
    for (auto iter = m_aryData.begin(); iter != m_aryData.end(); iter++)
    {
        for (auto iter2 = (*iter).begin(); iter2 != (*iter).end(); iter2++)
        {
            if (*iter2 != nullptr)
                engine->ForwardGCEnumReferences(*iter2, engine->GetTypeInfoByName("CSQLItem"));
        }
    }
}

void CASSQLGrid::ReleaseReferences(asIScriptEngine* engine)
{
    for (auto iter = m_aryData.begin(); iter != m_aryData.end(); iter++)
    {
        for (auto iter2 = (*iter).begin(); iter2 != (*iter).end(); iter2++)
        {
            if (*iter2 != nullptr)
            {
                (*iter2)->Release();
                *iter2 = nullptr;
            }
        }
    }
}

CASSQLGrid* CASSQLGrid::Factory(size_t row, size_t column)
{
    CASSQLGrid* obj = new CASSQLGrid();
    obj->m_aryData.resize(row);
    for (auto iter = obj->m_aryData.begin(); iter != obj->m_aryData.end(); iter++)
    {
        (*iter).resize(column);
    }
    obj->m_iRow               = row;
    obj->m_iColumn            = column;
    CASServerManager* manager = ASEXT_GetServerManager();
    asIScriptEngine*  engine  = manager->scriptEngine;
    asITypeInfo*      type    = engine->GetTypeInfoByName("CSQLGrid");
    engine->NotifyGarbageCollectorOfNewObject(obj, type);
    return obj;
}

void CASSQLGrid::Set(size_t row, size_t column, CASSQLItem* pItem)
{
    m_aryData[row][column] = pItem;
}

CASSQLItem* CASSQLGrid::Get(size_t row, size_t column)
{
    if (row >= m_iRow || column >= m_iColumn)
        return nullptr;
    //注册声明为 CSQLItem@ (非 @+)，引擎不会对返回句柄自动加引用
    //网格自身持有所有权，这里必须先 AddRef 把引用移交给脚本
    CASSQLItem* pItem = m_aryData[row][column];
    if (pItem != nullptr)
        pItem->AddRef();
    return pItem;
}
CASSQLItem* CASSQLGrid::opIndex(size_t row, size_t column)
{
    return Get(row, column);
}
size_t CASSQLGrid::Rows()
{
    return m_iRow;
}
size_t CASSQLGrid::Columns()
{
    return m_iColumn;
}
