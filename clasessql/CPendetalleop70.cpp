#include "CPendetalleop70.hpp"
CPendetalleop70::CPendetalleop70(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=36;
    odbcRet=TRUE;

    nSqlTipo[0] = 	SQL_INTEGER;
	nSqlTipo[1] = 	SQL_INTEGER;
	nSqlTipo[2] = 	SQL_CHAR;
	nSqlTipo[3] = 	SQL_CHAR;
	nSqlTipo[4] = 	SQL_CHAR;
	nSqlTipo[5] = 	SQL_INTEGER;
	nSqlTipo[6] = 	SQL_CHAR;
	nSqlTipo[7] = 	SQL_CHAR;
	nSqlTipo[8] = 	SQL_CHAR;
	nSqlTipo[9] = 	SQL_CHAR;
	nSqlTipo[10] = 	SQL_CHAR;
	nSqlTipo[11] = 	SQL_SMALLINT;
	nSqlTipo[12] = 	SQL_CHAR;
	nSqlTipo[13] = 	SQL_CHAR;
	nSqlTipo[14] = 	SQL_DOUBLE;
	nSqlTipo[15] = 	SQL_DOUBLE;
	nSqlTipo[16] = 	SQL_DOUBLE;
	nSqlTipo[17] = 	SQL_DOUBLE;
	nSqlTipo[18] = 	SQL_SMALLINT;
	nSqlTipo[19] = 	SQL_DOUBLE;
	nSqlTipo[20] = 	SQL_DOUBLE;
	nSqlTipo[21] = 	SQL_DOUBLE;
	nSqlTipo[22] =	SQL_DOUBLE;
	nSqlTipo[23] =	SQL_SMALLINT;
	nSqlTipo[24] = 	SQL_DOUBLE;
	nSqlTipo[25] = 	SQL_CHAR;
	nSqlTipo[26] = 	SQL_CHAR;
	nSqlTipo[27] = 	SQL_CHAR;
	nSqlTipo[28] = 	SQL_CHAR;
	nSqlTipo[29] = 	SQL_SMALLINT;
	nSqlTipo[30] = 	SQL_SMALLINT;
	nSqlTipo[31] = 	SQL_CHAR;
	nSqlTipo[32] = 	SQL_CHAR;
	nSqlTipo[33] = 	SQL_CHAR;
	nSqlTipo[34] = 	SQL_SMALLINT;
	nSqlTipo[35] = 	SQL_SMALLINT;
	
	nCTipo[0] = 	SQL_C_SLONG;
	nCTipo[1] = 	SQL_C_SLONG;
	nCTipo[2] = 	SQL_C_CHAR;
	nCTipo[3] = 	SQL_C_CHAR;
	nCTipo[4] = 	SQL_C_CHAR;
	nCTipo[5] = 	SQL_C_SLONG;
	nCTipo[6] = 	SQL_C_CHAR;
	nCTipo[7] = 	SQL_C_CHAR;
	nCTipo[8] = 	SQL_C_CHAR;
	nCTipo[9] = 	SQL_C_CHAR;
	nCTipo[10] = 	SQL_C_CHAR;
	nCTipo[11] = 	SQL_C_SSHORT;
	nCTipo[12] = 	SQL_C_CHAR;
	nCTipo[13] = 	SQL_C_CHAR;
	nCTipo[14] = 	SQL_C_DOUBLE;
	nCTipo[15] = 	SQL_C_DOUBLE;
	nCTipo[16] = 	SQL_C_DOUBLE;
	nCTipo[17] = 	SQL_C_DOUBLE;
	nCTipo[18] = 	SQL_C_SSHORT;
	nCTipo[19] = 	SQL_C_DOUBLE;
	nCTipo[20] = 	SQL_C_DOUBLE;
	nCTipo[21] = 	SQL_C_DOUBLE;
	nCTipo[22] = 	SQL_C_DOUBLE;
	nCTipo[23] = 	SQL_C_SSHORT;
	nCTipo[24] = 	SQL_C_DOUBLE;
	nCTipo[25] = 	SQL_C_CHAR;
	nCTipo[26] = 	SQL_C_CHAR;
	nCTipo[27] = 	SQL_C_CHAR;
	nCTipo[28] = 	SQL_C_CHAR;
	nCTipo[29] = 	SQL_C_SSHORT;
	nCTipo[30] = 	SQL_C_SSHORT;
	nCTipo[31] = 	SQL_C_CHAR;
	nCTipo[32] = 	SQL_C_CHAR;
	nCTipo[33] = 	SQL_C_CHAR;
	nCTipo[34] = 	SQL_C_SSHORT;
	nCTipo[35] = 	SQL_C_SSHORT;
	
    nLongitud[0] =   5;
    nLongitud[1] =   5; 
    nLongitud[2] =   13;
    nLongitud[3] =   20;
    nLongitud[4] =   4;
    nLongitud[5] =   5;
	nLongitud[6] =   3;
    nLongitud[7] =   4;
    nLongitud[8] =   4;
    nLongitud[9] =   4;
    nLongitud[10] =  5;
    nLongitud[11] =  3;
	nLongitud[12] =  12;
    nLongitud[13] =  12;
    nLongitud[14] =  9;
    nLongitud[15] =  9;
    nLongitud[16] =  9;
    nLongitud[17] =  9;
	nLongitud[18] =  3;
    nLongitud[19] =  9;
    nLongitud[20] =  9;
    nLongitud[21] =  9;
    nLongitud[22] =  9;
    nLongitud[23] =  3;
	nLongitud[24] =  9;
    nLongitud[25] =  12;
    nLongitud[26] =  12;
    nLongitud[27] =  12;
	nLongitud[28] =	 4;	
	nLongitud[29] =	 3;
	nLongitud[30] =	 3;
	nLongitud[31] =  12;
	nLongitud[32] =  12;
	nLongitud[33] =	 17;
	nLongitud[34] =  3;
	nLongitud[35] =  3;
	
	pVar[0] = 	&folioenvio;
	pVar[1] = 	&idtiponotifica;
	pVar[2] = 	nss;
	pVar[3] = 	curp;
	pVar[4] = 	secpension;
	pVar[5] = 	&foliodatamart;
	pVar[6] = 	tiporetiro;
	pVar[7] = 	regimen;
	pVar[8] = 	tiposeguro;
	pVar[9] = 	tipopension;
	pVar[10] =	cvepension;
	pVar[11] =	&tipoprestacion;
	pVar[12] =	fechainipen;
	pVar[13] =	fechaprimerpago;
	pVar[14] =	&mtoretiro97;
	pVar[15] =	&mtocv;
	pVar[16] =	&mtocs;
	pVar[17] =	&mtoviv97;
	pVar[18] =	&nummenpagadas;
	pVar[19] =	&saldoretiro97;
	pVar[20] =	&saldocv;
	pVar[21] =	&saldocs;
	pVar[22] =	&saldoviv97;
	pVar[23] =	&nummencalculadas;
	pVar[24] =	&mtototalpmg;
	pVar[25] =	fechaultimopago;
	pVar[26] =	fechaagotamiento;
	pVar[27] =	fechafallecimiento;
	pVar[28] =	diagoperacion;
	pVar[29] =	&codigorechazo;
	pVar[30] =	&origeninformacion;
	pVar[31] =	fechacarga;
	pVar[32] =	horacarga;
	pVar[33] =	usuario;
	pVar[34] =	&estado;
	pVar[35] =	&estatusreplica;
	
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
CPendetalleop70::~CPendetalleop70()
{
	Commit();
}
void CPendetalleop70::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
}

