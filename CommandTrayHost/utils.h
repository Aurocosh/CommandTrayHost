﻿#pragma once

std::wstring utf8_to_wstring(const std::string&);
std::string wstring_to_utf8(const std::wstring&);

int64_t FileSize(PCWSTR);

bool json_object_has_member(const nlohmann::json&, PCSTR);

/*
* Make sure out is initialized with default value before call try_read_optional_json
*/
template<typename Type>
#ifdef _DEBUG
bool try_read_optional_json(const nlohmann::json& root, Type& out, PCSTR query_string, PCSTR caller_fuc_name)
#else
bool try_read_optional_json(const nlohmann::json& root, Type& out, PCSTR query_string)
#endif
{
	//Type ignore_all = false; // Do it before call try_read_optional_json
	try
	{
		out = root.at(query_string);
	}
#ifdef _DEBUG
	catch (std::out_of_range& e)
#else
	catch (std::out_of_range&)
#endif
	{
		LOGMESSAGE(L"%S %S out_of_range %S\n", caller_fuc_name, query_string, e.what());
		return false;
	}
	catch (...)
	{
		MessageBox(NULL,
			(utf8_to_wstring(query_string) + L" type check failed!").c_str(),
			L"Type Error",
			MB_OK | MB_ICONERROR
		);
		return false;
	}
	return true;
}


#ifdef _DEBUG
void ChangeIcon(const HICON);
#endif