#ifndef CRETIROSTOTALESPMGIMSS
#define CRETIROSTOTALESPMGIMSS

#include <RecordSet.hpp>
class CRetirostotalespmgimss : public CRecordSet
{
public:
	CRetirostotalespmgimss(C_ODBC *odbc_ext, const char *select=NULL);
    ~CRetirostotalespmgimss();
    void activarCols();
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[58];
    int nCTipo[58];
    long nLongitud[58];
    long nLongResp[58];
    void *pVar[58];
	
	/***************************pensolicitudpmgimss****************************/
	char		cNss[13];
	int			iConsecutivo;
	int			iSeccontrato;
	int			iFoliocontrato;
	int			iFoliolote;
	int			iFoliosolicitud;
	char		cCurp[20];
	char		cSecpension[4];
	char		cTiporetiro[3];
	char		cRegimen[4];
	char		cTiposeguro[4];
	char		cTipopension[4];
	short int	iTipoprestacion;
	double		dImportemensual;
	char		cFechainipen[12];
	char		cFecharesolucion[12];
	char		cFechasolicitud[12];
	char		cFechapago[12];
	short int	iEstadosubviv;
	char		cDiagregistro[5];
	short int	iGrupo;
	char		cFechacaptura[12];
	char		cHoracaptura[10];
	char		cUsuariocaptura[17];
	char		cFechamodifica[12];
	char		cHoramodifica[10];
	char		cUsuariomodifica[17];
	char		cFechaconfirma[12];
	char		cHoraconfirma[10];
	char		cUsuarioconfirma[17];
	short int	iCodigorechazo;
	short int	iEstadosolicitud;										
	int 		iFoliosolicitudctrdet;/**********************penctrpagodetimss*********************************/
	char 		cNssctrdet[13];
	int 		iConsecutivoctrdet;
	short int 	iSeccontratoctrdet;
	int			iFolioop78;/*X*/
	int			iFolioliquida;
	char		cFechapagoestimada[12];
	char		cFecharecibeop79[12];
	char		cFechaliquida[12];
	short int	iNummensualidad;
	double		dMtopagopesos;
	short int	iMotivocancela;
	short int	iEstado;
	int			iFoliopago;
	char		cMarcaultpago[3];	
	int 		iFoliosolicitudctr;/*************************penctrpagoimss******************************/
	char 		cNssctr[13];
	int 		iConsecutivoctr;
	int 		iFoliolotectr;
	short int 	iEstadoctr;/*X*/
	short int	iNummensualidades;
	double		dPagomensualpesos;
	double		dPagoretroactivopesos;
	double		dDevengadaspesos;
	int			iTipocontrato;
};
#endif
