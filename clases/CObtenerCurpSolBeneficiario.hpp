
#ifndef COBTENERCURPSOLBENEFICIARIO
#define COBTENERCURPSOLBENEFICIARIO

#include <RecordSet.hpp>
class CObtenerCurpSolBeneficiario : public CRecordSet 
{
public:
    CObtenerCurpSolBeneficiario(C_ODBC *odbc_ext, const char *select=NULL);
    ~CObtenerCurpSolBeneficiario();
    void activarCols();
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[2];
    int nCTipo[2];
    long nLongitud[2];
    long nLongResp[2];
    void *pVar[2];
    
    char                curpbenef[56];
};
#endif COBTENERCURPSOLBENEFICIARIO
