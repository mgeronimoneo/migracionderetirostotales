#ifndef CRETIROSTOTALESCONSTANCIAISSSTE
#define CRETIROSTOTALESCONSTANCIAISSSTE

#include <RecordSet.hpp>
class CRetirostotalesconstanciaissste : public CRecordSet
{
public:
	CRetirostotalesconstanciaissste(C_ODBC *odbc_ext, const char *select=NULL);
    ~CRetirostotalesconstanciaissste();
    void activarCols();
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[5];
    int nCTipo[5];
    long nLongitud[5];
    long nLongResp[5];
    void *pVar[5];

	int		iFoliosolicitud;
	char	cNss[13];
	int		iConsecutivo;
	char	cConstancia[3];
};
#endif