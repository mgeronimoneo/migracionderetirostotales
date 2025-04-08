PATH_LIB		=	/sysx/proyectos/afore/migracionretirostotales
CC      		=	g++
CFLAGS  		=	-Wall -W -o4 -fpack-struct=1 -fPIC -g -w
INCLUDE		=	-I/usr/local/lib64 -I/usr/include -I/usr/local/include -I./ -I/sysx/proyectos/include -I./clases -I./clasessql
LIBSC++ 	=	-lodbc /sysx/progs/afore/librerias/cfuncionesgenerales.so
OBJ_X64		=	/sysx/proyectos/include/x86_64

all:
	@rm -f ./bin/*	
	#=============  ClasesSql ====================================
	$(CC) $(CFLAGS) $(INCLUDE) -c -o ./bin/CInformacion.o clasessql/CInformacion.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c -o ./bin/CMarca.o clasessql/CMarca.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c -o ./bin/CBeneficiario.o clasessql/CBeneficiario.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c -o ./bin/CControlBeneficiario.o clasessql/CControlBeneficiario.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c -o ./bin/CRetirostotalesimss.o clasessql/CRetirostotalesimss.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c -o ./bin/CTimbrado.o clasessql/CTimbrado.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c -o ./bin/CRetirostotalesissste.o clasessql/CRetirostotalesissste.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c -o ./bin/CRetirostotalespmgimss.o clasessql/CRetirostotalespmgimss.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c -o ./bin/CRetirostotalesconstanciaissste.o clasessql/CRetirostotalesconstanciaissste.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c -o ./bin/CSolicitante.o clasessql/CSolicitante.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c -o ./bin/CRetconstanciaretencion.o clasessql/CRetconstanciaretencion.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c -o ./bin/CInfoMarca.o clasessql/CInfoMarca.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c -o ./bin/CPendetalleop70.o clasessql/CPendetalleop70.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c -o ./bin/CRetfolioinfonavit.o clasessql/CRetfolioinfonavit.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c -o ./bin/CRetnotificavivienda.o clasessql/CRetnotificavivienda.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c -o ./bin/CRetftoconformidad.o clasessql/CRetftoconformidad.cpp
	#=============================================================
	
	#=============  Clases =======================================
	$(CC) $(CFLAGS) $(INCLUDE) -c -o ./bin/CRetirostotales.o clases/CRetirostotales.cpp	
	$(CC) $(CFLAGS) $(INCLUDE) -c -o ./bin/CInfoBeneficiarios.o clases/CInfoBeneficiarios.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c -o ./bin/CInfoRetirosTotalesImss.o clases/CInfoRetirosTotalesImss.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c -o ./bin/CInfoRecServiciosTimbrado.o clases/CInfoRecServiciosTimbrado.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c -o ./bin/CInfoRetirosTotalesIssste.o clases/CInfoRetirosTotalesIssste.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c -o ./bin/CInfoRetTotPmgImss.o clases/CInfoRetTotPmgImss.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c -o ./bin/CInfoRetSolIsssteConstancia.o clases/CInfoRetSolIsssteConstancia.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c -o ./bin/CInfoSolicitante.o clases/CInfoSolicitante.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c -o ./bin/CInfoRetConstanciaRetencion.o clases/CInfoRetConstanciaRetencion.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c -o ./bin/CInfoPenDetOp70.o clases/CInfoPenDetOp70.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c -o ./bin/CInfoRetFolioInfonavit.o clases/CInfoRetFolioInfonavit.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c -o ./bin/CInfoRetNotifVivienda.o clases/CInfoRetNotifVivienda.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c -o ./bin/CInfoRetConformidad.o clases/CInfoRetConformidad.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c -o ./bin/CObtenerCurpSolBeneficiario.o clases/CObtenerCurpSolBeneficiario.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c -o ./bin/migracionderetirostotales.o migracionderetirostotales.cpp
	#=============================================================
	
	#=============  Binario =======================================
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBSC++) -o ./bin/migracionderetirostotales ./bin/migracionderetirostotales.o \
	$(OBJ_X64)/SqlTime.o $(OBJ_X64)/RecordSet.o $(OBJ_X64)/C_ODBC.o $(OBJ_X64)/md5.o \
	 ./bin/CRetirostotales.o ./bin/CInfoBeneficiarios.o ./bin/CInfoRetirosTotalesImss.o ./bin/CControlBeneficiario.o \
	 ./bin/CInformacion.o ./bin/CMarca.o ./bin/CBeneficiario.o ./bin/CRetirostotalesimss.o ./bin/CTimbrado.o ./bin/CInfoRecServiciosTimbrado.o \
	 ./bin/CRetirostotalesissste.o ./bin/CInfoRetirosTotalesIssste.o ./bin/CRetirostotalespmgimss.o ./bin/CInfoRetTotPmgImss.o \
	 ./bin/CRetirostotalesconstanciaissste.o ./bin/CInfoRetSolIsssteConstancia.o ./bin/CSolicitante.o ./bin/CInfoSolicitante.o \
	 ./bin/CRetconstanciaretencion.o ./bin/CInfoRetConstanciaRetencion.o ./bin/CInfoMarca.o ./bin/CPendetalleop70.o ./bin/CRetfolioinfonavit.o ./bin/CInfoRetFolioInfonavit.o \
	 ./bin/CRetnotificavivienda.o ./bin/CInfoRetNotifVivienda.o ./bin/CRetftoconformidad.o ./bin/CInfoRetConformidad.o \
	 ./bin/CInfoPenDetOp70.o ./bin/CObtenerCurpSolBeneficiario.o
	#=============================================================
	
	@rm -f ./bin/*.o
	@cp ./bin/migracionderetirostotales $(PATH_LIB)
	@echo "======================================================="
	@echo "=            ! ! !    E X I T O   ! ! !               ="
	@echo "=======================================================" 