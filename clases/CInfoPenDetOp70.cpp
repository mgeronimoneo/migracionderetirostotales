#include "CInfoPenDetOp70.hpp"

CInfoPenDetOp70::CInfoPenDetOp70()
{
	// TODO Auto-generated constructor stub
}

CInfoPenDetOp70::~CInfoPenDetOp70()
{
	// TODO Auto-generated destructor stub
}

short CInfoPenDetOp70::ReplicarDetalleOp70(int iFolioServicio,C_ODBC* odbcInfxSafreaf, C_ODBC* odbcServiciosAfore)
{
	CPendetalleop70 objDet70(odbcServiciosAfore);

	char cNss[13]              	 = {0};
	char cCurp[20]               = {0};	
	char cSecPension[4]          = {0};
	char cTipoRetiro[3]          = {0};
	char cRegimen[4]             = {0};
	char cTipoSeguro[4]          = {0};
	char cTipoPension[4]         = {0};
	char cCvePension[5]          = {0};
	char cFechaInicioPen[12]     = {0};
	char cFechaPrimerPago[12]    = {0};
	char cFechaUltimoPago[12]    = {0};
	char cFechaAgotamiento[12]   = {0};
	char cFechaFallecimiento[12] = {0};
	char cDiagOperacion[4]       = {0};
	char cFechaCarga[12]         = {0};
	char cHoraCarga[12]          = {0};
	char cUsuario[17]            = {0};


	char	cSql[2024] 		= {0};
	char	cSqlAux[2024] 	= {0};
	char 	cTexto[2024] 	= {0};

	int 	iRespuesta = 0;

	objFG.fnArcGrabarLogx(RUTA_LOG,"***********************************ENTRA DETALLE OPERACION 70***************************************");
	memset(cTexto,0,sizeof(cTexto));
	snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "FOLIO QUE SE ESTA MIGRANDO: [%i]", iFolioServicio);
	objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);	
							
	//OBTENCIÓN DE LA INFORMACION QUE SE VA A MIGRAR DE PENDETALLE70
	memset(cSql,0,sizeof(cSql));
	memset(cTexto,0,sizeof(cTexto));
	
	snprintf(cSql,  strnlen(cSql, sizeof(cSql)), "SELECT COALESCE(folioenvio, 0)::integer AS folioenvio, "
						  "COALESCE(idtiponotifica, 0)::smallint AS idtiponotifica, "
						  "TRIM(COALESCE(nss, ''))::Char(11) AS nss, "
						  "TRIM(COALESCE(curp,''))::Char(18) AS curp, "
						  "TRIM(COALESCE(secpension,''))::Char(2) AS secpension, "
						  "COALESCE(foliodatamart, 0)::integer AS foliodatamart, "
						  "TRIM(COALESCE(tiporetiro, ''))::Char(1) AS tiporetiro, "
						  "TRIM(COALESCE(regimen ,''))::Char(2) AS regimen, "
						  "TRIM(COALESCE(tiposeguro,''))::Char(2) AS tiposeguro, "
						  "TRIM(COALESCE(tipopension,''))::Char(2) AS tipopension, "
						  "TRIM(COALESCE(cvepension,''))::Char(3) AS cvepension, "
						  "COALESCE(tipoprestacion,0)::smallint AS tipoprestacion, "
						  "TRIM(COALESCE(fechainipen, ''))::Char(10) AS fechainipen, "
						  "TRIM(COALESCE(fechaprimerpago, ''))::Char(10) AS fechaprimerpago, "
						  "COALESCE(mtoretiro97, 0)::double precision AS mtoretiro97, "
						  "COALESCE(mtocv, 0)::double precision AS mtocv, "
						  "COALESCE(mtocs, 0)::double precision AS mtocs, "
						  "COALESCE(saldoretiro97, 0)::double precision AS saldoretiro97, "
						  "COALESCE(nummenpagadas, 0)::smallint AS nummenpagadas, "
						  "COALESCE(saldoretiro97, 0)::double precision AS saldoretiro97, "
						  "COALESCE(saldocv, 0)::double precision AS saldocv, "
						  "COALESCE(saldocs, 0)::double precision AS saldocs, "
						  "COALESCE(saldoviv97, 0)::double precision AS saldoviv97, "
						  "COALESCE(nummencalculadas, 0)::smallint AS nummencalculadas, "
						  "COALESCE(mtototalpmg, 0)::double precision AS mtototalpmg, "
						  "TRIM(COALESCE(fechaultimopago, ''))::Char(10) AS fechaultimopago, "
						  "TRIM(COALESCE(fechaagotamiento, ''))::Char(10) AS fechaagotamiento, "
						  "TRIM(COALESCE(fechafallecimiento, ''))::Char(10) AS fechafallecimiento, "
						  "TRIM(COALESCE(diagoperacion,''))::Char(2) AS diagoperacion, "
						  "COALESCE(codigorechazo, 0)::smallint AS codigorechazo, "
						  "COALESCE(origeninformacion, 0)::smallint AS origeninformacion, "
						  "TRIM(COALESCE(fechacarga, ''))::Char(10) AS fechacarga, "
						  "TRIM(COALESCE(horacarga, ''))::Char(10) AS horacarga, "
						  "TRIM(COALESCE(usuario, ''))::Char(15) AS usuario, "
						  "COALESCE(estado, 0)::smallint AS estado, "
						  "COALESCE(estatusreplica, 0)::smallint AS estatusreplica "
						  "FROM fnconsultapendetalleop70pmgimssreplicart(%i);",iFolioServicio);

	objDet70.ClearResults();
	if(objDet70.Exec(cSql))
	{			
		objDet70.activarCols();
		if(objDet70.leer())
		{
			memset(cNss, 0, sizeof(cNss));
			memset(cCurp, 0, sizeof(cCurp));
			memset(cSecPension, 0, sizeof(cSecPension));
			memset(cTipoRetiro, 0, sizeof(cTipoRetiro));
			memset(cRegimen, 0, sizeof(cRegimen));
			memset(cTipoSeguro, 0, sizeof(cTipoSeguro));
			memset(cTipoPension, 0, sizeof(cTipoPension));
			memset(cCvePension, 0, sizeof(cCvePension));
			memset(cFechaInicioPen, 0, sizeof(cFechaInicioPen));
			memset(cFechaPrimerPago, 0, sizeof(cFechaPrimerPago));
			memset(cFechaUltimoPago, 0, sizeof(cFechaUltimoPago));
			memset(cFechaAgotamiento, 0, sizeof(cFechaAgotamiento));
			memset(cFechaFallecimiento, 0, sizeof(cFechaFallecimiento));
			memset(cDiagOperacion, 0, sizeof(cDiagOperacion));
			memset(cFechaCarga, 0, sizeof(cFechaCarga));
			memset(cHoraCarga, 0, sizeof(cHoraCarga));
			memset(cUsuario, 0, sizeof(cUsuario));

			memmove(cNss, objDet70.nss, sizeof(11));
			memmove(cCurp, objDet70.curp, sizeof(18));
			memmove(cSecPension, objDet70.secpension, sizeof(2));
			memmove(cTipoRetiro, objDet70.tiporetiro, sizeof(1));
			memmove(cRegimen, objDet70.regimen, sizeof(2));
			memmove(cTipoSeguro, objDet70.tiposeguro, sizeof(2));
			memmove(cTipoPension, objDet70.tipopension, sizeof(2));
			memmove(cCvePension,  objDet70.cvepension, sizeof(3));		

			//memcpy(cFechaInicioPen, objDet70.fechainipen,10);
			snprintf(cFechaInicioPen, strnlen(cFechaInicioPen, sizeof(cFechaInicioPen)), "%c%c%c%c-%c%c-%c%c",
					objDet70.fechainipen[6], 
					objDet70.fechainipen[7],
					objDet70.fechainipen[8], 
					objDet70.fechainipen[9],
					objDet70.fechainipen[0],
					objDet70.fechainipen[1],
					objDet70.fechainipen[3],
					objDet70.fechainipen[4]);		

			//memcpy(cFechaPrimerPago, objDet70.fechaprimerpago,10);
			snprintf(cFechaPrimerPago, strnlen(cFechaPrimerPago, sizeof(cFechaPrimerPago)), "%c%c%c%c-%c%c-%c%c",
					objDet70.fechaprimerpago[6], 
					objDet70.fechaprimerpago[7],
					objDet70.fechaprimerpago[8], 
					objDet70.fechaprimerpago[9],
					objDet70.fechaprimerpago[0],
					objDet70.fechaprimerpago[1],
					objDet70.fechaprimerpago[3],
					objDet70.fechaprimerpago[4]);

			//memcpy(cFechaUltimoPago, objDet70.fechaultimopago,10);
			snprintf(cFechaUltimoPago,  strnlen(cFechaUltimoPago, sizeof(cFechaUltimoPago)), "%c%c%c%c-%c%c-%c%c",
					objDet70.fechaultimopago[6], 
					objDet70.fechaultimopago[7],
					objDet70.fechaultimopago[8], 
					objDet70.fechaultimopago[9],
					objDet70.fechaultimopago[0],
					objDet70.fechaultimopago[1],
					objDet70.fechaultimopago[3],
					objDet70.fechaultimopago[4]);

			//memcpy(cFechaAgotamiento, objDet70.fechaagotamiento,10);
			snprintf(cFechaAgotamiento, strnlen(cFechaAgotamiento, sizeof(cFechaAgotamiento)), "%c%c%c%c-%c%c-%c%c",
					objDet70.fechaagotamiento[6], 
					objDet70.fechaagotamiento[7],
					objDet70.fechaagotamiento[8], 
					objDet70.fechaagotamiento[9],
					objDet70.fechaagotamiento[0],
					objDet70.fechaagotamiento[1],
					objDet70.fechaagotamiento[3],
					objDet70.fechaagotamiento[4]);

			//memcpy(cFechaFallecimiento, objDet70.fechafallecimiento,10);
			snprintf(cFechaFallecimiento, strnlen(cFechaFallecimiento, sizeof(cFechaFallecimiento)), "%c%c%c%c-%c%c-%c%c",
					objDet70.fechafallecimiento[6], 
					objDet70.fechafallecimiento[7],
					objDet70.fechafallecimiento[8], 
					objDet70.fechafallecimiento[9],
					objDet70.fechafallecimiento[0],
					objDet70.fechafallecimiento[1],
					objDet70.fechafallecimiento[3],
					objDet70.fechafallecimiento[4]);

			memmove(cDiagOperacion, objDet70.diagoperacion, sizeof(2));

			//memcpy(cFechaCarga, objDet70.fechacarga,10);
			snprintf(cFechaCarga, strnlen(cFechaCarga, sizeof(cFechaCarga)), "%c%c%c%c-%c%c-%c%c",
					objDet70.fechacarga[6], 
					objDet70.fechacarga[7],
					objDet70.fechacarga[8], 
					objDet70.fechacarga[9],
					objDet70.fechacarga[0],
					objDet70.fechacarga[1],
					objDet70.fechacarga[3],
					objDet70.fechacarga[4]);

			memmove(cHoraCarga, objDet70.horacarga, sizeof(10));
			memmove(cUsuario, objDet70.usuario, sizeof(15));

			memset(cSqlAux,0, sizeof(cSqlAux));
			memset(cTexto,0, sizeof(cTexto));
			
			snprintf(cSqlAux, strnlen(cSqlAux, sizeof(cSqlAux)), "EXECUTE FUNCTION fn_guardarpendetalleop70pmgimssreplica(%i,%i,'%s','%s','%s',%i,'%s','%s','%s','%s','%s',%i,'%s','%s',%f,%f,%f,%f,%i,%f,%f,%f,%f,%i,%f,'%s','%s','%s','%s',%i,%i,'%s','%s','%s',%i,%i);",
																objDet70.folioenvio,
																objDet70.idtiponotifica,
																cNss,
																cCurp,
																cSecPension,
																objDet70.foliodatamart,
																cTipoRetiro,
																cRegimen,
																cTipoSeguro,
																cTipoPension,
																cCvePension,
																objDet70.tipoprestacion,
																cFechaInicioPen,
																cFechaPrimerPago,
																objDet70.mtoretiro97,
																objDet70.mtocv,
																objDet70.mtocs,
																objDet70.mtoviv97,
																objDet70.nummenpagadas,
																objDet70.saldoretiro97,
																objDet70.saldocv,
																objDet70.saldocs,
																objDet70.saldoviv97,
																objDet70.nummencalculadas,
																objDet70.mtototalpmg,
																cFechaUltimoPago,
																cFechaAgotamiento,
																cFechaFallecimiento,
																cDiagOperacion,
																objDet70.codigorechazo,
																objDet70.origeninformacion,
																cFechaCarga,
																cHoraCarga,
																cUsuario,
																objDet70.estado,
																objDet70.estatusreplica
																);

			objFG.fnSqlConsultarNumero(odbcInfxSafreaf, cSqlAux, iRespuesta, cTexto);

			if (iRespuesta == 1)
			{
				memset(cTexto, 0, sizeof(cTexto));
				snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "SE MIGRO LA INFORMACION CON EL FOLIO: [%i]", iFolioServicio);
				objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
				objFG.fnArcGrabarLogx(RUTA_LOG,"**************************************************************************");
			}
			else
			{
				memset(cTexto, 0, sizeof(cTexto));
				snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "NO SE PUDO MIGRAR LA INFORMACION CON EL FOLIO: [%i]", iFolioServicio);
				objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);

				memset(cTexto, 0, sizeof(cTexto));
				snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "QUERY: [%s]", cSqlAux);
				
				objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
				objFG.fnArcGrabarLogx(RUTA_LOG,"**************************************************************************");
			}				
		}
		else
		{
			memset(cTexto, 0, sizeof(cTexto));
			snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "[%s][%s] Error al leer la informacion que arroja el query: %s %i %s", __FILE__,__FUNCTION__, cSql, errno, strerror(errno));
			objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
		}		
	}
	else
	{
		memset(cTexto, 0, sizeof(cTexto));
		snprintf(cTexto, strnlen(cTexto, sizeof(cTexto)), "[%s][%s] Error al Ejecutar el Query: %s %i %s", __FILE__,__FUNCTION__, cSql, errno, strerror(errno));
		objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);		
	}
}