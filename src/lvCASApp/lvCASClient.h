/*
 * casHandleClient.h
 *
 *  Created on: Jul 4, 2018
 *      Author: Kai Yang
 */

#ifndef CASCLIENT_H_
#define CASCLIENT_H_

#ifdef __cplusplus
extern "C" {
#endif
typedef unsigned int* casHandle;
typedef signed char         aitInt8;
typedef unsigned char       aitUint8;
typedef short               aitInt16;
typedef unsigned short      aitUint16;
typedef int                 aitInt32;
typedef unsigned int        aitUint32;
typedef float               aitFloat32;
typedef double              aitFloat64;
typedef aitUint32 caStatus;
typedef void(*caCallback)(const char* pvname,const void *value,int len);

int createCAS(const char* pname,const char* dbdFile,casHandle* pcas);
int loadDbFile(casHandle pcas,const char* file);
int startCAS(casHandle pcas);
int stopCAS(casHandle pcas);
int closeCAS(casHandle pcas);
void installCallback(casHandle pcas,caCallback callback);

caStatus readI8(casHandle pcas,const char* pvname,aitInt8 *value);
caStatus readU8(casHandle pcas,const char* pvname,aitUint8 *value);
caStatus readI16(casHandle pcas,const char* pvname,aitInt16 *value);
caStatus readU16(casHandle pcas,const char* pvname,aitUint16 *value);
caStatus readI32(casHandle pcas,const char* pvname,aitInt32 *value);
caStatus readU32(casHandle pcas,const char* pvname,aitUint32 *value);
caStatus readFloat32(casHandle pcas,const char* pvname,aitFloat32 *value);
caStatus readFloat64(casHandle pcas,const char* pvname,aitFloat64 *value);
caStatus readString(casHandle pcas,const char* pvname,char *buffer,const int len);
caStatus writeI8(casHandle pcas,const char* pvname, aitInt8 value);
caStatus writeU8(casHandle pcas,const char* pvname, aitUint8 value);
caStatus writeI16(casHandle pcas,const char* pvname,aitInt16 value);
caStatus writeU16(casHandle pcas,const char* pvname,aitUint16 value);
caStatus writeI32(casHandle pcas,const char* pvname,aitInt32 value);
caStatus writeU32(casHandle pcas,const char* pvname,aitUint32 value);
caStatus writeFloat32(casHandle pcas,const char* pvname,aitFloat32 value);
caStatus writeFloat64(casHandle pcas,const char* pvname,aitFloat64 value);
caStatus writeString(casHandle pcas,const char* pvname,const char *stringIn);
caStatus readI8Array(casHandle pcas,const char* pvname,aitInt8 *value,const int len);
caStatus readU8Array(casHandle pcas,const char* pvname,aitUint8 *value,const int len);
caStatus readI16Array(casHandle pcas,const char* pvname,aitInt16 *value,int len);
caStatus readU16Array(casHandle pcas,const char* pvname,aitUint16 *value,const int len);
caStatus readI32Array(casHandle pcas,const char* pvname,aitInt32 *value,const int len);
caStatus readU32Array(casHandle pcas,const char* pvname,aitUint32 *value,const int len);
caStatus readFloat32Array(casHandle pcas,const char* pvname,aitFloat32 *value,const int len);
caStatus readFloat64Array(casHandle pcas,const char* pvname,aitFloat64 *value,const int len);
caStatus writeI8Array(casHandle pcas,const char* pvname,aitInt8 *value,int len);
caStatus writeU8Array(casHandle pcas,const char* pvname,aitUint8 *value,const int len);
caStatus writeI16Array(casHandle pcas,const char* pvname,aitInt16 *value,int len);
caStatus writeU16Array(casHandle pcas,const char* pvname,aitUint16 *value,const int len);
caStatus writeI32Array(casHandle pcas,const char* pvname,aitInt32 *value,const int len);
caStatus writeU32Array(casHandle pcas,const char* pvname,aitUint32 *value,const int len);
caStatus writeFloat32Array(casHandle pcas,const char* pvname,aitFloat32 *value,const int len);
caStatus writeFloat64Array(casHandle pcas,const char* pvname,aitFloat64 *value,const int len);
#ifdef __cplusplus
}
#endif



#endif /* CASCLIENT_H_ */
