#pragma once
#include <string>
#ifdef _WIN32
#include <Rpc.h>
#else
#define UUID_UNPARSED_SIZE 37
typedef unsigned char uuid_t[16];
extern "C" {
	void uuid_generate(uuid_t out);
	void uuid_unparse(const uuid_t uu, char *out);
	int uuid_parse(char *in, uuid_t uu);
}
#endif

namespace dolphin_common
{
	class UUIDGen
	{
	public:
		UUIDGen();
		~UUIDGen();
		std::string GetNewUuid();
		static bool IsValidUuid(const std::string& string);

	protected:
#ifdef _WIN32
		UUID m_uuid;
#ifdef UNICODE
		RPC_WSTR m_str;
#else
		RPC_CSTR m_str;
#endif
#else
		uuid_t m_uuid;
		char m_str[UUID_UNPARSED_SIZE];
#endif
	};
}
