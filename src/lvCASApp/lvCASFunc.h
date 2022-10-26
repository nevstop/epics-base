#ifndef INCLVCACFUNC_h
#define INCLVCACFUNC_h

#include <lvCASDef.h>
#include <casdef.h>

// 说明：1、dll使用C++编写的，所以会看到例如lvCAS这种类的类型，但是声明的时候已经被extern "C"修饰，所以是按照C语言方式编译和连接的，不影响CVI调用；
// 	调用的时候遇到C没有的数据类型需要做特殊处理。
// 	例如：void**可以替换为int*,则lvCAS便为int
// 	  2、return value为0的情况下代表没有出错

epicsShareFunc int createCAS(const char* pname,const char* dbdFile,void** pcas);

epicsShareFunc int loadDbFile(void* pcas,const char* file);

epicsShareFunc int startCAS(void* pcas);

epicsShareFunc int stopCAS(void* pcas);

epicsShareFunc int closeCAS(void* pcas);

epicsShareFunc caStatus readI8(void* pcas,const char* pvname,aitInt8 *value);

epicsShareFunc caStatus readU8(void* pcas,const char* pvname,aitUint8 *value);

epicsShareFunc caStatus readI16(void* pcas,const char* pvname,aitInt16 *value);

epicsShareFunc caStatus readU16(void* pcas,const char* pvname,aitUint16 *value);

epicsShareFunc caStatus readI32(void* pcas,const char* pvname,aitInt32 *value);

epicsShareFunc caStatus readU32(void* pcas,const char* pvname,aitUint32 *value);

epicsShareFunc caStatus readFloat32(void* pcas,const char* pvname,aitFloat32 *value);

epicsShareFunc caStatus readFloat64(void* pcas,const char* pvname,aitFloat64 *value);

epicsShareFunc caStatus readString(void* pcas,const char* pvname,char *buffer,const int len);

epicsShareFunc caStatus writeI8(void* pcas,const char* pvname, aitInt8 value);

epicsShareFunc caStatus writeU8(void* pcas,const char* pvname, aitUint8 value);

epicsShareFunc caStatus writeI16(void* pcas, const char* pvname, aitInt16 value);

epicsShareFunc caStatus writeU16(void* pcas,const char* pvname,aitUint16 value);

epicsShareFunc caStatus writeI32(void* pcas, const char* pvname, aitInt32 value);

epicsShareFunc caStatus writeU32(void* pcas,const char* pvname,aitUint32 value);

epicsShareFunc caStatus writeFloat32(void* pcas,const char* pvname,aitFloat32 value);

epicsShareFunc caStatus writeFloat64(void* pcas,const char* pvname,aitFloat64 value);

epicsShareFunc caStatus writeString(void* pcas,const char* pvname,const char *stringIn);

epicsShareFunc caStatus readI8Array(void* pcas,const char* pvname,aitInt8 *value,const int len);

epicsShareFunc caStatus readU8Array(void* pcas,const char* pvname,aitUint8 *value,const int len);

epicsShareFunc caStatus readI16Array(void* pcas,const char* pvname,aitInt16 *value,int len);

epicsShareFunc caStatus readU16Array(void* pcas,const char* pvname,aitUint16 *value,const int len);

epicsShareFunc caStatus readI32Array(void* pcas,const char* pvname,aitInt32 *value,const int len);

epicsShareFunc caStatus readU32Array(void* pcas,const char* pvname,aitUint32 *value,const int len);

epicsShareFunc caStatus readFloat32Array(void* pcas,const char* pvname,aitFloat32 *value,const int len);

epicsShareFunc caStatus readFloat64Array(void* pcas,const char* pvname,aitFloat64 *value,const int len);

epicsShareFunc caStatus writeI8Array(void* pcas,const char* pvname,aitInt8 *value,int len);

epicsShareFunc caStatus writeU8Array(void* pcas,const char* pvname,aitUint8 *value,const int len);

epicsShareFunc caStatus writeI16Array(void* pcas,const char* pvname,aitInt16 *value,int len);

epicsShareFunc caStatus writeU16Array(void* pcas,const char* pvname,aitUint16 *value,const int len);

epicsShareFunc caStatus writeI32Array(void* pcas,const char* pvname,aitInt32 *value,const int len);

epicsShareFunc caStatus writeU32Array(void* pcas,const char* pvname,aitUint32 *value,const int len);

epicsShareFunc caStatus writeFloat32Array(void* pcas,const char* pvname,aitFloat32 *value,const int len);

epicsShareFunc caStatus writeFloat64Array(void* pcas,const char* pvname,aitFloat64 *value,const int len);


#endif