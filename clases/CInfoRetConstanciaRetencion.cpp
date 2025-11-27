#include "CInfoRetConstanciaRetencion.hpp"

CInfoRetConstanciaRetencion::CInfoRetConstanciaRetencion()
{
	// TODO Auto-generated constructor stub
}

CInfoRetConstanciaRetencion::~CInfoRetConstanciaRetencion()
{
	// TODO Auto-generated destructor stub
}

short CInfoRetConstanciaRetencion::ReplicarRetConstanciaRetencion(int iFolioServicio, C_ODBC *odbcInfxSafreaf, C_ODBC *odbcServiciosAfore)
{
	CRetconstanciaretencion objRetencion(odbcServiciosAfore);

	char cFechaAlta[11] = {0};
	char cNss[13] = {0};
	char cRfc[15] = {0};
	char cCurp[20] = {0};
	char cNombreSolicitante[102] = {0};
	char cTipoRetiro[3] = {0};

	char cSql[1024] = {0};
	char cSqlAux[1024] = {0};
	char cSqlUpdate[1024] = {0};
	char cTexto[1024] = {0};
	char cTextoAux[1024] = {0};
	char cTextoUpdate[1024] = {0};

	int iRespuesta = 0;

	objFG.fnArcGrabarLogx(RUTA_LOG, "***********************************ENTRA RET CONSTANCIA RETENCION***************************************");
	memset(cTexto, 0, sizeof(cTexto));
	snprintf(cTexto, sizeof(cTexto), "FOLIO QUE SE ESTA MIGRANDO: [%i]", iFolioServicio);
	objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);

	// OBTENCIÓN DE LA INFORMACION QUE SE VA A MIGRAR DE RET CONSTANCIA RETENCION
	memset(cSql, 0, sizeof(cSql));
	memset(cTexto, 0, sizeof(cTexto));

	snprintf(cSql, sizeof(cSql), "SELECT TRIM(COALESCE(fechaalta,''))::char(10) AS fechaalta, "
								 "COALESCE(foliosolicitud,0) AS foliosolicitud, "
								 "COALESCE(consecutivo,0) AS consecutivo, "
								 "TRIM(COALESCE(nss,''))::char(11) AS nss, "
								 "TRIM(COALESCE(rfc,''))::char(13) AS rfc, "
								 "TRIM(COALESCE(curp,''))::char(18) AS curp, "
								 "TRIM(COALESCE(nombresolicitante,''))::char(100) AS nombresolicitante, "
								 "TRIM(COALESCE(tiporetiro,''))::char(1) AS tiporetiro, "
								 "COALESCE(origenretiro,0) AS origenretiro, "
								 "COALESCE(deduccion,0) AS deduccion, "
								 "COALESCE(idbeneficiario,0) AS idbeneficiario, "
								 "COALESCE(migracionrettotsafre,0) AS migracionrettotsafre "
								 "FROM fnconsultaretconstanciaretencion(%i);",
			 iFolioServicio);

	objRetencion.ClearResults();
	if (objRetencion.Exec(cSql))
	{
		objRetencion.activarCols();
		if (objRetencion.leer())
		{
			memset(cFechaAlta, 0, sizeof(cFechaAlta));
			memset(cNss, 0, sizeof(cNss));
			memset(cRfc, 0, sizeof(cRfc));
			memset(cCurp, 0, sizeof(cCurp));
			memset(cNombreSolicitante, 0, sizeof(cNombreSolicitante));
			memset(cTipoRetiro, 0, sizeof(cTipoRetiro));

			// memcpy(cFechaAlta, objRetencion.cFechaAlta, 10);
			memmove(cNss, objRetencion.cNss, sizeof(cNss));
			memmove(cRfc, objRetencion.cRfc, sizeof(cRfc));
			memmove(cCurp, objRetencion.cCurp, sizeof(cCurp));
			memmove(cNombreSolicitante, objRetencion.cNombreSolicitante, sizeof(cNombreSolicitante));
			memmove(cTipoRetiro, objRetencion.cTipoRetiro, sizeof(cTipoRetiro));

			if (objRetencion.iFolioSolicitud == 0)
			{
				memset(cTexto, 0, sizeof(cTexto));
				snprintf(cTexto, sizeof(cTexto), "NO EXISTE INFORMACION CON EL FOLIO: [%i]", iFolioServicio);
				objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
				objFG.fnArcGrabarLogx(RUTA_LOG, "**************************************************************************");
			}
			else
			{
				memset(cSqlAux, 0, sizeof(cSqlAux));
				memset(cTexto, 0, sizeof(cTexto));

				snprintf(cSqlAux, sizeof(cSqlAux), "EXECUTE FUNCTION fn_afop_guardar_ret_constancia_retencion(%i,%ld,'%s','%s','%s','%s','%s',%i,%i,%i);",
						 objRetencion.iFolioSolicitud,
						 objRetencion.iConsecutivo,
						 cNss,
						 cRfc,
						 cCurp,
						 cNombreSolicitante,
						 cTipoRetiro,
						 objRetencion.iOrigenRetiro,
						 objRetencion.iDeduccion,
						 objRetencion.iIdBeneficiario);

				objFG.fnSqlConsultarNumero(odbcInfxSafreaf, cSqlAux, iRespuesta, cTexto);

				if (iRespuesta == 1)
				{
					memset(cTexto, 0, sizeof(cTexto));
					snprintf(cTexto, sizeof(cTexto), "SE MIGRO LA INFORMACION CON EL FOLIO: [%i]", iFolioServicio);
					objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
					objFG.fnArcGrabarLogx(RUTA_LOG, "**************************************************************************");

					memset(cTextoUpdate, 0, sizeof(cTextoUpdate));
					memset(cSqlUpdate, 0, sizeof(cSqlUpdate));

					snprintf(cFechaAlta, sizeof(cFechaAlta), "%c%c-%c%c-%c%c%c%c",
							 objRetencion.cFechaAlta[5],
							 objRetencion.cFechaAlta[6],
							 objRetencion.cFechaAlta[8],
							 objRetencion.cFechaAlta[9],
							 objRetencion.cFechaAlta[0],
							 objRetencion.cFechaAlta[1],
							 objRetencion.cFechaAlta[2],
							 objRetencion.cFechaAlta[3]);

					snprintf(cSqlUpdate, sizeof(cSqlUpdate), "UPDATE ret_constancia_retencion SET fechaalta = '%s' WHERE folio_solicitud = '%i' AND consecutivo = '%ld'", cFechaAlta, iFolioServicio, objRetencion.iConsecutivo);
					objFG.fnSqlEjecutarScrip(odbcInfxSafreaf, cSqlUpdate, cTextoUpdate);

					memset(cTextoUpdate, 0, sizeof(cTextoUpdate));
					snprintf(cTextoUpdate, sizeof(cTextoUpdate), "ACTUALIZACION DE LA FECHA: [%s]", cSqlUpdate);
					objFG.fnArcGrabarLogx(RUTA_LOG, cTextoUpdate);

					objFG.fnArcGrabarLogx(RUTA_LOG, "**************************************************************************");
				}
				else
				{
					memset(cTexto, 0, sizeof(cTexto));
					snprintf(cTexto, sizeof(cTexto), "NO SE PUDO MIGRAR LA INFORMACION CON EL FOLIO: [%i]", iFolioServicio);
					objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);

					memset(cTexto, 0, sizeof(cTexto));
					snprintf(cTexto, sizeof(cTexto), "QUERY: [%s]", cSqlAux);

					objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
					objFG.fnArcGrabarLogx(RUTA_LOG, "**************************************************************************");
				}
			}
		}
		else
		{
			memset(cTexto, 0, sizeof(cTexto));
			snprintf(cTexto, sizeof(cTexto), "[%s][%s] Error al leer la informacion que arroja el query: %s %i %s", __FILE__, __FUNCTION__, cSql, errno, strerror(errno));
			objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
		}
	}
	else
	{
		memset(cTexto, 0, sizeof(cTexto));
		snprintf(cTexto, sizeof(cTexto), "[%s][%s] Error al Ejecutar el Query: %s %i %s", __FILE__, __FUNCTION__, cSql, errno, strerror(errno));
		objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
	}
}