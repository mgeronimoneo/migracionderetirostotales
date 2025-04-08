
#ifndef CINFORMACION
#define CINFORMACION

#include <RecordSet.hpp>
class CInformacion : public CRecordSet
{
public:
	CInformacion(C_ODBC *odbc_ext, const char *select=NULL);
    ~CInformacion();
    void activarCols();
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[30];
    int nCTipo[30];
    long nLongitud[30];
    long nLongResp[30];
    void *pVar[30];
	
	int 		iFolioServicio;
	char		cCurp[20] ;
	char		cNss[13];
	int 		iFolioSolicitud;
	int 		iOrigenServicio;
	int 		iCodigoMedio;
	int 		iCodigoTipo;
	int 		iCodigoMotivo;
	char		cTipoServicio[3];
	char		cFechaReclamo[10];
	char		cFechaInicio[10];
	char		cFechaFinEstimada[10];
	char		cFechaFinReal[10];
	int 		iPromotor;
	char		cFechaAlta[10];
	int 		iCodigoTermino;
	short int   iMotivoretiro;
	char		cTipoOperacion[6];
	char		cCurpAgenteServicio[20];
	char		cCurpFuncionario[20];
	char		cSelloVoluntad[16];
	char		cSelloFuncionario[16];
	int 		iTipoGrupoServicio;
	int 		iTipoSolicitante;
	int 		iTipoIdentificador;
	int 		iIdpago;
	int 		iTipoSolicitud;
	char 	cHoraFin[10];
	char		cSellotrabajador[16];				    
};
#endif
