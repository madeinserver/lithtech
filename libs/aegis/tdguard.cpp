/*
	Apperently this was used for protection of some sort, now unrequired mostly. it's left here just for compatibility with LT tools
	Trough reversing the tdguard.lib via IDA it's pretty much a stub.
	
	Author: Arves100
	Date: 15/02/2023
*/

#include <stdlib.h>
#define private public // @note: this is an horrible crap to allow the creation of the Aegis singleton
#include <tdguard.h>

namespace TdGuard
{
	static TdGuard::Aegis __S1__1__GetSingleton_Aegis_TdGuard__SAAAV23_XZ_4IA;

	Aegis::Aegis() {}
	Aegis::~Aegis() {}

	bool Aegis::Init() { return 1; }

	Aegis& Aegis::GetSingleton() {
		return __S1__1__GetSingleton_Aegis_TdGuard__SAAAV23_XZ_4IA;
	}

	bool Aegis::DoWork() { return 1; }

} // namespace TdGuard
