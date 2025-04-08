#ifndef CRETFTOCONFORMIDAD
#define CRETFTOCONFORMIDAD

#include <RecordSet.hpp>
class CRetftoconformidad : public CRecordSet
{
public:
	CRetftoconformidad(C_ODBC *odbc_ext, const char *select=NULL);
    ~CRetftoconformidad();
    void activarCols();
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[19];
    int nCTipo[19];
    long nLongitud[19];
    long nLongResp[19];
    void *pVar[19];
	
	char		cNss[13];
	int			iFoliosolicitud;
	int			iConsecsolicitud;
	int			iConsecconformidad;
	short int	iBanco;
	char		cCtaclabe[20];
	char		cNumcuenta[13];
	char		cIdentificacion[4];
	char		cOtraidentificacion[4];
	char		cFolioife[15];
	char		cCveelector[20];
	double		dMontoenpesos;
	char		cFechacaptura[12];
	char		cFechamodifica[12];
	char		cFolioinfonavit[16];
	char		cUsuariocaptura[14];
	char		cUsuariomodifica[14];
	short int	iMigracionrettotsafre;
	
};
#endif