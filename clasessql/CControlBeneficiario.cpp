#include "CControlBeneficiario.hpp"
CControlBeneficiario::CControlBeneficiario(C_ODBC *odbc_ext, const char *select) : CRecordSet(odbc_ext)
{
    odbc = odbc_ext;
    nCols=5;
    odbcRet=TRUE;

    nSqlTipo[0] = 	SQL_INTEGER;
	nSqlTipo[1] = 	SQL_CHAR;
	nSqlTipo[2] = 	SQL_SMALLINT;
	nSqlTipo[3] = 	SQL_INTEGER;
	nSqlTipo[4] = 	SQL_INTEGER;
	
	nCTipo[0] = 	SQL_C_SLONG;
	nCTipo[1] = 	SQL_C_CHAR;
	nCTipo[2] = 	SQL_C_SSHORT;
	nCTipo[3] = 	SQL_INTEGER;
	nCTipo[4] = 	SQL_INTEGER;

    nLongitud[0] =   5;
    nLongitud[1] =   13; 
    nLongitud[2] =   3;
    nLongitud[3] =   5;
    nLongitud[4] =   3;

	pVar[0] = 	&foliosolicitud;
	pVar[1] = 	nsstrab;
	pVar[2] = 	&tipobeneficiario;
    pVar[3] = 	&porcbeneficiario;
    pVar[4] = 	&porcentajelegal;
    

	
    if (select != NULL)
    {
        odbcRet = Exec(select);
        activarCols();
    }                                                              
}
CControlBeneficiario::~CControlBeneficiario()
{
	Commit();
}
void CControlBeneficiario::activarCols()
{
    int i;
    for (i=0; i<nCols; i++)                                                              
    {                                                              
        Activar(i, nCTipo[i], pVar[i], nLongitud[i], &nLongResp[i]);
    }                                                              
}

