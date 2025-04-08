#ifndef CRETIROSTOTALES_HPP_
#define CRETIROSTOTALES_HPP_
#include "../definiciones.hpp"
#include "../struct.hpp"
#include "../../sisaforecoppel/funcionesgenerales/CFuncionesGenerales.hpp"

#include "../clasessql/CMarca.hpp"
#include "../clasessql/CInformacion.hpp"
#include "../clasessql/CInfoMarca.hpp"

#include "../clases/CInfoBeneficiarios.hpp"
#include "../clases/CInfoRetirosTotalesImss.hpp"
#include "../clases/CInfoRecServiciosTimbrado.hpp"
#include "../clases/CInfoRetirosTotalesIssste.hpp"
#include "../clases/CInfoRetTotPmgImss.hpp"
#include "../clases/CInfoRetSolIsssteConstancia.hpp"
#include "../clases/CInfoSolicitante.hpp"
#include "../clases/CInfoRetConstanciaRetencion.hpp"
#include "../clases/CInfoPenDetOp70.hpp"
#include "../clases/CInfoRetFolioInfonavit.hpp"
#include "../clases/CInfoRetNotifVivienda.hpp"
#include "../clases/CInfoRetConformidad.hpp"
#include "../clases/CObtenerCurpSolBeneficiario.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>;
#include <string.h>;

class CRetirostotales {
public:
	CRetirostotales();
	~CRetirostotales();
			
	CFuncionesGenerales objFG;
	
	CInfoBeneficiarios 					objBen;
	CInfoRetirosTotalesImss 				objRetTotImss;
	CInfoRecServiciosTimbrado 			objRecServTimbrado;
	CInfoRetirosTotalesIssste 			objRetTotIssste;
	CInfoRetTotPmgImss 				objRetTotPmgIms;
	CInfoRetSolIsssteConstancia 			objRetSolConstancia;
	CInfoSolicitante 					objSolicitante;
	CInfoRetConstanciaRetencion 			objRetencion;
	CInfoPenDetOp70					objPenDet70;
	CInfoRetFolioInfonavit				objRetFolioInfonavit;
	CInfoRetNotifVivienda				objRetNotVivienda;
	CInfoRetConformidad				objRetConformidad;

	ST_SELLOBIOMETRICO_SUV	stSelloBiometricoSuv;
	
	short ReplicarSolicitudesRetirosTotales(C_ODBC* odbcAforeGlobal, C_ODBC* odbcInfxSafreaf, C_ODBC* odbcServiciosAfore);
	short ReplicarRecServiciosAfore(C_ODBC* odbcAforeGlobal, C_ODBC* odbcInfxSafreaf, C_ODBC* odbcServiciosAfore);
};
#endif
