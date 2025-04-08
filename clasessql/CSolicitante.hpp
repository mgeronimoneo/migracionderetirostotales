#ifndef CSOLICITANTE
#define CSOLICITANTE

#include <RecordSet.hpp>
class CSolicitante : public CRecordSet
{
public:
    CSolicitante(C_ODBC *odbc_ext, const char *select=NULL);
    ~CSolicitante();
    void activarCols();

    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[10];
    int nCTipo[10];
    long nLongitud[10];
    long nLongResp[10];
    void *pVar[10];

    int         iFoliosolicitud;
    char        cCurp[20];
    long        lConsecutivo;
    char        cPaterno[32];
    char        cMaterno[32];
    char        cNombres[32];
    char        cTelefono[42];
    short int   iParencod;
    short int   iMigracionrettotsafre;
};
#endif
