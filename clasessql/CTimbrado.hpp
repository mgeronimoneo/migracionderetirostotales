#ifndef CTIMBRADO
#define CTIMBRADO

#include <RecordSet.hpp>
class CTimbrado : public CRecordSet
{
public:
	CTimbrado(C_ODBC *odbc_ext, const char *select=NULL);
    ~CTimbrado();
    void activarCols();
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[8];
    int nCTipo[8];
    long nLongitud[8];
    long nLongResp[8];
    void *pVar[8];
			
	char		cNss[13];
	char		cRfc[15];
	int			iFolioservicio;
	char		cTiposervicio[3];
	short int	iRespuesta;
	short int	iMigracionrettotsafre;
    char        cFechaAlta[21];
};
#endif
