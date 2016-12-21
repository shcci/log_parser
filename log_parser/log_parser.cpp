// log_parser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "utmp.h"

void log_parsing(_In_ std::wstring utmp_file_name,_Inout_ std::list<utmp> *utmp_info_list)
{
	FILE			*utmp_file_ptr;
	struct utmp		utmp_buf;

	/* Open the file if it exists */
	errno = 0;
	_wfopen_s(&utmp_file_ptr, utmp_file_name.c_str(), L"rb");
	if (utmp_file_ptr == NULL)
	{
		_wperror(utmp_file_name.c_str());
		return;
	}

	while (fread(&utmp_buf, sizeof(utmp_buf), 1, utmp_file_ptr))
		utmp_info_list->push_back(utmp_buf);
	
	fclose(utmp_file_ptr);
}

void time_info(_Inout_ char str[], _In_ std::list<utmp>::iterator it)
{
	time_t t = (time_t)it->ut_tv.tv_sec;
	struct tm timeinfo = { 0 };
	localtime_s(&timeinfo, &t);
	asctime_s(str, sizeof(struct tm), &timeinfo);
}

void type_info(_In_ short type)
{
	switch (type)
	{
	case 1:
		printf("RUN_LVL");
		break;
	case 2:
		printf("BOOT_TIME");
		break;
	case 3:
		printf("NEW_TIME");
		break;
	case 4:
		printf("OLD_TIME");
		break;
	case 5:
		printf("INIT_PROCESS");
		break;
	case 6:
		printf("LOGIN_PROCESS");
		break;
	case 7:
		printf("USER_PROCESS");
		break;
	case 8:
		printf("DEAD_PROCESS");
		break;
	case 9:
		printf("ACCOUNTING");
		break;
	}
}

bool log_print(_In_ std::wstring file_name)
{
	std::list<utmp> utmp_data_list;
	log_parsing(file_name, &utmp_data_list);
	std::list<utmp>::iterator it = utmp_data_list.begin();
	char time[40] = { 0 };

	while (utmp_data_list.end() != it)
	{
		time_info(time, it);

		if (it->ut_type == RUN_LVL)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			printf("%s\t %s\t %s",
				it->ut_user,
				it->ut_host,
				time);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		else if (it->ut_type == BOOT_TIME)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			printf("%s\t\t %s\t %s",
				it->ut_user,
				it->ut_host,
				time);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		else if (it->ut_type == INIT_PROCESS)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			type_info(it->ut_type);
			printf("\t %s\t %s\t %s",
				it->ut_line,
				it->ut_id,
				time);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		else if (it->ut_type == LOGIN_PROCESS)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			type_info(it->ut_type);
			printf("\t %d\t %s\t %s\t %s\t",
				it->ut_pid,
				it->ut_line,
				it->ut_user,
				it->ut_host);
			printf("%s", time);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		else if (it->ut_type == USER_PROCESS)
		{
			type_info(it->ut_type);
			printf("\t %d\t %s\t %s\t %s\n",
				it->ut_pid,
				it->ut_line,
				it->ut_user,
				it->ut_host);
		}
		else if (it->ut_type == DEAD_PROCESS)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			type_info(it->ut_type);
			printf("\t %s\t %s\t %s",
				it->ut_line,
				it->ut_id,
				time);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		it++;
		memset(time, NULL, 40);
	}

	utmp_data_list.clear();
	return true;
}

int wmain(int argc, wchar_t *argv[])
{
	//if (argc == 2)
	//	log_print(argv[1]);
	//else
	//	printf("log_parser.exe [file_name]\n");
	log_print(L"wtmp");
	return 0;
}