#ifndef CINFOMARCA
#define CINFOMARCA

#include <RecordSet.hpp>
class CInfoMarca : public CRecordSet
{
public:
    CInfoMarca(C_ODBC *odbc_ext, const char *select=NULL);
    ~CInfoMarca();
    void activarCols();
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[3];
    int nCTipo[3];
    long nLongitud[3];
    long nLongResp[3];
    void *pVar[3];

    char        cFechaMarca[12];
    char        cHoraMarca[10];
    
};
#endif