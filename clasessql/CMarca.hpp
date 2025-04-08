
#ifndef  CMARCA
#define  CMARCA

#include <RecordSet.hpp>
class CMarca : public CRecordSet
{
public:
	CMarca(C_ODBC *odbc_ext, const char *select=NULL);
    ~CMarca();
    void activarCols();
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[4];
    int nCTipo[4];
    long nLongitud[4];
    long nLongResp[4];
    void *pVar[4];

	char	cMarca_Res[52];
    int 	iCod_Rechazo;
	char	cRechazo_Desc[52];

};
#endif
