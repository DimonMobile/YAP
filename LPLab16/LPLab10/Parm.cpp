#include "Parm.h"
#include "Error.h"

Parm::PARM Parm::getparm(int argc, _TCHAR **argv)
{
	PARM res;
	size_t parmInLen = wcslen(PARM_IN);
	size_t parmOutLen = wcslen(PARM_OUT);
	size_t parmLogLen = wcslen(PARM_LOG);
	for (int i = 1; i < argc; ++i)
	{
		size_t parmSize = wcslen(argv[i]);
		if (parmSize > PARM_MAX_SIZE)
			throw ERROR_THROW(104)
		if (!wcsncmp(argv[i], PARM_IN, parmInLen))
			wcscpy_s(res.in, argv[i]+parmInLen);
		else if (!wcsncmp(argv[i], PARM_OUT, parmOutLen))
			wcscpy_s(res.out, argv[i]+parmOutLen);
		else if (!wcsncmp(argv[i], PARM_LOG, parmLogLen))
			wcscpy_s(res.log, argv[i]+parmLogLen);
	}
	if (!wcslen(res.in))
		throw ERROR_THROW(100);
	if (!wcslen(res.out))
	{
		wcscpy_s(res.out, argv[0]);
		wcscat_s(res.out, PARM_OUT_DEFAULT_EXT);
	}
	if (!wcslen(res.log))
	{
		wcscpy_s(res.log, argv[0]);
		wcscat_s(res.log, PARM_LOG_DEFAULT_EXT);
	}
	return res;
}

Parm::PARM::PARM()
{
	*in = L'\0';
	*out = L'\0';
	*log = L'\0';
}
