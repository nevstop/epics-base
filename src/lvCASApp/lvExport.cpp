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

epicsShareFunc int createCAS(const char* pname,const char* dbdFile,lvCAS** pcas)
{
	*pcas = new lvCAS(pname,dbdFile);
	assert(*pcas);
	return 0;
}

epicsShareFunc int loadDbFile(lvCAS* pcas,const char* file)
{
	return pcas->loadDbFile(file);
}

epicsShareFunc void installCallback(lvCAS* pcas,caCallback callback)
{
	pcas->installCallback(callback);
}

epicsShareFunc int startCAS(lvCAS* pcas)
{
	pcas->startCAS();
	return 0;
}
epicsShareFunc int stopCAS(lvCAS* pcas)
{
	pcas->stopCAS();
	return 0;
}

epicsShareFunc int closeCAS(lvCAS* pcas)
{
	delete pcas;
	return 0;
}

epicsShareFunc caStatus readI8(lvCAS* pcas,const char* pvname,aitInt8 *value)
{
	lvPV* pPV = pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddScalar(gddAppType_value,aitEnumInt8);
	assert(pdd);
	caStatus s = pPV->getValue(*pdd);
	pdd->getConvert(*value);
	pdd->unreference();
	return s;
}

epicsShareFunc caStatus readU8(lvCAS* pcas,const char* pvname,aitUint8 *value)
{
	return readI8(pcas,pvname,(aitInt8*)value);
}

epicsShareFunc caStatus readI16(lvCAS* pcas,const char* pvname,aitInt16 *value)
{
	lvPV* pPV = pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddScalar(gddAppType_value,aitEnumInt16);
	assert(pdd);
	caStatus s = pPV->getValue(*pdd);
	pdd->getConvert(*value);
	pdd->unreference();
	return s;
}

epicsShareFunc caStatus readU16(lvCAS* pcas,const char* pvname,aitUint16 *value)
{
	return readI16(pcas,pvname,(aitInt16*)value);
}

epicsShareFunc caStatus readI32(lvCAS* pcas,const char* pvname,aitInt32 *value)
{
	lvPV* pPV = pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddScalar(gddAppType_value,aitEnumInt32);
	assert(pdd);
	caStatus s = pPV->getValue(*pdd);
	pdd->getConvert(*value);
	pdd->unreference();
	return s;
}

epicsShareFunc caStatus readU32(lvCAS* pcas,const char* pvname,aitUint32 *value)
{
	return readI32(pcas,pvname,(aitInt32*)value);
}

epicsShareFunc caStatus readFloat32(lvCAS* pcas,const char* pvname,aitFloat32 *value)
{
	lvPV* pPV = pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddScalar(gddAppType_value,aitEnumFloat32);
	assert(pdd);
	caStatus s = pPV->getValue(*pdd);
	pdd->getConvert(*value);
	pdd->unreference();
	return s;
}

epicsShareFunc caStatus readFloat64(lvCAS* pcas,const char* pvname,aitFloat64 *value)
{
	lvPV* pPV = pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddScalar(gddAppType_value,aitEnumFloat64);
	assert(pdd);
	caStatus s = pPV->getValue(*pdd);
	pdd->getConvert(*value);
	pdd->unreference();
	return s;
}

epicsShareFunc caStatus readString(lvCAS* pcas,const char* pvname,char *buffer,const int len)
{
	lvPV* pPV = pcas->findPV(pvname);
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

epicsShareFunc caStatus writeI8(lvCAS* pcas,const char* pvname, aitInt8 value)
{
	lvPV* pPV = pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddScalar(gddAppType_value,aitEnumInt8);
	assert(pdd);
	pdd->put(value);
	caStatus s = pPV->setValue(*pdd);
	pdd->unreference();
	return s;
}

epicsShareFunc caStatus writeU8(lvCAS* pcas,const char* pvname, aitUint8 value)
{
	return writeI8(pcas,pvname,value);
}

epicsShareFunc caStatus writeI16(lvCAS* pcas,const char* pvname,aitInt16 value)
{
	lvPV* pPV = pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddScalar(gddAppType_value,aitEnumInt16);
	assert(pdd);
	pdd->put(value);
	caStatus s = pPV->setValue(*pdd);
	pdd->unreference();
	return s;
}

epicsShareFunc caStatus writeU16(lvCAS* pcas,const char* pvname,aitUint16 value)
{
	return writeI16(pcas,pvname,value);
}

epicsShareFunc caStatus writeI32(lvCAS* pcas,const char* pvname,aitInt32 value)
{
	lvPV* pPV = pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddScalar(gddAppType_value,aitEnumInt32);
	assert(pdd);
	pdd->put(value);
	caStatus s = pPV->setValue(*pdd);
	pdd->unreference();
	return s;
}

epicsShareFunc caStatus writeU32(lvCAS* pcas,const char* pvname,aitUint32 value)
{
	return writeI32(pcas,pvname,value);
}

epicsShareFunc caStatus writeFloat32(lvCAS* pcas,const char* pvname,aitFloat32 value)
{
	lvPV* pPV = pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddScalar(gddAppType_value,aitEnumFloat32);
	assert(pdd);
	pdd->put(value);
	caStatus s = pPV->setValue(*pdd);
	pdd->unreference();
	return s;
}
epicsShareFunc caStatus writeFloat64(lvCAS* pcas,const char* pvname,aitFloat64 value)
{
	lvPV* pPV = pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddScalar(gddAppType_value,aitEnumFloat64);
	assert(pdd);
	pdd->put(value);
	caStatus s = pPV->setValue(*pdd);
	pdd->unreference();
	return s;
}

epicsShareFunc caStatus writeString(lvCAS* pcas,const char* pvname,const char *stringIn)
{
	lvPV* pPV = pcas->findPV(pvname);
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


epicsShareFunc caStatus readI8Array(lvCAS* pcas,const char* pvname,aitInt8 *value,const int len)
{
	lvPV* pPV = pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddAtomic(gddAppType_value,aitEnumInt8,1u,len);
	pdd->putRef(value);
	assert(pdd);
	caStatus s = pPV->getValue(*pdd);
	pdd->unreference();
	return s;
}

epicsShareFunc caStatus readU8Array(lvCAS* pcas,const char* pvname,aitUint8 *value,const int len)
{
	return readI8Array(pcas,pvname,(aitInt8 *)value,len);
}

epicsShareFunc caStatus readI16Array(lvCAS* pcas,const char* pvname,aitInt16 *value,int len)
{
	lvPV* pPV = pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddAtomic(gddAppType_value,aitEnumInt16,1u,len);
	assert(pdd);
	pdd->putRef(value);
	caStatus s = pPV->getValue(*pdd);
	pdd->unreference();
	return s;
}

epicsShareFunc caStatus readU16Array(lvCAS* pcas,const char* pvname,aitUint16 *value,const int len)
{
	return readI16Array(pcas,pvname,(aitInt16 *)value,len);
}

epicsShareFunc caStatus readI32Array(lvCAS* pcas,const char* pvname,aitInt32 *value,const int len)
{
	lvPV* pPV = pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddAtomic(gddAppType_value,aitEnumInt32,1u,len);
	assert(pdd);
	pdd->putRef(value);
	caStatus s = pPV->getValue(*pdd);
	pdd->unreference();
	return s;
}


epicsShareFunc caStatus readU32Array(lvCAS* pcas,const char* pvname,aitUint32 *value,const int len)
{
	return readI32Array(pcas,pvname,(aitInt32 *)value,len);
}

epicsShareFunc caStatus readFloat32Array(lvCAS* pcas,const char* pvname,aitFloat32 *value,const int len)
{
	lvPV* pPV = pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddAtomic(gddAppType_value,aitEnumFloat32,1u,len);
	assert(pdd);
	pdd->putRef(value);
	caStatus s = pPV->getValue(*pdd);
	pdd->unreference();
	return s;
}

epicsShareFunc caStatus readFloat64Array(lvCAS* pcas,const char* pvname,aitFloat64 *value,const int len)
{
	lvPV* pPV = pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddAtomic(gddAppType_value,aitEnumFloat64,1u,len);
	assert(pdd);
	pdd->putRef(value);
	caStatus s = pPV->getValue(*pdd);
	pdd->unreference();
	return s;
}


epicsShareFunc caStatus writeI8Array(lvCAS* pcas,const char* pvname,aitInt8 *value,int len)
{
	lvPV* pPV = pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddAtomic(gddAppType_value,aitEnumInt8,1u,len);
	assert(pdd);
	pdd->putRef(value);
	caStatus s = pPV->setValue(*pdd);
	pdd->unreference();
	return s;
}

epicsShareFunc caStatus writeU8Array(lvCAS* pcas,const char* pvname,aitUint8 *value,const int len)
{
	return writeI8Array(pcas,pvname,(aitInt8 *)value,len);
}

epicsShareFunc caStatus writeI16Array(lvCAS* pcas,const char* pvname,aitInt16 *value,int len)
{
	lvPV* pPV = pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddAtomic(gddAppType_value,aitEnumInt16,1u,len);
	assert(pdd);
	pdd->putRef(value);
	caStatus s = pPV->setValue(*pdd);
	pdd->unreference();
	return s;
}

epicsShareFunc caStatus writeU16Array(lvCAS* pcas,const char* pvname,aitUint16 *value,const int len)
{
	return writeI16Array(pcas,pvname,(aitInt16 *)value,len);
}

epicsShareFunc caStatus writeI32Array(lvCAS* pcas,const char* pvname,aitInt32 *value,const int len)
{
	lvPV* pPV = pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddAtomic(gddAppType_value,aitEnumInt32,1u,len);
	assert(pdd);
	pdd->putRef(value);
	caStatus s = pPV->setValue(*pdd);
	pdd->unreference();
	return s;
}


epicsShareFunc caStatus writeU32Array(lvCAS* pcas,const char* pvname,aitUint32 *value,const int len)
{
	return writeI32Array(pcas,pvname,(aitInt32 *)value,len);
}

epicsShareFunc caStatus writeFloat32Array(lvCAS* pcas,const char* pvname,aitFloat32 *value,const int len)
{
	lvPV* pPV = pcas->findPV(pvname);
	if(!pPV)
		return S_casApp_pvNotFound;
	gdd* pdd = new gddAtomic(gddAppType_value,aitEnumFloat32,1u,len);
	assert(pdd);
	pdd->putRef(value);
	caStatus s = pPV->setValue(*pdd);
	pdd->unreference();
	return s;
}

epicsShareFunc caStatus writeFloat64Array(lvCAS* pcas,const char* pvname,aitFloat64 *value,const int len)
{
	lvPV* pPV = pcas->findPV(pvname);
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
