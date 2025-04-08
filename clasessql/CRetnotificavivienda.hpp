#ifndef CRETNOTIFICAVIVIENDA
#define CRETNOTIFICAVIVIENDA

#include <RecordSet.hpp>
class CRetnotificavivienda : public CRecordSet
{
public:
	CRetnotificavivienda(C_ODBC *odbc_ext, const char *select=NULL);
    ~CRetnotificavivienda();
    void activarCols();
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[28];
    int nCTipo[28];
    long nLongitud[28];
    long nLongResp[28];
    void *pVar[28];
	
	//char		cFechaalta[12];
	char		cNss[13];
	int			iFoliocarga;
	int			iFoliosolicitud;
	int			iConsecutivo;
	//char		cFolionotifica[31];
	char 		cFoliooperacion[16];
	char		cClabe[20];
	char 		cGrupotrabajador[20];
	char		cSecpension[4];
	char		cRegimen[4];
	char		cTiporetiro[3];
	char		cTiposeguro[4];
	char		cTipopension[4];
	char		cTipoprestacion[4];
	short int	iSemanascotizadas;
	char		cNombre[42];
	char		cPaterno[42];
	char		cMaterno[42];
	char		cRfc[15];
	char		cCurp[20];
	short int	iEntidad;
	short int	iIdbenef;
	char		cNombrebenef[42];
	char		cPaternobenef[42];
	char		cMaternobenef[42];
	char		cRfcbenef[15];
	char		cCurpbenef[20];
	//char		cComentarios[129];
	//char		cReferenciapago[22];
	//char		cObservaciones[129];
	char		cFechacaptura[12];
	//char		cIndicador[3];
	//char		cDiaginfonavit[5];
	//char		cUsuariocarga[17];
	//char		cFechacarga[12];
	//char		cHoracarga[12];
	//short int	iEstado;
	//short int	iMigracionrettotsafre;	
};
#endif