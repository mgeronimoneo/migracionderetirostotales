#include "CTimbrado.hpp"
CTimbrado::CTimbrado(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=7;
    odbcRet=TRUE;

	nSqlTipo[0] = SQL_CHAR;
	nSqlTipo[1] = SQL_CHAR;
	nSqlTipo[2] = SQL_INTEGER;
	nSqlTipo[3] = SQL_CHAR;
	nSqlTipo[4] = SQL_SMALLINT;
	nSqlTipo[5] = SQL_SMALLINT;
	nSqlTipo[6] = SQL_CHAR;

	nCTipo[0] = SQL_C_CHAR;
	nCTipo[1] = SQL_C_CHAR;
	nCTipo[2] = SQL_C_SLONG;
	nCTipo[3] = SQL_C_CHAR;
	nCTipo[4] = SQL_C_SSHORT;
	nCTipo[5] = SQL_C_SSHORT;
	nCTipo[6] = SQL_C_CHAR;

    nLongitud[0] = 13;
    nLongitud[1] = 15;
    nLongitud[2] = 5;
    nLongitud[3] = 3;
	nLongitud[4] = 3;
    nLongitud[5] = 3;
    nLongitud[6] = 21;

	pVar[0] = cNss;
	pVar[1] = cRfc;
	pVar[2] = &iFolioservicio;
	pVar[3] = cTiposervicio;
	pVar[4] = &iRespuesta;
	pVar[5] = &iMigracionrettotsafre;
	pVar[6] = cFechaAlta;

    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }
}
CTimbrado::~CTimbrado()
{
	Commit();
}
void CTimbrado::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
}

