#ifndef CBENEFICIARIO
#define CBENEFICIARIO

#include <RecordSet.hpp>
class CBeneficiario : public CRecordSet
{
public:
	CBeneficiario(C_ODBC *odbc_ext, const char *select=NULL);
    ~CBeneficiario();
    void activarCols();

    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[43];
    int nCTipo[43];
    long nLongitud[43];
    long nLongResp[43];
    void *pVar[43];

	int				foliosolicitud;//0
	char			nss[13];//1
	long			consecutivo;//2
	short int		consecbenef;//3
	short int		tipopago;//4
	short int		parencod;//5
	char			paterno[32];//6
	char			materno[32];//7
	char			nombres[32];//8
	char 			nssbenef[13];//9
	char 			curpbenef[20];//10
	char 			rfcbenef[15];//11
	char 			correoelect[102];//12
	short int 		porcentaje;//13
	int 			tiendacod;//14
	short int 		banco;//15
	int 			codsucursal;//16
	short int 		codplaza;//17
	short int		ciudadcod;//18
	short int 		estadcod;//19
	char 			numcuenta[20];//20
	char 			tipocuenta[3];//21
	char 			clabe[20];//22
	double 			numcheque;//23
	double 			montoenpesos;//24
	char 			fechapago[17];//25
	char			domcalle[42];//26
	char 			domnumeroext[12];//27
	char 			domnumeroint[12];//28
	char 			domcodpos[7];//29
	char 			domcolonia[62];//30
	int				domdelega;//31
	short int		domciudadcod;//32
	short int		domestadocod;//33
	char 			dompais[5];//34
	char 			domtelefono[42];//35
	char			numordpago[22];//36
	char			fechacaptura[17];//37
	char			fechamodifica[17];//38
	char			usuariocaptura[14];//39
	char			usuariomodifica[14];//40
	short int		migracionretparsafre;//41
};
#endif
