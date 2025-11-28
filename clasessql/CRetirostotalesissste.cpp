#include "CRetirostotalesissste.hpp"
CRetirostotalesissste::CRetirostotalesissste(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=39;
    odbcRet=TRUE;

    nSqlTipo[0] = 	SQL_INTEGER;
	nSqlTipo[1] = 	SQL_C_SBIGINT;
	nSqlTipo[2] = 	SQL_CHAR;
	nSqlTipo[3] = 	SQL_CHAR;
	nSqlTipo[4] = 	SQL_CHAR;
	nSqlTipo[5] = 	SQL_INTEGER;
	nSqlTipo[6] = 	SQL_CHAR;
	nSqlTipo[7] = 	SQL_CHAR;
	nSqlTipo[8] = 	SQL_CHAR;
	nSqlTipo[9] = 	SQL_CHAR;
	nSqlTipo[10] = 	SQL_CHAR;
	nSqlTipo[11] = 	SQL_CHAR;
	nSqlTipo[12] =	SQL_CHAR;
	nSqlTipo[13] = 	SQL_CHAR;
	nSqlTipo[14] = 	SQL_CHAR;
	nSqlTipo[15] =	SQL_SMALLINT;
	nSqlTipo[16] =	SQL_CHAR;
	nSqlTipo[17] =	SQL_CHAR;
	nSqlTipo[18] =	SQL_CHAR;
	nSqlTipo[19] =	SQL_CHAR;
	nSqlTipo[20] =	SQL_CHAR;
	nSqlTipo[21] = 	SQL_CHAR;
	nSqlTipo[22] = 	SQL_CHAR;
	nSqlTipo[23] = 	SQL_CHAR;
	nSqlTipo[24] = 	SQL_INTEGER;
	nSqlTipo[25] = 	SQL_SMALLINT;
	nSqlTipo[26] = 	SQL_SMALLINT;
	nSqlTipo[27] = 	SQL_SMALLINT;
	nSqlTipo[28] = 	SQL_CHAR;
	nSqlTipo[29] = 	SQL_SMALLINT;
	nSqlTipo[30] = 	SQL_CHAR;
	nSqlTipo[31] = 	SQL_CHAR;
	nSqlTipo[32] = 	SQL_CHAR;
	nSqlTipo[33] = 	SQL_CHAR;
	nSqlTipo[34] = 	SQL_CHAR;
	nSqlTipo[35] = 	SQL_CHAR;
	nSqlTipo[36] = 	SQL_SMALLINT;
	nSqlTipo[37] = 	SQL_SMALLINT;
	nSqlTipo[38] = 	SQL_SMALLINT;
	//nSqlTipo[39] =  SQL_SMALLINT;

	nCTipo[0] = 	SQL_C_SLONG;
	nCTipo[1] = 	SQL_C_SBIGINT;
	nCTipo[2] = 	SQL_C_CHAR;
	nCTipo[3] = 	SQL_C_CHAR;
	nCTipo[4] = 	SQL_C_CHAR;
	nCTipo[5] = 	SQL_C_SLONG;
	nCTipo[6] = 	SQL_C_CHAR;
	nCTipo[7] = 	SQL_C_CHAR;
	nCTipo[8] = 	SQL_C_CHAR;
	nCTipo[9] = 	SQL_C_CHAR;
	nCTipo[10] = 	SQL_C_CHAR;
	nCTipo[11] = 	SQL_C_CHAR;
	nCTipo[12] = 	SQL_C_CHAR;
	nCTipo[13] = 	SQL_C_CHAR;
	nCTipo[14] = 	SQL_C_CHAR;
	nCTipo[15] = 	SQL_C_SSHORT;
	nCTipo[16] = 	SQL_C_CHAR;
	nCTipo[17] = 	SQL_C_CHAR;
	nCTipo[18] = 	SQL_C_CHAR;
	nCTipo[19] = 	SQL_C_CHAR;
	nCTipo[20] = 	SQL_C_CHAR;
	nCTipo[21] = 	SQL_C_CHAR;
	nCTipo[22] = 	SQL_C_CHAR;
	nCTipo[23] = 	SQL_C_CHAR;	
	nCTipo[24] = 	SQL_C_SLONG;
	nCTipo[25] = 	SQL_C_SSHORT;
	nCTipo[26] = 	SQL_C_SSHORT;
	nCTipo[27] = 	SQL_C_SSHORT;	
	nCTipo[28] = 	SQL_C_CHAR;
	nCTipo[29] = 	SQL_C_SSHORT;
	nCTipo[30] = 	SQL_C_CHAR;
	nCTipo[31] = 	SQL_C_CHAR;
	nCTipo[32] = 	SQL_C_CHAR;
	nCTipo[33] = 	SQL_C_CHAR;
	nCTipo[34] = 	SQL_C_CHAR;
	nCTipo[35] = 	SQL_C_CHAR;
	nCTipo[36] = 	SQL_C_SSHORT;
	nCTipo[37] = 	SQL_C_SSHORT;
	nCTipo[38] = 	SQL_C_SSHORT;
	//nCTipo[39] =    SQL_C_SSHORT;

    nLongitud[0] =   5;
    nLongitud[1] =   9;
    nLongitud[2] =   20;
    nLongitud[3] =   15;
    nLongitud[4] =   13;
    nLongitud[5] =   5;
	nLongitud[6] =   42;
    nLongitud[7] =   42;
    nLongitud[8] =   42;
    nLongitud[9] =   4;
    nLongitud[10] =  3;
    nLongitud[11] =  4;
	nLongitud[12] =  4;
    nLongitud[13] =  4;  
    nLongitud[14] =  5;
    nLongitud[15] =  3;
    nLongitud[16] =  12;
    nLongitud[17] =  12;
	nLongitud[18] =  12;
    nLongitud[19] =  3;
    nLongitud[20] =  12;
    nLongitud[21] =  5;
    nLongitud[22] =  9;
    nLongitud[23] =  10;
	nLongitud[24] =  5;
    nLongitud[25] =  3;
    nLongitud[26] =  3;
    nLongitud[27] =  3;
	nLongitud[28] =  5;
	nLongitud[29] =  3;
	nLongitud[30] =  12;
	nLongitud[31] =  17;
	nLongitud[32] =  12;
	nLongitud[33] =  17;
	nLongitud[34] =  12;
	nLongitud[35] =  17;
	nLongitud[36] =  3;
	nLongitud[37] =  3;
	nLongitud[38] =  3;
	//nLongitud[39] =  3;

	pVar[0] = 	&iFolio;
	pVar[1] = 	&lConsecutivo;
	pVar[2] = 	cCurp;
	pVar[3] = 	cRfc;
	pVar[4] = 	cNss;
	pVar[5] = 	&iFoliosolicitud;
	pVar[6] = 	cNombreafore;
	pVar[7] = 	cPaterno_afore;
	pVar[8] = 	cMaterno_afore;
	pVar[9] = 	cSecpension;
	pVar[10] = 	cTiporetiro;
	pVar[11] = 	cRegimen;
	pVar[12] = 	cTiposeguro;
	pVar[13] = 	cTipopension;
	pVar[14] = 	cCvepension;
	pVar[15] = 	&iTipoprestacion;
	pVar[16] = 	cFechainiciopension;
	pVar[17] = 	cFecharesolucion;
	pVar[18] = 	cFechasolicitud;
	pVar[19] = 	cClavedocumentoprobatorio;
	pVar[20] = 	cFechanacimiento;
	pVar[21] = 	cAseguradora;
	pVar[22] = 	cActuario;
	pVar[23] = 	cNumplanprivado;
	pVar[24] = 	&iPeriodopago;
	pVar[25] = 	&iSemanas_cotizadas;
	pVar[26] = 	&iEstadcod;
	pVar[27] = 	&iDelegcod;
	pVar[28] = 	cDiagprocesar;
	pVar[29] = 	&iGrupo;
	pVar[30] = 	cFechacaptura;
	pVar[31] = 	cUsuariocaptura;
	pVar[32] = 	cFechamodifica;
	pVar[33] = 	cUsuariomodifica;
	pVar[34] = 	cFechaconfirma;
	pVar[35] = 	cUsuarioconfirma;
	pVar[36] = 	&iCodigo_rechazo;
	pVar[37] = 	&iEstado_solicitud;
	//pVar[38] = 	&iMigracionrettotsafre;
	pVar[38] =  &iPortabilidad;

    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
CRetirostotalesissste::~CRetirostotalesissste()
{
	Commit();
}
void CRetirostotalesissste::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
}