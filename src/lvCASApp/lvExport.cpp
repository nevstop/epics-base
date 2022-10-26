/*
 * glbFunction.cpp
 *
 *  Created on: Jul 24, 2013
 *      Author: Kai Yang
 */
#include "lvCASDef.h"
#define epicsExportSharedSymbols
#include "shareLib.h"
#ifdef __cplusplus
extern "C" {
#endif
using namespace lvCASInterface;

int createCAS(const char* pname,const char* dbdFile,void** pcas)
{
	*pcas = new lvCAS(pname,dbdFile);
	assert(*pcas);
	return 0;
}

int loadDbFile(void* pcas,const char* file)
{
	return (lvCAS*)pcas->loadDbFile(file);
}

void installCallback(void* pcas,caCallback callback)
{
	(lvCAS*)pcas->installCallback(callback);
}

int startCAS(void* pcas)
{
	(lvCAS*)pcas->startCAS();
	return 0;
}
int stopCAS(void* pcas)
{
	(lvCAS*)pcas->stopCAS();
	return 0;
}

int closeCAS(void* pcas)
{
	delete pcas;
	return 0;
}

caStatus readI8(void* pcas,const char* pvname,aitInt8 *value)
{
	lvPV* pPV = (lvCAS*)pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddScalar(gddAppType_value,aitEnumInt8);
	assert(pdd);
	caStatus s = pPV->getValue(*pdd);
	pdd->getConvert(*value);
	pdd->unreference();
	return s;
}

caStatus readU8(void* pcas,const char* pvname,aitUint8 *value)
{
	return readI8(pcas,pvname,(aitInt8*)value);
}

caStatus readI16(void* pcas,const char* pvname,aitInt16 *value)
{
	lvPV* pPV = (lvCAS*)pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddScalar(gddAppType_value,aitEnumInt16);
	assert(pdd);
	caStatus s = pPV->getValue(*pdd);
	pdd->getConvert(*value);
	pdd->unreference();
	return s;
}

caStatus readU16(void* pcas,const char* pvname,aitUint16 *value)
{
	return readI16(pcas,pvname,(aitInt16*)value);
}

caStatus readI32(void* pcas,const char* pvname,aitInt32 *value)
{
	lvPV* pPV = (lvCAS*)pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddScalar(gddAppType_value,aitEnumInt32);
	assert(pdd);
	caStatus s = pPV->getValue(*pdd);
	pdd->getConvert(*value);
	pdd->unreference();
	return s;
}

caStatus readU32(void* pcas,const char* pvname,aitUint32 *value)
{
	return readI32(pcas,pvname,(aitInt32*)value);
}

caStatus readFloat32(void* pcas,const char* pvname,aitFloat32 *value)
{
	lvPV* pPV = (lvCAS*)pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddScalar(gddAppType_value,aitEnumFloat32);
	assert(pdd);
	caStatus s = pPV->getValue(*pdd);
	pdd->getConvert(*value);
	pdd->unreference();
	return s;
}

caStatus readFloat64(void* pcas,const char* pvname,aitFloat64 *value)
{
	lvPV* pPV = (lvCAS*)pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddScalar(gddAppType_value,aitEnumFloat64);
	assert(pdd);
	caStatus s = pPV->getValue(*pdd);
	pdd->getConvert(*value);
	pdd->unreference();
	return s;
}

caStatus readString(void* pcas,const char* pvname,char *buffer,const int len)
{
	lvPV* pPV = (lvCAS*)pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddScalar(gddAppType_value,aitEnumString);
	assert(pdd);
	caStatus s = pPV->getValue(*pdd);
	aitString str(buffer,aitStrRef,0,len);
	pdd->getConvert(str);
	pdd->unreference();
	return s;
}

caStatus writeI8(void* pcas,const char* pvname, aitInt8 value)
{
	lvPV* pPV = (lvCAS*)pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddScalar(gddAppType_value,aitEnumInt8);
	assert(pdd);
	pdd->put(value);
	caStatus s = pPV->setValue(*pdd);
	pdd->unreference();
	return s;
}

caStatus writeU8(void* pcas,const char* pvname, aitUint8 value)
{
	return writeI8(pcas,pvname,value);
}

caStatus writeI16(void* pcas,const char* pvname,aitInt16 value)
{
	lvPV* pPV = (lvCAS*)pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddScalar(gddAppType_value,aitEnumInt16);
	assert(pdd);
	pdd->put(value);
	caStatus s = pPV->setValue(*pdd);
	pdd->unreference();
	return s;
}

caStatus writeU16(void* pcas,const char* pvname,aitUint16 value)
{
	return writeI16(pcas,pvname,value);
}

caStatus writeI32(void* pcas,const char* pvname,aitInt32 value)
{
	lvPV* pPV = (lvCAS*)pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddScalar(gddAppType_value,aitEnumInt32);
	assert(pdd);
	pdd->put(value);
	caStatus s = pPV->setValue(*pdd);
	pdd->unreference();
	return s;
}

caStatus writeU32(void* pcas,const char* pvname,aitUint32 value)
{
	return writeI32(pcas,pvname,value);
}

caStatus writeFloat32(void* pcas,const char* pvname,aitFloat32 value)
{
	lvPV* pPV = (lvCAS*)pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddScalar(gddAppType_value,aitEnumFloat32);
	assert(pdd);
	pdd->put(value);
	caStatus s = pPV->setValue(*pdd);
	pdd->unreference();
	return s;
}
caStatus writeFloat64(void* pcas,const char* pvname,aitFloat64 value)
{
	lvPV* pPV = (lvCAS*)pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddScalar(gddAppType_value,aitEnumFloat64);
	assert(pdd);
	pdd->put(value);
	caStatus s = pPV->setValue(*pdd);
	pdd->unreference();
	return s;
}

caStatus writeString(void* pcas,const char* pvname,const char *stringIn)
{
	lvPV* pPV = (lvCAS*)pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddScalar(gddAppType_value,aitEnumString);
	assert(pdd);
	aitString str(stringIn,aitStrRefConst);
	pdd->put(str);
	caStatus s = pPV->setValue(*pdd);
	pdd->unreference();
	return s;
}


caStatus readI8Array(void* pcas,const char* pvname,aitInt8 *value,const int len)
{
	lvPV* pPV = (lvCAS*)pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddAtomic(gddAppType_value,aitEnumInt8,1u,len);
	pdd->putRef(value);
	assert(pdd);
	caStatus s = pPV->getValue(*pdd);
	pdd->unreference();
	return s;
}

caStatus readU8Array(void* pcas,const char* pvname,aitUint8 *value,const int len)
{
	return readI8Array(pcas,pvname,(aitInt8 *)value,len);
}

caStatus readI16Array(void* pcas,const char* pvname,aitInt16 *value,int len)
{
	lvPV* pPV = (lvCAS*)pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddAtomic(gddAppType_value,aitEnumInt16,1u,len);
	assert(pdd);
	pdd->putRef(value);
	caStatus s = pPV->getValue(*pdd);
	pdd->unreference();
	return s;
}

caStatus readU16Array(void* pcas,const char* pvname,aitUint16 *value,const int len)
{
	return readI16Array(pcas,pvname,(aitInt16 *)value,len);
}

caStatus readI32Array(void* pcas,const char* pvname,aitInt32 *value,const int len)
{
	lvPV* pPV = (lvCAS*)pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddAtomic(gddAppType_value,aitEnumInt32,1u,len);
	assert(pdd);
	pdd->putRef(value);
	caStatus s = pPV->getValue(*pdd);
	pdd->unreference();
	return s;
}


caStatus readU32Array(void* pcas,const char* pvname,aitUint32 *value,const int len)
{
	return readI32Array(pcas,pvname,(aitInt32 *)value,len);
}

caStatus readFloat32Array(void* pcas,const char* pvname,aitFloat32 *value,const int len)
{
	lvPV* pPV = (lvCAS*)pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddAtomic(gddAppType_value,aitEnumFloat32,1u,len);
	assert(pdd);
	pdd->putRef(value);
	caStatus s = pPV->getValue(*pdd);
	pdd->unreference();
	return s;
}

caStatus readFloat64Array(void* pcas,const char* pvname,aitFloat64 *value,const int len)
{
	lvPV* pPV = (lvCAS*)pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddAtomic(gddAppType_value,aitEnumFloat64,1u,len);
	assert(pdd);
	pdd->putRef(value);
	caStatus s = pPV->getValue(*pdd);
	pdd->unreference();
	return s;
}


caStatus writeI8Array(void* pcas,const char* pvname,aitInt8 *value,int len)
{
	lvPV* pPV = (lvCAS*)pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddAtomic(gddAppType_value,aitEnumInt8,1u,len);
	assert(pdd);
	pdd->putRef(value);
	caStatus s = pPV->setValue(*pdd);
	pdd->unreference();
	return s;
}

caStatus writeU8Array(void* pcas,const char* pvname,aitUint8 *value,const int len)
{
	return writeI8Array(pcas,pvname,(aitInt8 *)value,len);
}

caStatus writeI16Array(void* pcas,const char* pvname,aitInt16 *value,int len)
{
	lvPV* pPV = (lvCAS*)pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddAtomic(gddAppType_value,aitEnumInt16,1u,len);
	assert(pdd);
	pdd->putRef(value);
	caStatus s = pPV->setValue(*pdd);
	pdd->unreference();
	return s;
}

caStatus writeU16Array(void* pcas,const char* pvname,aitUint16 *value,const int len)
{
	return writeI16Array(pcas,pvname,(aitInt16 *)value,len);
}

caStatus writeI32Array(void* pcas,const char* pvname,aitInt32 *value,const int len)
{
	lvPV* pPV = (lvCAS*)pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddAtomic(gddAppType_value,aitEnumInt32,1u,len);
	assert(pdd);
	pdd->putRef(value);
	caStatus s = pPV->setValue(*pdd);
	pdd->unreference();
	return s;
}


caStatus writeU32Array(void* pcas,const char* pvname,aitUint32 *value,const int len)
{
	return writeI32Array(pcas,pvname,(aitInt32 *)value,len);
}

caStatus writeFloat32Array(void* pcas,const char* pvname,aitFloat32 *value,const int len)
{
	lvPV* pPV = (lvCAS*)pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddAtomic(gddAppType_value,aitEnumFloat32,1u,len);
	assert(pdd);
	pdd->putRef(value);
	caStatus s = pPV->setValue(*pdd);
	pdd->unreference();
	return s;
}

caStatus writeFloat64Array(void* pcas,const char* pvname,aitFloat64 *value,const int len)
{
	lvPV* pPV = (lvCAS*)pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddAtomic(gddAppType_value,aitEnumFloat64,1u,len);
	assert(pdd);
	pdd->putRef(value);
	caStatus s = pPV->setValue(*pdd);
	pdd->unreference();
	return s;
}

#ifdef __cplusplus
}
#endif
