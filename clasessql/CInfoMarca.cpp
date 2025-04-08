#include "CInfoMarca.hpp"
CInfoMarca::CInfoMarca(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=2;
    odbcRet=TRUE;

    nSqlTipo[0] = SQL_CHAR;
	nSqlTipo[1] = SQL_CHAR;

	nCTipo[0] = SQL_C_CHAR;
	nCTipo[1] = SQL_C_CHAR;

    nLongitud[0] = 12;
    nLongitud[1] = 10;

	pVar[0] = cFechaMarca;
	pVar[1] = cHoraMarca;
	
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
CInfoMarca::~CInfoMarca()
{
	Commit();
}
void CInfoMarca::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
}