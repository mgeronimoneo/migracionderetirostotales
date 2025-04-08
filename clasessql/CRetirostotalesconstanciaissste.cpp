#include "CRetirostotalesconstanciaissste.hpp"
CRetirostotalesconstanciaissste::CRetirostotalesconstanciaissste(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=4;
    odbcRet=TRUE;

    nSqlTipo[0] = 	SQL_INTEGER;
	nSqlTipo[1] = 	SQL_CHAR;
	nSqlTipo[2] = 	SQL_INTEGER;
	nSqlTipo[3] = 	SQL_CHAR;

	nCTipo[0] = 	SQL_C_SLONG;
	nCTipo[1] = 	SQL_C_CHAR;
	nCTipo[2] = 	SQL_C_SLONG;
	nCTipo[3] = 	SQL_C_CHAR;

    nLongitud[0] =   5;
    nLongitud[1] =   13;
    nLongitud[2] =   5;
    nLongitud[3] =   3;

	pVar[0] = 	&iFoliosolicitud;
	pVar[1] = 	cNss;
	pVar[2] = 	&iConsecutivo;
	pVar[3] = 	cConstancia;

	
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
CRetirostotalesconstanciaissste::~CRetirostotalesconstanciaissste()
{
	Commit();
}
void CRetirostotalesconstanciaissste::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
}