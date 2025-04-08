#include "CMarca.hpp"
CMarca::CMarca(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=3;
    odbcRet=TRUE;

	nSqlTipo[0] = 	SQL_CHAR;
    nSqlTipo[1] = 	SQL_INTEGER;
	nSqlTipo[2] = 	SQL_CHAR;

	nCTipo[0] = 	SQL_C_CHAR;
    nCTipo[1] = 	SQL_C_SLONG;
	nCTipo[2] = 	SQL_C_CHAR;

    nLongitud[0] =   52;
    nLongitud[1] =   5;
	nLongitud[2] =   52;

	pVar[0] =   cMarca_Res;
	pVar[1] =   &iCod_Rechazo;
	pVar[2] =   cRechazo_Desc;

    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
CMarca::~CMarca()
{
	Commit();
}
void CMarca::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
}
