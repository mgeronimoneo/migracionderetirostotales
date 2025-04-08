#include "CRetftoconformidad.hpp"
CRetftoconformidad::CRetftoconformidad(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=18;
    odbcRet=TRUE;

    nSqlTipo[0] = 	SQL_CHAR;
	nSqlTipo[1] = 	SQL_INTEGER;
	nSqlTipo[2] = 	SQL_BIGINT;
	nSqlTipo[3] = 	SQL_BIGINT;
	nSqlTipo[4] = 	SQL_SMALLINT;
	nSqlTipo[5] = 	SQL_CHAR;
	nSqlTipo[6] = 	SQL_CHAR;
	nSqlTipo[7] = 	SQL_CHAR;
	nSqlTipo[8] = 	SQL_CHAR;
	nSqlTipo[9] = 	SQL_CHAR;
	nSqlTipo[10] = 	SQL_CHAR;
	nSqlTipo[11] = 	SQL_DOUBLE;	
	nSqlTipo[12] =	SQL_CHAR;
	nSqlTipo[13] = 	SQL_CHAR;
	nSqlTipo[14] = 	SQL_CHAR;
	nSqlTipo[15] =	SQL_CHAR;
	nSqlTipo[16] =	SQL_CHAR;
	nSqlTipo[17] =	SQL_SMALLINT;

	nCTipo[0] = 	SQL_C_CHAR;
	nCTipo[1] = 	SQL_C_SLONG;
	nCTipo[2] = 	SQL_C_SBIGINT;
	nCTipo[3] = 	SQL_C_SBIGINT;
	nCTipo[4] = 	SQL_C_SSHORT;
	nCTipo[5] = 	SQL_C_CHAR;
	nCTipo[6] = 	SQL_C_CHAR;	
	nCTipo[7] = 	SQL_C_CHAR;
	nCTipo[8] = 	SQL_C_CHAR;
	nCTipo[9] = 	SQL_C_CHAR;
	nCTipo[10] = 	SQL_C_CHAR;
	nCTipo[11] = 	SQL_C_DOUBLE;
	nCTipo[12] = 	SQL_C_CHAR;
	nCTipo[13] = 	SQL_C_CHAR;
	nCTipo[14] = 	SQL_C_CHAR;
	nCTipo[15] = 	SQL_C_CHAR;
	nCTipo[16] = 	SQL_C_CHAR;
	nCTipo[17] = 	SQL_C_SSHORT;
	
    nLongitud[0] =	13;
    nLongitud[1] =  5;
    nLongitud[2] =  9;
    nLongitud[3] =  9;
    nLongitud[4] =  3;
    nLongitud[5] =  20;
	nLongitud[6] =  13;
    nLongitud[7] =  4;
    nLongitud[8] =  4;
    nLongitud[9] =  15;
    nLongitud[10] = 20;
    nLongitud[11] = 9;
	nLongitud[12] = 12;
    nLongitud[13] = 12;  
    nLongitud[14] = 16;
    nLongitud[15] = 14;
    nLongitud[16] = 14;
    nLongitud[17] = 3;

	pVar[0] = cNss;
	pVar[1] = &iFoliosolicitud;
	pVar[2] = &iConsecsolicitud;
	pVar[3] = &iConsecconformidad;
	pVar[4] = &iBanco;
	pVar[5] = cCtaclabe;
	pVar[6] = cNumcuenta;
	pVar[7] = cIdentificacion;
	pVar[8] = cOtraidentificacion;
	pVar[9] = cFolioife;
	pVar[10] = cCveelector;
	pVar[11] = &dMontoenpesos;
	pVar[12] = cFechacaptura;
	pVar[13] = cFechamodifica;
	pVar[14] = cFolioinfonavit;
	pVar[15] = cUsuariocaptura;
	pVar[16] = cUsuariomodifica;
	pVar[17] = &iMigracionrettotsafre;

    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
CRetftoconformidad::~CRetftoconformidad()
{
	Commit();
}
void CRetftoconformidad::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
}