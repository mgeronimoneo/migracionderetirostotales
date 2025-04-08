#ifndef CRETFOLIOINFONAVIT
#define CRETFOLIOINFONAVIT

#include <RecordSet.hpp>
class CRetfolioinfonavit : public CRecordSet
{
public:
	CRetfolioinfonavit(C_ODBC *odbc_ext, const char *select=NULL);
    ~CRetfolioinfonavit();
    void activarCols();
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[9];
    int nCTipo[9];
    long nLongitud[9];
    long nLongResp[9];
    void *pVar[9];
	
	char		cNss[13];
	int			iConsecutivo;
	char		cFolioinfonavit[16];
	int			iFoliosolicitud;
	char		cTiporetiro[3];
	char 		cFechacaptura[12];
	char		cUsuariocaptura[14];
	short int	iMigracionrettotsafre;
};
#endif