#include "CInfoRetConformidad.hpp"

CInfoRetConformidad::CInfoRetConformidad()
{
	// TODO Auto-generated constructor stub
}

CInfoRetConformidad::~CInfoRetConformidad()
{
	// TODO Auto-generated destructor stub
}

short CInfoRetConformidad::ReplicarRetConformidad(int iFolioServicio, C_ODBC *odbcInfxSafreaf, C_ODBC *odbcServiciosAfore)
{
	CRetftoconformidad objRetConformidad(odbcServiciosAfore);

	char cNss[13] = {0};
	char cCtaclabe[20] = {0};
	char cNumcuenta[13] = {0};
	char cIdentificacion[4] = {0};
	char cOtraidentificacion[4] = {0};
	char cFolioife[15] = {0};
	char cCveelector[20] = {0};
	char cFechacaptura[20] = {0};
	char cFechamodifica[12] = {0};
	char cFolioinfonavit[16] = {0};
	char cUsuariocaptura[14] = {0};
	char cUsuariomodifica[14] = {0};

	char cSql[2024] = {0};
	char cSqlAux[1024] = {0};
	char cTexto[1024] = {0};

	int iRespuesta = 0;

	objFG.fnArcGrabarLogx(RUTA_LOG, "***********************************ENTRA RET CONFORMIDAD***************************************");
	memset(cTexto, 0, sizeof(cTexto));
	snprintf(cTexto, sizeof(cTexto), "FOLIO QUE SE ESTA MIGRANDO: [%i]", iFolioServicio);
	objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);

	memset(cSql, 0, sizeof(cSql));
	memset(cTexto, 0, sizeof(cTexto));

	snprintf(cSql, sizeof(cSql), "SELECT TRIM( COALESCE(cnss,''))::char(11) AS cnss, "
								 "COALESCE(ifoliosolicitud,0) AS ifoliosolicitud, "
								 "COALESCE(bconsecsolicitud,0) AS bconsecsolicitud, "
								 "COALESCE(bconsecconformidad,0) AS bconsecconformidad, "
								 "COALESCE(ibanco,0) AS ibanco, "
								 "TRIM(COALESCE(cctaclave,''))::char(18) AS cctaclave, "
								 "TRIM(COALESCE(cnumcuenta,''))::char(11) AS cnumcuenta, "
								 "TRIM(COALESCE(cidentificacion,''))::char(2) AS cidentificacion, "
								 "TRIM(COALESCE(cotraidentificacion,''))::char(2) AS cotraidentificacion, "
								 "TRIM(COALESCE(cfolioife,''))::char(13) AS cfolioife, "
								 "TRIM(COALESCE(ccveelector,''))::char(18) AS ccveelector, "
								 "		COALESCE(dmontoenpesos,0) AS cmontoenpesos, "
								 "dfechacaptura::char(10) AS dfechacaptura, "
								 "dfechamodifica::char(10) AS dfechamodifica, "
								 "TRIM(COALESCE(cfolioinfonavit,''))::char(14) AS cfolioinfonavit, "
								 "TRIM(COALESCE(cusuariocaptura,''))::char(12) AS cusuariocaptura, "
								 "TRIM(COALESCE(cusuariomodifica,''))::char(12) AS cusuariomodifica, "
								 "COALESCE(imigracionrettotsafre,0) AS imigracionrettotsafre "
								 "FROM fnconsultaretftoconformidadreplicart(%i);",
			 iFolioServicio);

	objRetConformidad.ClearResults();
	if (objRetConformidad.Exec(cSql))
	{
		objRetConformidad.activarCols();
		if (objRetConformidad.leer())
		{
			memset(cNss, 0, sizeof(cNss));
			memset(cCtaclabe, 0, sizeof(cCtaclabe));
			memset(cNumcuenta, 0, sizeof(cNumcuenta));
			memset(cIdentificacion, 0, sizeof(cIdentificacion));
			memset(cOtraidentificacion, 0, sizeof(cOtraidentificacion));
			memset(cFolioife, 0, sizeof(cFolioife));
			memset(cCveelector, 0, sizeof(cCveelector));
			memset(cFechacaptura, 0, sizeof(cFechacaptura));
			memset(cFechamodifica, 0, sizeof(cFechamodifica));
			memset(cFolioinfonavit, 0, sizeof(cFolioinfonavit));
			memset(cUsuariocaptura, 0, sizeof(cUsuariocaptura));
			memset(cUsuariomodifica, 0, sizeof(cUsuariomodifica));

			memmove(cNss, objRetConformidad.cNss, sizeof(cNss));
			memmove(cCtaclabe, objRetConformidad.cCtaclabe, sizeof(cCtaclabe));
			memmove(cNumcuenta, objRetConformidad.cNumcuenta, sizeof(cNumcuenta));
			memmove(cIdentificacion, objRetConformidad.cIdentificacion, sizeof(cIdentificacion));
			memmove(cOtraidentificacion, objRetConformidad.cOtraidentificacion, sizeof(cOtraidentificacion));
			memmove(cFolioife, objRetConformidad.cFolioife, sizeof(cFolioife));
			memmove(cCveelector, objRetConformidad.cCveelector, sizeof(cCveelector));

			// memcpy(cFechacaptura, objRetConformidad.cFechacaptura, 10);
			snprintf(cFechacaptura, sizeof(cFechacaptura), "MDY(%c%c,%c%c,%c%c%c%c)",
					 objRetConformidad.cFechacaptura[5],
					 objRetConformidad.cFechacaptura[6],
					 objRetConformidad.cFechacaptura[8],
					 objRetConformidad.cFechacaptura[9],
					 objRetConformidad.cFechacaptura[0],
					 objRetConformidad.cFechacaptura[1],
					 objRetConformidad.cFechacaptura[2],
					 objRetConformidad.cFechacaptura[3]);

			memmove(cFechamodifica, objRetConformidad.cFechamodifica, sizeof(cFechamodifica));
			memmove(cFolioinfonavit, objRetConformidad.cFolioinfonavit, sizeof(cFolioinfonavit));
			memmove(cUsuariocaptura, objRetConformidad.cUsuariocaptura, sizeof(cUsuariocaptura));
			memmove(cUsuariomodifica, objRetConformidad.cUsuariomodifica, sizeof(cUsuariomodifica));

			if (objRetConformidad.iFoliosolicitud == 0)
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

				snprintf(cSqlAux, sizeof(cSqlAux), "EXECUTE FUNCTION fn_guardarretftoconformidadreplicart('%s',%i,%i,%i,%i,'%s','%s','%s','%s','%s','%s',%f,%s,'%s','%s');",
						 cNss,
						 objRetConformidad.iFoliosolicitud,
						 objRetConformidad.iConsecsolicitud,
						 objRetConformidad.iConsecconformidad,
						 objRetConformidad.iBanco,
						 cCtaclabe,
						 cNumcuenta,
						 cIdentificacion,
						 cOtraidentificacion,
						 cFolioife,
						 cCveelector,
						 objRetConformidad.dMontoenpesos,
						 cFechacaptura,
						 cUsuariocaptura,
						 cFolioinfonavit);

				objFG.fnSqlConsultarNumero(odbcInfxSafreaf, cSqlAux, iRespuesta, cTexto);

				if (iRespuesta == 1)
				{
					memset(cTexto, 0, sizeof(cTexto));
					snprintf(cTexto, sizeof(cTexto), "SE MIGRO LA INFORMACION CON EL FOLIO: [%i]", iFolioServicio);
					objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
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