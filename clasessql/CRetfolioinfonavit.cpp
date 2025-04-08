#include "CRetfolioinfonavit.hpp"
CRetfolioinfonavit::CRetfolioinfonavit(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=8;
    odbcRet=TRUE;

	nSqlTipo[0] = 	SQL_CHAR;
	nSqlTipo[1] = 	SQL_BIGINT;
	nSqlTipo[2] = 	SQL_CHAR;
	nSqlTipo[3] = 	SQL_INTEGER;
	nSqlTipo[4] = 	SQL_CHAR;
	nSqlTipo[5] = 	SQL_CHAR;
	nSqlTipo[6] = 	SQL_CHAR;
	nSqlTipo[7] = 	SQL_SMALLINT;

	nCTipo[0] = 	SQL_C_CHAR;
	nCTipo[1] = 	SQL_C_SBIGINT;
	nCTipo[2] = 	SQL_C_CHAR;
	nCTipo[3] = 	SQL_C_SLONG;
	nCTipo[4] = 	SQL_C_CHAR;
	nCTipo[5] = 	SQL_C_CHAR;	
	nCTipo[6] = 	SQL_C_CHAR; 
	nCTipo[7] = 	SQL_C_SSHORT;

    nLongitud[0] =  13;
    nLongitud[1] =  9;
    nLongitud[2] =  16;
    nLongitud[3] =  5;
    nLongitud[4] =  3;
	nLongitud[5] =  12;
    nLongitud[6] =  14;
    nLongitud[7] =  3;

	pVar[0] = cNss;
	pVar[1] = &iConsecutivo;
	pVar[2] = cFolioinfonavit;
	pVar[3] = &iFoliosolicitud;
	pVar[4] = cTiporetiro;
	pVar[5] = cFechacaptura;
	pVar[6] = cUsuariocaptura;
	pVar[7] = &iMigracionrettotsafre;

    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
CRetfolioinfonavit::~CRetfolioinfonavit()
{
	Commit();
}
void CRetfolioinfonavit::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
}