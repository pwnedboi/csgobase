#pragma once

namespace NetVar
{
    vector<RecvTable*> GetTables();
    RecvTable* GetTable(vector<RecvTable*> tables, const char* tableName);
    int GetOffset(vector<RecvTable*> tables, const char* tableName, const char *propName);
    int GetProp(vector<RecvTable*> tables, const char* tableName, const char* propName, RecvProp** prop = 0);
    int GetProp(vector<RecvTable*> tables, RecvTable* recvTable, const char* propName, RecvProp** prop = 0);
    string DumpTable(RecvTable* table, int depth);
    uintptr_t HookProp(const char* tableName, const char* propName, RecvVarProxyFn function);
}
