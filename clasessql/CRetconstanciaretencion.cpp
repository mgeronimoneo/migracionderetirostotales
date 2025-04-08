#include "CRetconstanciaretencion.hpp"
CRetconstanciaretencion::CRetconstanciaretencion(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=12;
    odbcRet=TRUE;

    nSqlTipo[0] = SQL_CHAR;
    nSqlTipo[1] = SQL_INTEGER;
	nSqlTipo[2] = SQL_BIGINT;
	nSqlTipo[3] = SQL_CHAR;
	nSqlTipo[4] = SQL_CHAR;
    nSqlTipo[5] =  SQL_CHAR;
    nSqlTipo[6] =  SQL_CHAR;
    nSqlTipo[7] =  SQL_CHAR;
    nSqlTipo[8] =  SQL_SMALLINT;
    nSqlTipo[9] =  SQL_SMALLINT;
    nSqlTipo[10] =  SQL_SMALLINT;
    nSqlTipo[11] = SQL_SMALLINT;

    nCTipo[0] = SQL_C_CHAR;
	nCTipo[1] = SQL_C_SLONG;
	nCTipo[2] = SQL_C_SBIGINT;
	nCTipo[3] = SQL_C_CHAR;
	nCTipo[4] = SQL_C_CHAR;
    nCTipo[5] = SQL_C_CHAR;
    nCTipo[6] = SQL_C_CHAR;
    nCTipo[7] = SQL_C_CHAR;
    nCTipo[8] = SQL_C_SSHORT;
    nCTipo[9] = SQL_C_SSHORT;
    nCTipo[10] = SQL_C_SSHORT;
    nCTipo[11] = SQL_C_SSHORT;

    nLongitud[0] = 12;
    nLongitud[1] = 5;
    nLongitud[2] = 9;
    nLongitud[3] = 13;
    nLongitud[4] = 15;
    nLongitud[5] = 20;
    nLongitud[6] = 102;
    nLongitud[7] = 3;
    nLongitud[8] = 3;
    nLongitud[9] = 3;
    nLongitud[10] = 3;
    nLongitud[11] = 3;

    pVar[0] = cFechaAlta;
	pVar[1] = &iFolioSolicitud;
	pVar[2] = &iConsecutivo;
	pVar[3] = cNss;
	pVar[4] = cRfc;
    pVar[5] = cCurp;
    pVar[6] = cNombreSolicitante;
    pVar[7] = cTipoRetiro;
    pVar[8] = &iOrigenRetiro;
    pVar[9] = &iDeduccion;
    pVar[10] = &iIdBeneficiario;
    pVar[11] = &iMigracionRetTotSafre;
	
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
CRetconstanciaretencion::~CRetconstanciaretencion()
{
	Commit();
}
void CRetconstanciaretencion::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
}