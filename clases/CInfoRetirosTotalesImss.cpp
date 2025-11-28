#include "CInfoRetirosTotalesImss.hpp"

CInfoRetirosTotalesImss::CInfoRetirosTotalesImss()
{
	// TODO Auto-generated constructor stub
}

CInfoRetirosTotalesImss::~CInfoRetirosTotalesImss()
{
	// TODO Auto-generated destructor stub
}
void CInfoRetirosTotalesImss::setStSelloBiometricoSuv(ST_SELLOBIOMETRICO_SUV *stSuv)
{
	char cTexto[5000] = {0};

	stSelloBiometricoSuv = stSuv;
	// memcpy(stSelloBiometricoSuv,stSuv,sizeof(stSuv));
	if (snprintf(cTexto, sizeof(cTexto), "[%s][%s] stSelloBiometricoSuv: cNss[%s] iIdsolicitante[%i] cCurpSolicitante[%s] cSellotrabajador[%s] cCurpAgente[%s] iConsecutivo[%i]", __FILE__, __FUNCTION__, stSelloBiometricoSuv->cNss, stSelloBiometricoSuv->iIdsolicitante, stSelloBiometricoSuv->cCurpSolicitante, stSelloBiometricoSuv->cSellotrabajador, stSelloBiometricoSuv->cCurpAgente, stSelloBiometricoSuv->iConsecutivo))
	{
		objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
	}
}

void CInfoRetirosTotalesImss::saveSelloBiometricoSuv(C_ODBC *odbcInfxSafreaf)
{
	objFG.fnArcGrabarLogx(RUTA_LOG, "=========== TABLA : RET_SELLOSBIOMETRICOS_SUV ===========");
	char cSql[5000] = {0};
	char cTexto[5000] = {0};
	char cAux[5000] = {0};
	int shRespuesta = 0;

	snprintf(cSql, sizeof(cSql), "EXECUTE FUNCTION fn_guardar_sellosuvtrabajador(1,'%s',%i,'%i','%s','%s','%s',0);",
			 stSelloBiometricoSuv->cNss, stSelloBiometricoSuv->iConsecutivo, stSelloBiometricoSuv->iIdsolicitante, stSelloBiometricoSuv->cCurpSolicitante,
			 stSelloBiometricoSuv->cSellotrabajador, stSelloBiometricoSuv->cCurpAgente); //, stSelloBiometricoSuv->cCurpSolBene);

	if (snprintf(cTexto, sizeof(cTexto), "QUERY: [%s]", cSql))
	{
		objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
	}
	objFG.fnSqlConsultarNumero(odbcInfxSafreaf, cSql, shRespuesta, cAux);

	if (shRespuesta == 1)
	{
		if (snprintf(cTexto, sizeof(cTexto), "SE MIGRO LA INFORMACION CON EL CONSECUTIVO: [%i]", stSelloBiometricoSuv->iConsecutivo))
		{
			objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
		}
	}
	else
	{
		if (snprintf(cTexto, sizeof(cTexto), "NO SE PUDO MIGRAR LA INFORMACION CON EL CONSECUTIVO: [%i] Error[%s]", stSelloBiometricoSuv->iConsecutivo, cAux))
		{
			objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
		}
	}
} /// Termina CInfoRetirosTotalesImss::saveSelloBiometricoSuv()

short CInfoRetirosTotalesImss::ReplicarRetirosTotalesImss(int iFolioServicio, C_ODBC *odbcInfxSafreaf, C_ODBC *odbcServiciosAfore)
{
	CRetirostotalesimss objRetTotImss(odbcServiciosAfore);

	char cNss[13] = {0};
	char cTipoid[3] = {0};
	char cCurp[20] = {0};
	char cSecpension[4] = {0};
	char cTiporetiro[3] = {0};
	char cRegimen[4] = {0};
	char cTiposeguro[4] = {0};
	char cTipopension[4] = {0};
	char cFechainipen[24] = {0};
	char cFecharesolucion[24] = {0};
	char cFechasolicitud[24] = {0};
	char cCvedocprobatorio[3] = {0};
	char cFechanacimiento[24] = {0};
	char cAseguradora[5] = {0};
	char cActuario[9] = {0};
	char cNumplanpension[10] = {0};
	char cFechavalorviv[24] = {0};
	char cDiagregistro[5] = {0};
	char cEstadosubviv[3] = {0};
	char cFechacaptura[24] = {0};
	char cFechaconfirma[24] = {0};
	char cFechamodifica[24] = {0};
	char cFechaenvio[24] = {0};
	char cUsuariocaptura[14] = {0};
	char cUsuarioconfirma[14] = {0};
	char cUsuariomodifica[14] = {0};
	char cCvedestino[3] = {0};
	char cPaternosol[42] = {0};
	char cMaternosol[42] = {0};
	char cNombresol[42] = {0};

	char cSql[3000] = {0};
	char cSqlAux[3000] = {0};
	char cTexto[300] = {0};

	int iRespuesta = 0;

	objFG.fnArcGrabarLogx(RUTA_LOG, "***********************************ENTRA RETIROS TOTALES IMSS***************************************");

	// OBTENCIÓN DE LA INFORMACION QUE SE VA A MIGRAR DE RETIROS TOTALES IMSS
	memset(cTexto, 0, sizeof(cTexto));

	snprintf(cSql, sizeof(cSql), "SELECT nss, "
								 "consecutivo, "
								 "folio, "
								 "foliosolicitud, "
								 "idtipo, "
								 "curp, "
								 "secpension, "
								 "tipodocumento, "
								 "tiporetiro, "
								 "regimen, "
								 "tiposeguro, "
								 "tipopension, "
								 "tipoprestacion, "
								 "fechainipension, "
								 "fecharesolucion, "
								 "fechasolicitud, "
								 "cvedocprobatorio, "
								 "fechanacimiento, "
								 "aseguradora, "
								 "actuario, "
								 "numplanpension, "
								 "periodopago, "
								 "accionesret97, "
								 "accionescv, "
								 "accionescuotasoc, "
								 "accionesret92, "
								 "fechavalorviv,"
								 "saldoviv97, "
								 "saldoviv92, "
								 "saldoviv72, "
								 "diagregistro, "
								 "estadosubviv, "
								 "semanascotizadas, "
								 "estadosolicitud, "
								 "entidad, "
								 "codrechazoent,"
								 "rechazocod, "
								 "fechacaptura, "
								 "fechaconfirma, "
								 "fechamodifica, "
								 "fechaenvio, "
								 "usuariocaptura, "
								 "usuarioconfirma, "
								 "usuariomodifica, "
								 "carta, "
								 "grupo, "
								 "cvedestino, "
								 "porcentajeval, "
								 "numresolucion, "
								 "paternosol, "
								 "maternosol, "
								 "nombresol, "
								 "migracionrettotsafre,"
								 "portabilidad "
								 "FROM fnconsultaretirostotalesimssreplicaportabilidad(%i);",
			 iFolioServicio);

	objRetTotImss.ClearResults();
	if (objRetTotImss.Exec(cSql))
	{
		objRetTotImss.activarCols();
		if (objRetTotImss.leer())
		{

			memset(cNss, 0, sizeof(cNss));
			memset(cTipoid, 0, sizeof(cTipoid));
			memset(cCurp, 0, sizeof(cCurp));
			memset(cSecpension, 0, sizeof(cSecpension));
			memset(cTiporetiro, 0, sizeof(cTiporetiro));
			memset(cRegimen, 0, sizeof(cRegimen));
			memset(cTiposeguro, 0, sizeof(cTiposeguro));
			memset(cTipopension, 0, sizeof(cTipopension));
			memset(cFechainipen, 0, sizeof(cFechainipen));
			memset(cFecharesolucion, 0, sizeof(cFecharesolucion));
			memset(cFechasolicitud, 0, sizeof(cFechasolicitud));
			memset(cCvedocprobatorio, 0, sizeof(cCvedocprobatorio));
			memset(cFechanacimiento, 0, sizeof(cFechanacimiento));
			memset(cAseguradora, 0, sizeof(cAseguradora));
			memset(cActuario, 0, sizeof(cActuario));
			memset(cNumplanpension, 0, sizeof(cNumplanpension));
			memset(cFechavalorviv, 0, sizeof(cFechavalorviv));
			memset(cDiagregistro, 0, sizeof(cDiagregistro));
			memset(cEstadosubviv, 0, sizeof(cEstadosubviv));
			memset(cFechacaptura, 0, sizeof(cFechacaptura));
			memset(cFechaconfirma, 0, sizeof(cFechaconfirma));
			memset(cFechamodifica, 0, sizeof(cFechamodifica));
			memset(cFechaenvio, 0, sizeof(cFechaenvio));
			memset(cUsuariocaptura, 0, sizeof(cUsuariocaptura));
			memset(cUsuarioconfirma, 0, sizeof(cUsuarioconfirma));
			memset(cUsuariomodifica, 0, sizeof(cUsuariomodifica));
			memset(cCvedestino, 0, sizeof(cCvedestino));
			memset(cPaternosol, 0, sizeof(cPaternosol));
			memset(cMaternosol, 0, sizeof(cMaternosol));
			memset(cNombresol, 0, sizeof(cNombresol));

			strncpy(cNss, objRetTotImss.cNss, 11);
			cNss[11] = '\0';
			strncpy(cTipoid, objRetTotImss.cTipoid, 1);
			cTipoid[1] = '\0';
			strncpy(cCurp, objRetTotImss.cCurp, 18);
			cCurp[18] = '\0';
			strncpy(cSecpension, objRetTotImss.cSecpension, 2);
			cSecpension[2] = '\0';
			strncpy(cTiporetiro, objRetTotImss.cTiporetiro, 1);
			cTiporetiro[1] = '\0';
			strncpy(cRegimen, objRetTotImss.cRegimen, 2);
			cRegimen[2] = '\0';
			strncpy(cTiposeguro, objRetTotImss.cTiposeguro, 2);
			cTiposeguro[2] = '\0';
			strncpy(cTipopension, objRetTotImss.cTipopension, 2);
			cTipopension[2] = '\0';

			// memcpy(cFechainipen, objRetTotImss.cFechainipen, 10);
			snprintf(cFechainipen, sizeof(cFechainipen), "%c%c%c%c-%c%c-%c%c",
					 objRetTotImss.cFechainipen[6],
					 objRetTotImss.cFechainipen[7],
					 objRetTotImss.cFechainipen[8],
					 objRetTotImss.cFechainipen[9],
					 objRetTotImss.cFechainipen[0],
					 objRetTotImss.cFechainipen[1],
					 objRetTotImss.cFechainipen[3],
					 objRetTotImss.cFechainipen[4]);

			// memcpy(cFecharesolucion, objRetTotImss.cFecharesolucion, 10);
			snprintf(cFecharesolucion, sizeof(cFecharesolucion), "%c%c%c%c-%c%c-%c%c",
					 objRetTotImss.cFecharesolucion[6],
					 objRetTotImss.cFecharesolucion[7],
					 objRetTotImss.cFecharesolucion[8],
					 objRetTotImss.cFecharesolucion[9],
					 objRetTotImss.cFecharesolucion[0],
					 objRetTotImss.cFecharesolucion[1],
					 objRetTotImss.cFecharesolucion[3],
					 objRetTotImss.cFecharesolucion[4]);

			// memcpy(cFechasolicitud, objRetTotImss.cFechasolicitud, 10);
			snprintf(cFechasolicitud, sizeof(cFechasolicitud), "%c%c%c%c-%c%c-%c%c",
					 objRetTotImss.cFechasolicitud[6],
					 objRetTotImss.cFechasolicitud[7],
					 objRetTotImss.cFechasolicitud[8],
					 objRetTotImss.cFechasolicitud[9],
					 objRetTotImss.cFechasolicitud[0],
					 objRetTotImss.cFechasolicitud[1],
					 objRetTotImss.cFechasolicitud[3],
					 objRetTotImss.cFechasolicitud[4]);

			strncpy(cCvedocprobatorio, objRetTotImss.cCvedocprobatorio, 1);
			cCvedocprobatorio[1] = '\0';
			// memcpy(cFechanacimiento, objRetTotImss.cFechanacimiento, 10);
			snprintf(cFechanacimiento, sizeof(cFechanacimiento), "%c%c%c%c-%c%c-%c%c",
					 objRetTotImss.cFechanacimiento[6],
					 objRetTotImss.cFechanacimiento[7],
					 objRetTotImss.cFechanacimiento[8],
					 objRetTotImss.cFechanacimiento[9],
					 objRetTotImss.cFechanacimiento[0],
					 objRetTotImss.cFechanacimiento[1],
					 objRetTotImss.cFechanacimiento[3],
					 objRetTotImss.cFechanacimiento[4]);

			strncpy(cAseguradora, objRetTotImss.cAseguradora, 3);
			cAseguradora[3] = '\0';
			strncpy(cActuario, objRetTotImss.cActuario, 7);
			cActuario[7] = '\0';
			strncpy(cNumplanpension, objRetTotImss.cNumplanpension, 8);
			cNumplanpension[8] = '\0';

			// memcpy(cFechavalorviv, objRetTotImss.cFechavalorviv, 8);
			snprintf(cFechavalorviv, sizeof(cFechavalorviv), "%c%c%c%c-%c%c-%c%c",
					 objRetTotImss.cFechavalorviv[6],
					 objRetTotImss.cFechavalorviv[7],
					 objRetTotImss.cFechavalorviv[8],
					 objRetTotImss.cFechavalorviv[9],
					 objRetTotImss.cFechavalorviv[0],
					 objRetTotImss.cFechavalorviv[1],
					 objRetTotImss.cFechavalorviv[3],
					 objRetTotImss.cFechavalorviv[4]);

			strncpy(cDiagregistro, objRetTotImss.cDiagregistro, 3);
			cDiagregistro[3] = '\0';
			strncpy(cEstadosubviv, objRetTotImss.cEstadosubviv, 1);
			cEstadosubviv[1] = '\0';

			// memcpy(cFechacaptura, objRetTotImss.cFechacaptura, 10);
			snprintf(cFechacaptura, sizeof(cFechacaptura), "%c%c%c%c-%c%c-%c%c",
					 objRetTotImss.cFechacaptura[6],
					 objRetTotImss.cFechacaptura[7],
					 objRetTotImss.cFechacaptura[8],
					 objRetTotImss.cFechacaptura[9],
					 objRetTotImss.cFechacaptura[0],
					 objRetTotImss.cFechacaptura[1],
					 objRetTotImss.cFechacaptura[3],
					 objRetTotImss.cFechacaptura[4]);

			// memcpy(cFechaconfirma, objRetTotImss.cFechaconfirma, 10);
			snprintf(cFechaconfirma, sizeof(cFechaconfirma), "%c%c%c%c-%c%c-%c%c",
					 objRetTotImss.cFechaconfirma[6],
					 objRetTotImss.cFechaconfirma[7],
					 objRetTotImss.cFechaconfirma[8],
					 objRetTotImss.cFechaconfirma[9],
					 objRetTotImss.cFechaconfirma[0],
					 objRetTotImss.cFechaconfirma[1],
					 objRetTotImss.cFechaconfirma[3],
					 objRetTotImss.cFechaconfirma[4]);

			// memcpy(cFechamodifica, objRetTotImss.cFechamodifica, 10);
			snprintf(cFechamodifica, sizeof(cFechamodifica), "%c%c%c%c-%c%c-%c%c",
					 objRetTotImss.cFechamodifica[6],
					 objRetTotImss.cFechamodifica[7],
					 objRetTotImss.cFechamodifica[8],
					 objRetTotImss.cFechamodifica[9],
					 objRetTotImss.cFechamodifica[0],
					 objRetTotImss.cFechamodifica[1],
					 objRetTotImss.cFechamodifica[3],
					 objRetTotImss.cFechamodifica[4]);

			// memcpy(cFechaenvio, objRetTotImss.cFechaenvio, 10);
			snprintf(cFechaenvio, sizeof(cFechaenvio), "%c%c%c%c-%c%c-%c%c",
					 objRetTotImss.cFechaenvio[6],
					 objRetTotImss.cFechaenvio[7],
					 objRetTotImss.cFechaenvio[8],
					 objRetTotImss.cFechaenvio[9],
					 objRetTotImss.cFechaenvio[0],
					 objRetTotImss.cFechaenvio[1],
					 objRetTotImss.cFechaenvio[3],
					 objRetTotImss.cFechaenvio[4]);

			strncpy(cUsuariocaptura, objRetTotImss.cUsuariocaptura, 12);
			cUsuariocaptura[12] = '\0';
			strncpy(cUsuarioconfirma, objRetTotImss.cUsuarioconfirma, 12);
			cUsuarioconfirma[12] = '\0';
			strncpy(cUsuariomodifica, objRetTotImss.cUsuariomodifica, 12);
			cUsuariomodifica[12] = '\0';
			strncpy(cCvedestino, objRetTotImss.cCvedestino, 1);
			cCvedestino[1] = '\0';
			strncpy(cPaternosol, objRetTotImss.cPaternosol, 40);
			cPaternosol[40] = '\0';
			strncpy(cMaternosol, objRetTotImss.cMaternosol, 40);
			cMaternosol[40] = '\0';
			strncpy(cNombresol, objRetTotImss.cNombresol, 40);
			cNombresol[40] = '\0';

			if (objRetTotImss.iFoliosolicitud == 0)
			{
				if (snprintf(cTexto, sizeof(cTexto), "NO EXISTE INFORMACION CON EL FOLIO: [%i]", iFolioServicio))
				{
					objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
				}
				objFG.fnArcGrabarLogx(RUTA_LOG, "**************************************************************************");
			}
			else
			{

				memset(cTexto, 0, sizeof(cTexto));

				if (objRetTotImss.iGrupo != 0)
				{
					snprintf(cSqlAux, sizeof(cSqlAux), "EXECUTE FUNCTION fn_guardarretirostotalesimssreplicaportabilidad('%s',%ld,%i,%i,'%s','%s','%s',%i,'%s','%s','%s','%s',%i,'%s','%s','%s','%s','%s','%s','%s','%s',%i,%f,%f,%f,%f,'%s',%f,%f,%f,'%s','%s',%i,%i,%i,%i,%i,'%s','%s','%s','%s','%s','%s','%s',%i,%i,'%s',%f,%ld,'%s','%s','%s',%i);",
							 cNss,
							 objRetTotImss.iConsecutivo,
							 objRetTotImss.iFolio,
							 objRetTotImss.iFoliosolicitud,
							 cTipoid,
							 cCurp,
							 cSecpension,
							 objRetTotImss.iTipodocumento,
							 cTiporetiro,
							 cRegimen,
							 cTiposeguro,
							 cTipopension,
							 objRetTotImss.iTipoprestacion,
							 cFechainipen,
							 cFecharesolucion,
							 cFechasolicitud,
							 cCvedocprobatorio,
							 cFechanacimiento,
							 cAseguradora,
							 cActuario,
							 cNumplanpension,
							 objRetTotImss.iPeriodopago,
							 objRetTotImss.dAccionesret97,
							 objRetTotImss.dAccionescv,
							 objRetTotImss.dAccionescuotasoc,
							 objRetTotImss.dAccionesret92,
							 cFechavalorviv,
							 objRetTotImss.dSaldoviv97,
							 objRetTotImss.dSaldoviv92,
							 objRetTotImss.dSaldoviv72,
							 cDiagregistro,
							 cEstadosubviv,
							 objRetTotImss.iSemanascotizadas,
							 objRetTotImss.iEstadosolicitud,
							 objRetTotImss.iEntidad,
							 objRetTotImss.iCodrechazoent,
							 objRetTotImss.iRechazocod,
							 cFechacaptura,
							 cFechaconfirma,
							 cFechamodifica,
							 cFechaenvio,
							 cUsuariocaptura,
							 cUsuarioconfirma,
							 cUsuariomodifica,
							 objRetTotImss.iCarta,
							 objRetTotImss.iGrupo,
							 cCvedestino,
							 objRetTotImss.dPorcentajeval,
							 objRetTotImss.lNumresolucion,
							 cPaternosol,
							 cMaternosol,
							 cNombresol,
							 objRetTotImss.iPortabilidad);

					objFG.fnSqlConsultarNumero(odbcInfxSafreaf, cSqlAux, iRespuesta, cTexto);

					if (iRespuesta == 1)
					{
						if (snprintf(cTexto, sizeof(cTexto), "SE MIGRO LA INFORMACION CON EL FOLIO: [%i]", iFolioServicio))
						{
							objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
						}
						saveSelloBiometricoSuv(odbcInfxSafreaf);
						objFG.fnArcGrabarLogx(RUTA_LOG, "**************************************************************************");
					}
					else
					{
						if (snprintf(cTexto, sizeof(cTexto), "NO SE PUDO MIGRAR LA INFORMACION CON EL FOLIO: [%i]-[%i]-[%s]", iFolioServicio, errno, strerror(errno)))
						{
							objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
						}

						if (snprintf(cTexto, sizeof(cTexto), "QUERY: [%s]", cSqlAux))
						{
							objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
						}
						objFG.fnArcGrabarLogx(RUTA_LOG, "**************************************************************************");
					}
				}
				else
				{
					if (snprintf(cTexto, sizeof(cTexto), "NO SE PUDO MIGRAR LA INFORMACION CON EL FOLIO: [%i] POR QUE NO PERTENECE A UN GRUPO VALIDO", iFolioServicio))
					{
						objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
					}
					objFG.fnArcGrabarLogx(RUTA_LOG, "**************************************************************************");
				}
			}
		}
		else
		{
			if (snprintf(cTexto, sizeof(cTexto), "[%s][%s] Error al leer la informacion que arroja el query: %s %i %s", __FILE__, __FUNCTION__, cSql, errno, strerror(errno)))
			{
				objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
			}
		}
	}
	else
	{
		if (snprintf(cTexto, sizeof(cTexto), "[%s][%s] Error al Ejecutar el Query: %s %i %s", __FILE__, __FUNCTION__, cSql, errno, strerror(errno)))
		{
			objFG.fnArcGrabarLogx(RUTA_LOG, cTexto);
		}
	}
}