#include "CSolicitante.hpp"
CSolicitante::CSolicitante(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=9;
    odbcRet=TRUE;

    nSqlTipo[0] = 	SQL_INTEGER;
	nSqlTipo[1] = 	SQL_CHAR;
	nSqlTipo[2] = 	SQL_BIGINT;
	nSqlTipo[3] = 	SQL_CHAR;
	nSqlTipo[4] = 	SQL_CHAR;
	nSqlTipo[5] = 	SQL_CHAR;
	nSqlTipo[6] = 	SQL_CHAR;
	nSqlTipo[7] = 	SQL_SMALLINT;
	nSqlTipo[8] = 	SQL_SMALLINT;

	nCTipo[0] = 	SQL_C_SLONG;
	nCTipo[1] = 	SQL_C_CHAR;
	nCTipo[2] = 	SQL_C_SBIGINT;
	nCTipo[3] = 	SQL_C_CHAR;
	nCTipo[4] = 	SQL_C_CHAR;
	nCTipo[5] = 	SQL_C_CHAR;
	nCTipo[6] = 	SQL_C_CHAR;
	nCTipo[7] = 	SQL_C_SSHORT;
	nCTipo[8] = 	SQL_C_SSHORT;

    nLongitud[0] =   5;
    nLongitud[1] =   20;
    nLongitud[2] =   9;
    nLongitud[3] =   32;
    nLongitud[4] =   32;
    nLongitud[5] =   32;
	nLongitud[6] =   42;
    nLongitud[7] =   3;
    nLongitud[8] =   3;

	pVar[0] = 	&iFoliosolicitud;
	pVar[1] = 	cCurp;
	pVar[2] = 	&lConsecutivo;
	pVar[3] = 	cPaterno;
	pVar[4] = 	cMaterno;
	pVar[5] = 	cNombres;
	pVar[6] = 	cTelefono;
	pVar[7] = 	&iParencod;
	pVar[8] = 	&iMigracionrettotsafre;
	
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
CSolicitante::~CSolicitante()
{
	Commit();
}
void CSolicitante::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
}

