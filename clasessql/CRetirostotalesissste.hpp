#ifndef CRETIROSTOTALESISSSTE
#define CRETIROSTOTALESISSSTE

#include <RecordSet.hpp>
class CRetirostotalesissste : public CRecordSet
{
public:
	CRetirostotalesissste(C_ODBC *odbc_ext, const char *select=NULL);
    ~CRetirostotalesissste();
    void activarCols();
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[40];
    int nCTipo[40];
    long nLongitud[40];
    long nLongResp[40];
    void *pVar[40];

	int			iFolio;
	long		lConsecutivo;
	char		cCurp[20];
	char		cRfc[15];
	char		cNss[13];
	int			iFoliosolicitud;
	char		cNombreafore[42];
	char		cPaterno_afore[42];
	char		cMaterno_afore[42];
	char		cSecpension[4];
	char		cTiporetiro[3];
	char		cRegimen[4];
	char		cTiposeguro[4];
	char		cTipopension[4];
	char		cCvepension[5];
	short int	iTipoprestacion;
	char		cFechainiciopension[12];
	char		cFecharesolucion[12];
	char		cFechasolicitud[12];
	char		cClavedocumentoprobatorio[3];
	char		cFechanacimiento[12];
	char		cAseguradora[5];
	char		cActuario[9];
	char		cNumplanprivado[10];
	int			iPeriodopago;
	short int	iSemanas_cotizadas;
	short int 	iEstadcod;
	short int 	iDelegcod;
	char		cDiagprocesar[5];
	short int 	iGrupo;
	char		cFechacaptura[12];
	char		cUsuariocaptura[17];
	char		cFechamodifica[12];
	char		cUsuariomodifica[17];
	char		cFechaconfirma[12];
	char		cUsuarioconfirma[17];
	short int	iCodigo_rechazo;
	short int	iEstado_solicitud;
	short int	iMigracionrettotsafre;
};
#endif
