#ifndef CRETIROSTOTALESIMSS
#define CRETIROSTOTALESIMSS

#include <RecordSet.hpp>
class CRetirostotalesimss : public CRecordSet
{
public:
	CRetirostotalesimss(C_ODBC *odbc_ext, const char *select=NULL);
    ~CRetirostotalesimss();
    void activarCols();
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[54];
    int nCTipo[54];
    long nLongitud[54];
    long nLongResp[54];
    void *pVar[54];
	
	char		cNss[13];
	int			iConsecutivo;
	int			iFolio;
	int			iFoliosolicitud;
	char		cTipoid[3];
	char		cCurp[20];
	char		cSecpension[4];
	short int	iTipodocumento;
	char		cTiporetiro[3];
	char		cRegimen[4];
	char		cTiposeguro[4];
	char		cTipopension[4];
	short int	iTipoprestacion;
	char		cFechainipen[12];
	char		cFecharesolucion[12];
	char		cFechasolicitud[12];
	char		cCvedocprobatorio[3];
	char		cFechanacimiento[12];
	char		cAseguradora[5];
	char		cActuario[9];
	char		cNumplanpension[10];
	int			iPeriodopago;
	double		dAccionesret97;
	double		dAccionescv;
	double		dAccionescuotasoc;
	double		dAccionesret92;
	char		cFechavalorviv[12];
	double		dSaldoviv97;
	double		dSaldoviv92;
	double		dSaldoviv72;
	char		cDiagregistro[5];
	char		cEstadosubviv[3];
	short int	iSemanascotizadas;
	short int	iEstadosolicitud;
	short int	iEntidad;
	short int	iCodrechazoent;
	short int	iRechazocod;
	char		cFechacaptura[12];
	char		cFechaconfirma[12];
	char		cFechamodifica[12];
	char		cFechaenvio[12];
	char		cUsuariocaptura[14];
	char		cUsuarioconfirma[14];
	char		cUsuariomodifica[14];
	short int	iCarta;
	short int	iGrupo;
	char		cCvedestino[3];
	double		dPorcentajeval;
	long		lNumresolucion;
	char		cPaternosol[42];
	char		cMaternosol[42];
	char		cNombresol[42];
	short int	iEstatusreplica;
};
#endif