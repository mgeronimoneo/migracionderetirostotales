#include "CRetnotificavivienda.hpp"
CRetnotificavivienda::CRetnotificavivienda(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=27;
    odbcRet=TRUE;

	//nSqlTipo[0] X 	SQL_CHAR;
	nSqlTipo[0] = 	SQL_CHAR;
	nSqlTipo[1] = 	SQL_BIGINT;
	nSqlTipo[2] = 	SQL_INTEGER;
	nSqlTipo[3] = 	SQL_BIGINT;
	//nSqlTipo[4] X 	SQL_CHAR;
	nSqlTipo[4] = 	SQL_CHAR;
	nSqlTipo[5] = 	SQL_CHAR;
	nSqlTipo[6] = 	SQL_CHAR;
	nSqlTipo[7] = 	SQL_CHAR;
	nSqlTipo[8] = 	SQL_CHAR;	
	nSqlTipo[9] =	SQL_CHAR;
	nSqlTipo[10] = 	SQL_CHAR;
	nSqlTipo[11] = 	SQL_CHAR;
	nSqlTipo[12] =	SQL_CHAR;
	nSqlTipo[13] =	SQL_SMALLINT;
	nSqlTipo[14] =	SQL_CHAR;
	nSqlTipo[15] =	SQL_CHAR;
	nSqlTipo[16] =	SQL_CHAR;
	nSqlTipo[17] =	SQL_CHAR;
	nSqlTipo[18] = 	SQL_CHAR;
	nSqlTipo[19] = 	SQL_SMALLINT;
	nSqlTipo[20] = 	SQL_SMALLINT;
	nSqlTipo[21] = 	SQL_CHAR;
	nSqlTipo[22] = 	SQL_CHAR;
	nSqlTipo[23] = 	SQL_CHAR;
	nSqlTipo[24] = 	SQL_CHAR;
	nSqlTipo[25] = 	SQL_CHAR;
	//nSqlTipo[27] X 	SQL_CHAR;
	//nSqlTipo[28] X 	SQL_CHAR;
	//nSqlTipo[29] X 	SQL_CHAR;
	nSqlTipo[26] = 	SQL_CHAR;
	//nSqlTipo[31] X 	SQL_CHAR;
	//nSqlTipo[32] X 	SQL_CHAR;
	//nSqlTipo[33] X 	SQL_CHAR;
	//nSqlTipo[34] X 	SQL_CHAR;
	//nSqlTipo[35] X 	SQL_CHAR;
	//nSqlTipo[36] X 	SQL_SMALLINT;
	//nSqlTipo[37] X 	SQL_SMALLINT;

	//nCTipo[0] X 	SQL_C_CHAR;
	nCTipo[0] = 	SQL_C_CHAR;
	nCTipo[1] = 	SQL_C_SBIGINT;;
	nCTipo[2] = 	SQL_C_SLONG;
	nCTipo[3] = 	SQL_C_SBIGINT;;
	//nCTipo[4] X 	SQL_C_CHAR;	
	nCTipo[4] = 	SQL_C_CHAR;
	nCTipo[5] = 	SQL_C_CHAR;
	nCTipo[6] = 	SQL_C_CHAR;
	nCTipo[7] = 	SQL_C_CHAR;
	nCTipo[8] = 	SQL_C_CHAR;	
	nCTipo[9] = 	SQL_C_CHAR;
	nCTipo[10] = 	SQL_C_CHAR;
	nCTipo[11] = 	SQL_C_CHAR;
	nCTipo[12] = 	SQL_C_CHAR;
	nCTipo[13] = 	SQL_C_SSHORT;
	nCTipo[14] = 	SQL_C_CHAR;
	nCTipo[15] = 	SQL_C_CHAR;
	nCTipo[16] = 	SQL_C_CHAR;
	nCTipo[17] = 	SQL_C_CHAR;
	nCTipo[18] = 	SQL_C_CHAR;
	nCTipo[19] = 	SQL_C_SSHORT;
	nCTipo[20] = 	SQL_C_SSHORT;
	nCTipo[21] = 	SQL_C_CHAR;
	nCTipo[22] = 	SQL_C_CHAR;
	nCTipo[23] = 	SQL_C_CHAR;
	nCTipo[24] = 	SQL_C_CHAR;
	nCTipo[25] = 	SQL_C_CHAR;
	//nCTipo[27] X 	SQL_C_CHAR;
	//nCTipo[28] X 	SQL_C_CHAR;
	//nCTipo[29] X 	SQL_C_CHAR;
	nCTipo[26] = 	SQL_C_CHAR;
	//nCTipo[31] X 	SQL_C_CHAR;
	//nCTipo[32] X 	SQL_C_CHAR;
	//nCTipo[33] X 	SQL_C_CHAR;
	//nCTipo[34] X 	SQL_C_CHAR;
	//nCTipo[35] X 	SQL_C_CHAR;
	//nCTipo[36] X 	SQL_C_SSHORT;
	//nCTipo[37] X 	SQL_C_SSHORT;

    //nLongitud[0] X  12;
    nLongitud[0] =  13;
    nLongitud[1] =  9;
    nLongitud[2] =  5;
    nLongitud[3] =  9;
	//nLongitud[4] X  31;
    nLongitud[4] =  16;
    nLongitud[5] =  20;
    nLongitud[6] =  20;
    nLongitud[7] = 4;
    nLongitud[8] = 4;
	nLongitud[9] = 3;
    nLongitud[10] = 4;  
    nLongitud[11] = 4;
    nLongitud[12] = 4;
    nLongitud[13] = 3;
    nLongitud[14] = 42;
	nLongitud[15] = 42;
    nLongitud[16] = 42;
    nLongitud[17] = 15;
    nLongitud[18] = 20;
    nLongitud[19] = 3;
    nLongitud[20] = 3;
	nLongitud[21] = 42;
    nLongitud[22] = 42;
    nLongitud[23] = 42;
    nLongitud[24] = 15;
	nLongitud[25] = 20;
	//nLongitud[27] X 129;
	//nLongitud[28] X 22;
	//nLongitud[29] X 129;
	nLongitud[26] = 12;
	//nLongitud[31] X 3;
	//nLongitud[32] X 5;
	//nLongitud[33] X 17;
	//nLongitud[34] X 12;
	//nLongitud[35] X 12;
	//nLongitud[36] X 3;
	//nLongitud[37] X 3;

	//pVar[0] X cFechaalta;
	pVar[0] = cNss;
	pVar[1] = &iFoliocarga;
	pVar[2] = &iFoliosolicitud;
	pVar[3] = &iConsecutivo;
	//pVar[4] X cFolionotifica;
	pVar[4] = cFoliooperacion;
	pVar[5] = cClabe;
	pVar[6] = cGrupotrabajador;
	pVar[7] = cSecpension;
	pVar[8] = cRegimen;
	pVar[9] = cTiporetiro;
	pVar[10] = cTiposeguro;
	pVar[11] = cTipopension;
	pVar[12] = cTipoprestacion;
	pVar[13] = &iSemanascotizadas;
	pVar[14] = cNombre;
	pVar[15] = cPaterno;
	pVar[16] = cMaterno;
	pVar[17] = cRfc;
	pVar[18] = cCurp;
	pVar[19] = &iEntidad;
	pVar[20] = &iIdbenef;
	pVar[21] = cNombrebenef;
	pVar[22] = cPaternobenef;
	pVar[23] = cMaternobenef;
	pVar[24] = cRfcbenef;
	pVar[25] = cCurpbenef;
	//pVar[27] X cComentarios;
	//pVar[28] X cReferenciapago;
	//pVar[29] X cObservaciones;
	pVar[26] = cFechacaptura;
	//pVar[31] X cIndicador;
	//pVar[32] X cDiaginfonavit;
	//pVar[33] X cUsuariocarga;
	//pVar[34] X cFechacarga;
	//pVar[35] X cHoracarga;
	//pVar[36] X &iEstado;
	//pVar[37] X &iMigracionrettotsafre;

    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
CRetnotificavivienda::~CRetnotificavivienda()
{
	Commit();
}
void CRetnotificavivienda::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
}