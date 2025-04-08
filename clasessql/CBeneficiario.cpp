#include "CBeneficiario.hpp"
CBeneficiario::CBeneficiario(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=42;
    odbcRet=TRUE;

    nSqlTipo[0] = 	SQL_INTEGER;
	nSqlTipo[1] = 	SQL_CHAR;
	nSqlTipo[2] = 	SQL_BIGINT;
	nSqlTipo[3] = 	SQL_SMALLINT;
	nSqlTipo[4] = 	SQL_SMALLINT;
	nSqlTipo[5] = 	SQL_SMALLINT;
	nSqlTipo[6] = 	SQL_CHAR;
	nSqlTipo[7] = 	SQL_CHAR;
	nSqlTipo[8] = 	SQL_CHAR;
	nSqlTipo[9] = 	SQL_CHAR;
	nSqlTipo[10] = 	SQL_CHAR;
	nSqlTipo[11] = 	SQL_CHAR;
	nSqlTipo[12] = 	SQL_CHAR;
	nSqlTipo[13] = 	SQL_SMALLINT;
	nSqlTipo[14] = 	SQL_INTEGER;
	nSqlTipo[15] = 	SQL_SMALLINT;
	nSqlTipo[16] = 	SQL_INTEGER;
	nSqlTipo[17] = 	SQL_SMALLINT;
	nSqlTipo[18] = 	SQL_SMALLINT;
	nSqlTipo[19] = 	SQL_SMALLINT;
	nSqlTipo[20] = 	SQL_CHAR;
	nSqlTipo[21] = 	SQL_CHAR;
	nSqlTipo[22] =	SQL_CHAR;
	nSqlTipo[23] =	SQL_DOUBLE;
	nSqlTipo[24] = 	SQL_DOUBLE;
	nSqlTipo[25] = 	SQL_CHAR;
	nSqlTipo[26] = 	SQL_CHAR;
	nSqlTipo[27] = 	SQL_CHAR;
	nSqlTipo[28] = 	SQL_CHAR;
	nSqlTipo[29] = 	SQL_CHAR;
	nSqlTipo[30] = 	SQL_CHAR;
	nSqlTipo[31] = 	SQL_INTEGER;
	nSqlTipo[32] = 	SQL_SMALLINT;
	nSqlTipo[33] = 	SQL_SMALLINT;
	nSqlTipo[34] = 	SQL_CHAR;
	nSqlTipo[35] = 	SQL_CHAR;
	nSqlTipo[36] = 	SQL_CHAR;
	nSqlTipo[37] = 	SQL_CHAR;
	nSqlTipo[38] = 	SQL_CHAR;
	nSqlTipo[39] = 	SQL_CHAR;
	nSqlTipo[40] = 	SQL_CHAR;
	nSqlTipo[41] = 	SQL_SMALLINT;

	nCTipo[0] = 	SQL_C_SLONG;
	nCTipo[1] = 	SQL_C_CHAR;
	nCTipo[2] = 	SQL_C_SBIGINT;
	nCTipo[3] = 	SQL_C_SSHORT;
	nCTipo[4] = 	SQL_C_SSHORT;
	nCTipo[5] = 	SQL_C_SSHORT;
	nCTipo[6] = 	SQL_C_CHAR;
	nCTipo[7] = 	SQL_C_CHAR;
	nCTipo[8] = 	SQL_C_CHAR;
	nCTipo[9] = 	SQL_C_CHAR;
	nCTipo[10] = 	SQL_C_CHAR;
	nCTipo[11] = 	SQL_C_CHAR;
	nCTipo[12] = 	SQL_C_CHAR;
	nCTipo[13] = 	SQL_C_SSHORT;
	nCTipo[14] = 	SQL_C_SLONG;
	nCTipo[15] = 	SQL_C_SSHORT;
	nCTipo[16] = 	SQL_C_SLONG;
	nCTipo[17] = 	SQL_C_SSHORT;
	nCTipo[18] = 	SQL_C_SSHORT;
	nCTipo[19] = 	SQL_C_SSHORT;
	nCTipo[20] = 	SQL_C_CHAR;
	nCTipo[21] = 	SQL_C_CHAR;
	nCTipo[22] = 	SQL_C_CHAR;
	nCTipo[23] = 	SQL_C_DOUBLE;
	nCTipo[24] = 	SQL_C_DOUBLE;
	nCTipo[25] = 	SQL_C_CHAR;
	nCTipo[26] = 	SQL_C_CHAR;
	nCTipo[27] = 	SQL_C_CHAR;
	nCTipo[28] = 	SQL_C_CHAR;
	nCTipo[29] = 	SQL_C_CHAR;
	nCTipo[30] = 	SQL_C_CHAR;
	nCTipo[31] = 	SQL_C_SLONG;
	nCTipo[32] = 	SQL_C_SSHORT;
	nCTipo[33] = 	SQL_C_SSHORT;
	nCTipo[34] = 	SQL_C_CHAR;
	nCTipo[35] = 	SQL_C_CHAR;
	nCTipo[36] = 	SQL_C_CHAR;
	nCTipo[37] = 	SQL_C_CHAR;
	nCTipo[38] = 	SQL_C_CHAR;
	nCTipo[39] = 	SQL_C_CHAR;
	nCTipo[40] = 	SQL_C_CHAR;
	nCTipo[41] = 	SQL_C_SSHORT;
	
    nLongitud[0] =   5;
    nLongitud[1] =   13; 
    nLongitud[2] =   9;
    nLongitud[3] =   3;
    nLongitud[4] =   3;
    nLongitud[5] =   3;
	nLongitud[6] =   32;
    nLongitud[7] =   32;
    nLongitud[8] =   32;
    nLongitud[9] =   13;
    nLongitud[10] =  20;
    nLongitud[11] =  15;
	nLongitud[12] =  102;
    nLongitud[13] =  3;
    nLongitud[14] =  5;
    nLongitud[15] =  3;
    nLongitud[16] =  5;
    nLongitud[17] =  3;
	nLongitud[18] =  3;
    nLongitud[19] =  3;
    nLongitud[20] =  20;
    nLongitud[21] =  3;
    nLongitud[22] =  20;
    nLongitud[23] =  9;
	nLongitud[24] =  9;
    nLongitud[25] =  17;
    nLongitud[26] =  42;
    nLongitud[27] =  12;
	nLongitud[28] =	 12;	
	nLongitud[29] =	 7;
	nLongitud[30] =	 62;
	nLongitud[31] =  5;
	nLongitud[32] =  3;
	nLongitud[33] =	 3;
	nLongitud[34] =  5;
	nLongitud[35] =  42;
	nLongitud[36] =  22;
	nLongitud[37] =  17;
	nLongitud[38] =  17;
	nLongitud[39] =  14;
	nLongitud[40] =  14;
	nLongitud[41] =  3;

	pVar[0] = 	&foliosolicitud;
	pVar[1] = 	nss;
	pVar[2] = 	&consecutivo;
	pVar[3] = 	&consecbenef;
	pVar[4] = 	&tipopago;
	pVar[5] = 	&parencod;
	pVar[6] = 	paterno;
	pVar[7] = 	materno;
	pVar[8] = 	nombres;
	pVar[9] = 	nssbenef;
	pVar[10] =	curpbenef;
	pVar[11] =	rfcbenef;
	pVar[12] =	correoelect;
	pVar[13] =	&porcentaje;
	pVar[14] =	&tiendacod;
	pVar[15] =	&banco;
	pVar[16] =	&codsucursal;
	pVar[17] =	&codplaza;
	pVar[18] =	&ciudadcod;
	pVar[19] =	&estadcod;
	pVar[20] =	numcuenta;
	pVar[21] =	tipocuenta;
	pVar[22] =	clabe;
	pVar[23] =	&numcheque;
	pVar[24] =	&montoenpesos;
	pVar[25] =	fechapago;
	pVar[26] =	domcalle;
	pVar[27] =	domnumeroext;
	pVar[28] =	domnumeroint;
	pVar[29] =	domcodpos;
	pVar[30] =	domcolonia;
	pVar[31] =	&domdelega;
	pVar[32] =	&domciudadcod;
	pVar[33] =	&domestadocod;
	pVar[34] =	&dompais;
	pVar[35] =	&domtelefono;
	pVar[36] =	numordpago;
	pVar[37] =	fechacaptura;
	pVar[38] =	fechamodifica;
	pVar[39] =	usuariocaptura;
	pVar[40] =	usuariomodifica;
	pVar[41] =	&migracionretparsafre;
	
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
CBeneficiario::~CBeneficiario()
{
	Commit();
}
void CBeneficiario::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
}

