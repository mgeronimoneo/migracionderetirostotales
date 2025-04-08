#ifndef CPENDETALLEOP70
#define CPENDETALLEOP70

#include <RecordSet.hpp>
class CPendetalleop70 : public CRecordSet
{
public:
	CPendetalleop70(C_ODBC *odbc_ext, const char *select=NULL);
    ~CPendetalleop70();
    void activarCols();

    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[37];
    int nCTipo[37];
    long nLongitud[37];
    long nLongResp[37];
    void *pVar[37];

	int			folioenvio;
	int			idtiponotifica;
	char		nss[13];
	char		curp[20];
	char		secpension[4];
	int 		foliodatamart;
	char 		tiporetiro[3];
	char 		regimen[4];
	char 		tiposeguro[4];
	char 		tipopension[4];
	char 		cvepension[5];
	short int 	tipoprestacion;
	char 		fechainipen[12];
	char 		fechaprimerpago[12];
	double		mtoretiro97;
	double		mtocv;
	double 		mtocs;
	double 		mtoviv97;
	short int 	nummenpagadas;
	double 		saldoretiro97;
	double 		saldocv;
	double 		saldocs;
	double 		saldoviv97;
	short int   nummencalculadas;
	double 		mtototalpmg;
	char 		fechaultimopago[12];
	char 		fechaagotamiento[12];
	char 		fechafallecimiento[12];
	char 		diagoperacion[4];
	short int   codigorechazo;
	short int   origeninformacion;
	char		fechacarga[12];
	char 		horacarga[12];
	char 		usuario[17];
	short int 	estado;
	short int   estatusreplica;

};
#endif
