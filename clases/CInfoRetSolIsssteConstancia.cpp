#include "CInfoRetSolIsssteConstancia.hpp"

CInfoRetSolIsssteConstancia::CInfoRetSolIsssteConstancia()
{
	// TODO Auto-generated constructor stub
}

CInfoRetSolIsssteConstancia::~CInfoRetSolIsssteConstancia()
{
	// TODO Auto-generated destructor stub
}

short CInfoRetSolIsssteConstancia::ReplicarRetSolIsssteConstancia(int iFolioServicio, C_ODBC *odbcInfxSafreaf, C_ODBC *odbcServiciosAfore)
{
	CRetirostotalesconstanciaissste objRetConstancia(odbcServiciosAfore);

	char cNss[13] = {0};
	char cConstancia[3] = {0};

	char cSql[1024] = {0};
	char cSqlAux[1024] = {0};
	char cTexto[1024] = {0};

	int iRespuesta = 0;

	objFG.fnArcGrabarLogx(RUTA_LOG, "***********************************ENTRA ISSSTE CONSTANCIA***************************************");
	memset(cTexto, 0, sizeof(cTexto));
	snprintf(cTexto, sizeof(cTexto), "FOLIO QUE SE ESTA MIGRANDO: [%i]", iFolioServicio);
	objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);

	// OBTENCIÓN DE LA INFORMACION QUE SE VA A MIGRAR DE RET SOL ISSSTE CONSTANCIA
	memset(cSql, 0, sizeof(cSql));
	memset(cTexto, 0, sizeof(cTexto));

	snprintf(cSql, sizeof(cSql), "SELECT COALESCE(foliosolicitud,0) AS foliosolicitud, "
								 "TRIM(COALESCE(nss,' '))::char(11) AS nss, "
								 "COALESCE(consecutivo,0) AS consecutivo,"
								 "TRIM(COALESCE(constancia,' '))::char(1) AS constancia "
								 "FROM fnconsultaretsolisssteconstanciareplicart(%i);",
			 iFolioServicio);

	objRetConstancia.ClearResults();
	if (objRetConstancia.Exec(cSql))
	{
		objRetConstancia.activarCols();
		if (objRetConstancia.leer())
		{
			memset(cNss, 0, sizeof(cNss));
			memset(cConstancia, 0, sizeof(cConstancia));

			memmove(cNss, objRetConstancia.cNss, sizeof(cNss));
			memmove(cConstancia, objRetConstancia.cConstancia, sizeof(cConstancia));

			memset(cSqlAux, 0, sizeof(cSqlAux));
			memset(cTexto, 0, sizeof(cTexto));

			if (objRetConstancia.iFoliosolicitud == 0)
			{
				memset(cTexto, 0, sizeof(cTexto));
				snprintf(cTexto, sizeof(cTexto), "NO EXISTE INFORMACION CON EL FOLIO: [%i]", iFolioServicio);
				objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
				objFG.fnArcGrabarLogx(RUTA_LOG, "**************************************************************************");
			}
			else
			{
				snprintf(cSqlAux, sizeof(cSqlAux), "EXECUTE FUNCTION fn_guardarret_sol_issste_constanciareplicart('%s',%i,'%s');",
						 cNss,
						 objRetConstancia.iConsecutivo,
						 cConstancia);

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