#ifndef CRETCONSTANCIARETENCION
#define CRETCONSTANCIARETENCION

#include <RecordSet.hpp>
class CRetconstanciaretencion : public CRecordSet
{
public:
    CRetconstanciaretencion(C_ODBC *odbc_ext, const char *select=NULL);
    ~CRetconstanciaretencion();
    void activarCols();
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[13];
    int nCTipo[13];
    long nLongitud[13];
    long nLongResp[13];
    void *pVar[13];

    char        cFechaAlta[12];
    int         iFolioSolicitud;
    long        iConsecutivo;
    char        cNss[13];
    char        cRfc[15];
    char        cCurp[20];
    char        cNombreSolicitante[102];
    char        cTipoRetiro[3];
    short int   iOrigenRetiro;
    short int   iDeduccion;
    short int   iIdBeneficiario;
    short int   iMigracionRetTotSafre;
    
};
#endif