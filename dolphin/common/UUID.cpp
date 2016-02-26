#include "stdafx.h"
#include "UUID.h"
#include "Utility.h"

namespace dolphin_common
{
	UUIDGen::UUIDGen()
	{
#ifdef _WIN32
		m_str = NULL;
#endif
	}


	UUIDGen::~UUIDGen()
	{
#ifdef _WIN32
		if (m_str)
		{
			RpcStringFree(&m_str);
		}
#endif
	}

	std::string UUIDGen::GetNewUuid()
	{
#ifdef _WIN32
		if (m_str)
		{
			RpcStringFree(&m_str);
		}
		UuidCreate(&m_uuid);
		UuidToString(&m_uuid, &m_str);
		return Utility::WStringToString((TCHAR*)m_str);
#else
		uuid_generate(m_uuid);
		uuid_unparse(m_uuid, m_str);
		return (const char *)m_str;
#endif
	}

	bool UUIDGen::IsValidUuid(const std::string& str)
	{
		bool retval = false;
		if (str.length() == 36)
		{
#ifdef _WIN32
			UUID uuid;
			return UuidFromString((RPC_WSTR)str.c_str(), &uuid) == RPC_S_OK;
#else
			uuid_t uuid;
			return uuid_parse(_un_const(str), uuid) == 0;
#endif
		}
		return retval;
	}
}