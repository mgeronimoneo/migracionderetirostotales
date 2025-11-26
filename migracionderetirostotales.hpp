#ifndef MIGRACIONDERETIROSTOTALES_HPP_
#define MIGRACIONDERETIROSTOTALES_HPP_

#include "definiciones.hpp"
#include "../sisaforecoppel/funcionesgenerales/CFuncionesGenerales.hpp"
#include "CUtileriasAfo.hpp"
#include "clases/CRetirostotales.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> //Para Redondear Cantidades

short shRet;

C_ODBC odbcAdmonAfo;
C_ODBC odbcServiciosAfore;
C_ODBC odbcAforeGlobal;
C_ODBC odbcInfxSafreaf;

char cIp[30], cIpIfx[40], cSql[2024], cIp1[30], cIp2[30], cTexto[1024];
char cIpAdmonAfore[30];
char cIpAforeGlobal[30];
char cOutTexto[102];
int iTipoReplica = 0;
int arrOpciones[TOTAL_OPCIONES];

CRetirostotales objRes;
CFuncionesGenerales fns;

short obtenerConexionBaseDato();

#endif