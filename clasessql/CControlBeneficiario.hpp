#ifndef CCONTROLBENEFICIARIO
#define CCONTROLBENEFICIARIO

#include <RecordSet.hpp>
class CControlBeneficiario : public CRecordSet
{
public:
	CControlBeneficiario(C_ODBC *odbc_ext, const char *select=NULL);
    ~CControlBeneficiario();
    void activarCols();

    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[6];
    int nCTipo[6];
    long nLongitud[6];
    long nLongResp[6];
    void *pVar[6];

	int				foliosolicitud;//0
	char			nsstrab[13];//1
	short int		tipobeneficiario;//2
	short int		porcbeneficiario;//3
    	short int       porcentajelegal;//4
	
};
#endif
