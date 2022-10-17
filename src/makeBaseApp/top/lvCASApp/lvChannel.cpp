/*
 * lvChannel.cpp
 *
 *  Created on: Jul 22, 2013
 *      Author: Kai Yang
 */
#include "lvCASDef.h"
namespace lvCASInterface
{

	bool lvChannel::readAccess() const
	{
		lvPV* pPV = (lvPV*)const_cast<lvChannel* const>(this)->getPV();
		aitBool b;
		switch(pPV->accType)
		{
		case ReadOnly:
		case ReadWrite:
			b = aitTrue;
			break;
		default:
			b = aitFalse;
			break;
		}
		return b;
	}



	bool lvChannel::writeAccess() const
	{
		lvPV* pPV = (lvPV*)const_cast<lvChannel* const>(this)->getPV();
		aitBool b;
		switch(pPV->accType)
		{
		case WriteOnly:
		case ReadWrite:
			b = aitTrue;
			break;
		default:
			b = aitFalse;
			break;
		}
		return b;
	}
}
