/*
 * lvTest.cpp
 *
 *  Created on: Jul 19, 2013
 *      Author: Kai Yang
 */
#include "lvCASDef.h"
#include <stdio.h>
#include <iostream>
#include "fdManager.h"
using namespace lvCASInterface;
using std::cin;

extern "C"{
caStatus readString(lvCAS* pcas,const char* pvname,char *buffer,const int len);
caStatus writeString(lvCAS* pcas,const char* pvname,const char *stringIn);
caStatus readI16Array(lvCAS* pcas,const char* pvname,aitInt16 *value,int len);
caStatus writeI16Array(lvCAS* pcas,const char* pvname,aitInt16 *value,int len);
caStatus writeFloat64Array(lvCAS* pcas,const char* pvname,aitFloat64 *value,const int len);
}

	class myDest : public gddDestructor
	{
	public:
		myDest(void) : gddDestructor() { }
		void run(void*);
	};

	void myDest::run(void* v)
	{
		aitInt16* i16 = (aitInt16*)v;
		delete [] i16;
	}

void CallbackFun(const char* pvname,const void *value,int len)
{
	printf("cac update pv %s,length %d\n",pvname,len);
}

lvPV* testFindPV(lvCAS& cas,const char* pvName)
{
	lvPV* pPV = cas.findPV(pvName);
	if(!pPV)
		printf("cannot find PV\n");
	else{
		printf("find PV name=%s\n",pPV->getName());
	}
	return pPV;
}

int main()
{

	//test lvCAS with background thread off
	initRecord ini =
	{
		10.0,
		0.0,
		8.0,
		2.0,
		0.5,
		0.2,
		0.2,
		7.0,
		3.0,
		"ykVolts",
		4,
		MAJOR_ALARM,
		MAJOR_ALARM,
		MINOR_ALARM,
		MINOR_ALARM,
		NO_ALARM,
		MAJOR_ALARM,
		INVALID_ALARM
	};

	lvCAS cas("test","D:/EPICS/ykCAS-lib/src/lvCASApp/template.dbd");
	lvRecord* prec = new lvNumericRecord("testNumeric",cas,aitEnumFloat64,ini);
	cas.installRecord("testNumeric",prec);
	lvPV* pPV = testFindPV(cas,"testNumeric");
	testFindPV(cas,"testNumeric.HIHI");

	prec = new lvLogicRecord("testLogic",cas,aitEnumEnum16,ini);
	cas.installRecord("testLogic",prec);
	lvPV* pL = testFindPV(cas,"testLogic");
	testFindPV(cas,"testLogic.COSV");

	aitUint32 tot_elements = 20;
	prec = new lvVectorRecord("testVector",cas,aitEnumInt16,tot_elements,ini);
	cas.installRecord("testVector",prec);
	lvPV* pV = testFindPV(cas,"testVector");
	testFindPV(cas,"testVector.NELM");
	//test ok

	//test lvPV setValue and getValue
	gdd* pdd = new gddScalar(gddAppType_value,aitEnumFloat64);
	double v = 0.0;
	caStatus s;
	printf("test numeric record\n");
	while(cin >> v)
	{
		if(v > 100.0)
			break;

		pdd->putConvert(v);
		s = pPV->setValue(*pdd);
		assert(!s);
		pdd->putConvert(-1.0);
		s = pPV->getValue(*pdd);
		assert(!s);
		pdd->getConvert(v);
		short stat,sevr;
		pPV->getStatSevr(stat,sevr);
		printf("pdd value = %f,stat = %d,sevr = %d\n",v,stat,sevr);
	}
	char egu[20]={'\0'};
	readString(&cas,"testNumeric.EGU",egu,20);
	printf("read testNumeric.EGU=%s\n",egu);
	writeString(&cas,"testNumeric.EGU","testEGU");
	readString(&cas,"testNumeric.EGU",egu,20);
	printf("read testNumeric.EGU=%s\n",egu);

	printf("test logic record\n");
	pdd->setPrimType(aitEnumEnum16);
	short sv = 0;
	while(cin >> sv)
	{
		if(sv > 100)
			break;

		pdd->putConvert(sv);
		s = pL->setValue(*pdd);
		assert(!s);
		pdd->putConvert(5u);
		s = pL->getValue(*pdd);
		assert(!s);
		pdd->getConvert(sv);
		short stat,sevr;
		pL->getStatSevr(stat,sevr);
		printf("pdd value = %d,stat = %d,sevr = %d\n",sv,stat,sevr);
	}
	pdd->unreference();


//	printf("test waveform record\n");
//	aitInt16* i16 = new aitInt16[tot_elements];
//	for(short i = 0; i < tot_elements; ++i)
//		i16[i] = i;
	//gdd* ddb = new gddAtomic(gddAppType_value,aitEnumInt16,1,&tot_elements);
	//ddb->putRef(i16,new myDest);
	//gdd* ddc = new gddAtomic(gddAppType_value,aitEnumInt16,1,&int(10));
//	aitInt16 buffer[20];
//	for(short i = 0; i < 20; ++i)
//		buffer[i] = 100;
	//ddc->putRef(buffer);
	//ddb->dump();
	//s = pV->setValue(*ddb);
//	s = writeI16Array(&cas,"testVector",i16,20);
//	assert(!s);
	/*i16[0] = 55;
	ddb->dump();
	s = pV->getValue(*ddc);
	ddc->dump();*/
//	printf("test readI16Array\n");
//	readI16Array(&cas,"testVector",buffer,20);
	//ddc->dump();
//	printf("verify buffer\n");
//	for(short i = 0; i < 20; ++i)
//		printf("%d ",buffer[i]);
//	printf("\n");
	//ddb->unreference();
	//ddc->unreference();
	//test ok

	//test db file
	s = cas.loadDbFile("D:/EPICS/ykCAS-lib/src/lvCASApp/dbExample.db");
	assert(!s);
	testFindPV(cas,"yk:ai0");
	testFindPV(cas,"yk:ai0.HIHI");
	double fa[10];
	for(int i = 0; i < 10; ++i)
		fa[i]=i+500;
	writeFloat64Array(&cas,"yk:wv0",fa,10);
	//test ok

	//test CA
	/*while(true)
	{
		::fileDescriptorManager.process(0.02);
	}*/
	//test ok

	//test with background thread on
	cas.installCallback(CallbackFun);
	cas.startCAS();
	while(cin>>sv)
	{
		if(sv == 500)
			break;
	}
	cas.stopCAS();
	//test ok
	return 0;
}
