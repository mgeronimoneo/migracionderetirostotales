#include "CInformacion.hpp"
CInformacion::CInformacion(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=29;
    odbcRet=TRUE;
	
	nSqlTipo[0] = 	SQL_INTEGER;
    nSqlTipo[1] = 	SQL_CHAR;
    nSqlTipo[2] = 	SQL_CHAR;
    nSqlTipo[3] = 	SQL_INTEGER;
    nSqlTipo[4] = 	SQL_INTEGER;
    nSqlTipo[5] = 	SQL_INTEGER;
    nSqlTipo[6] = 	SQL_INTEGER;
    nSqlTipo[7] = 	SQL_INTEGER;
    nSqlTipo[8] = 	SQL_CHAR;
    nSqlTipo[9] = 	SQL_CHAR;
	nSqlTipo[10] = 	SQL_CHAR;
	nSqlTipo[11] = 	SQL_CHAR;
    nSqlTipo[12] = 	SQL_CHAR;
    nSqlTipo[13] = 	SQL_INTEGER;
    nSqlTipo[14] = 	SQL_CHAR;
	nSqlTipo[15] = 	SQL_INTEGER;
	nSqlTipo[16] = 	SQL_SMALLINT;//
	nSqlTipo[17] = 	SQL_CHAR;
	nSqlTipo[18] = 	SQL_CHAR;
	nSqlTipo[19] = 	SQL_CHAR;
	nSqlTipo[20] = 	SQL_CHAR;
	nSqlTipo[21] = 	SQL_CHAR;
	nSqlTipo[22] = 	SQL_INTEGER;
	nSqlTipo[23] = 	SQL_INTEGER;
	nSqlTipo[24] = 	SQL_INTEGER;
	nSqlTipo[25] = 	SQL_INTEGER;
	nSqlTipo[26] = 	SQL_INTEGER;
	nSqlTipo[27] = 	SQL_CHAR;
	nSqlTipo[28] = 	SQL_CHAR;
	
	nCTipo[0] = 	SQL_C_SLONG;
    nCTipo[1] = 	SQL_C_CHAR;
    nCTipo[2] = 	SQL_C_CHAR;
    nCTipo[3] = 	SQL_C_SLONG;
    nCTipo[4] = 	SQL_C_SLONG;
    nCTipo[5] = 	SQL_C_SLONG;
    nCTipo[6] = 	SQL_C_SLONG;
    nCTipo[7] = 	SQL_C_SLONG;
    nCTipo[8] = 	SQL_C_CHAR;
    nCTipo[9] = 	SQL_C_CHAR;
	nCTipo[10] = 	SQL_C_CHAR;
	nCTipo[11] = 	SQL_C_CHAR;
    nCTipo[12] = 	SQL_C_CHAR;
    nCTipo[13] = 	SQL_C_SLONG;
    nCTipo[14] = 	SQL_C_CHAR;
	nCTipo[15] = 	SQL_C_SLONG;
	nCTipo[16] = 	SQL_C_SSHORT;//
	nCTipo[17] = 	SQL_C_CHAR;
	nCTipo[18] = 	SQL_C_CHAR;
	nCTipo[19] = 	SQL_C_CHAR;
	nCTipo[20] = 	SQL_C_CHAR;
	nCTipo[21] = 	SQL_C_CHAR;
	nCTipo[22] = 	SQL_C_SLONG;
	nCTipo[23] = 	SQL_C_SLONG;
	nCTipo[24] = 	SQL_C_SLONG;
	nCTipo[25] = 	SQL_C_SLONG;
	nCTipo[26] = 	SQL_C_SLONG;
	nCTipo[27] = 	SQL_C_CHAR;
	nCTipo[28] = 	SQL_C_CHAR;			  
	
	nLongitud[0] = 5;
    nLongitud[1] = 20;
    nLongitud[2] = 13;
    nLongitud[3] = 5;
    nLongitud[4] = 3;
    nLongitud[5] = 3;
    nLongitud[6] = 3;
    nLongitud[7] = 3;
    nLongitud[8] = 3; 
    nLongitud[9] = 10;
	nLongitud[10] = 10;
   	nLongitud[11]=  10;
    nLongitud[12] = 10;
    nLongitud[13] = 5;
    nLongitud[14] = 10;
	nLongitud[15] = 3;
	nLongitud[16] = 3;//
	nLongitud[17] = 6;
	nLongitud[18] = 20;
	nLongitud[19] = 20;
	nLongitud[20] = 16;
	nLongitud[21] = 16;
	nLongitud[22] = 5;
	nLongitud[23] = 5;
	nLongitud[24] = 5;
	nLongitud[25] = 5;
	nLongitud[26] = 5;
	nLongitud[27] = 10;
	nLongitud[28] = 16;		  
	
	pVar[0] =   &iFolioServicio;
	pVar[1] =   cCurp;
	pVar[2] =   cNss;
	pVar[3] =   &iFolioSolicitud;
	pVar[4] =   &iOrigenServicio;
	pVar[5] =   &iCodigoMedio;
	pVar[6] =   &iCodigoTipo;
	pVar[7] =   &iCodigoMotivo;
	pVar[8] =   cTipoServicio;
    pVar[9] =   cFechaReclamo;
	pVar[10] =  cFechaInicio;
	pVar[11] =  cFechaFinEstimada;
	pVar[12] =  cFechaFinReal;
	pVar[13] =  &iPromotor;
	pVar[14] =  cFechaAlta;
	pVar[15] =  &iCodigoTermino;
	pVar[16] =  &iMotivoretiro;//
	pVar[17] =  cTipoOperacion;
	pVar[18] =  cCurpAgenteServicio;
	pVar[19] =  cCurpFuncionario;
	pVar[20] =  cSelloVoluntad;
	pVar[21] =  cSelloFuncionario;
	pVar[22] =  &iTipoGrupoServicio;
	pVar[23] =  &iTipoSolicitante;
	pVar[24] =  &iTipoIdentificador;
	pVar[25] =  &iIdpago;
	pVar[26] =  &iTipoSolicitud;
	pVar[27] =  &cHoraFin;
	pVar[28] =  cSellotrabajador;				
	
	if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }   	
}
CInformacion::~CInformacion()
{
	Commit();
}
void CInformacion::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
}