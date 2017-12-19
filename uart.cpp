#include "uart.h"

void usleep(__int64 usec)
{
	HANDLE timer;
	LARGE_INTEGER ft;

	ft.QuadPart = -(10 * usec); // Convert to 100 nanosecond interval, negative value indicates relative time

	timer = CreateWaitableTimer(NULL, TRUE, NULL);
	SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
	WaitForSingleObject(timer, INFINITE);
	CloseHandle(timer);
}

int Read_Register(_TCHAR *COM_port_name, uint16_t reg_addr, uint8_t width, uint16_t *p_reg_data)
{
	uint8_t		cmd;
	TCommPort	COM_port;
	int			ret;
	int			avail_bytes;
	int			repeat_count;
	BYTE		buf[8];

	if (!COM_port_name) return -1;

	if (width == 16) cmd = DEBUG_DEV_CMD_READ_16;
	else			cmd = DEBUG_DEV_CMD_READ_8;
	buf[0] = START_BYTE;
	buf[1] = cmd;
	buf[2] = (uint8_t)((reg_addr >> 8) & 0xFF);
	buf[3] = (uint8_t)(reg_addr & 0xFF);
	buf[4] = 0;
	buf[5] = 0;
	buf[6] = 0;
	buf[7] = STOP_BYTE;

	ret = COM_port.SetCommPort(std::tstring(COM_port_name));
	if (ret < 0) return -3;
	ret = COM_port.SetBaudRate(CBR_115200);
	if (ret < 0) return -4;
	ret = COM_port.SetParity(NOPARITY);
	if (ret < 0) return -5;
	ret = COM_port.SetByteSize(8);
	if (ret < 0) return -6;
	ret = COM_port.SetStopBits(ONESTOPBIT);
	if (ret < 0) return -7;
	ret = COM_port.OpenCommPort();
	if (ret < 0) return -8;

	ret = COM_port.WriteBuffer(buf, 8);
	if (ret < 0) return -9;
	ZeroMemory(buf, 8);
	repeat_count = TIMEOUT_MS;
	do {
		usleep(1 * 1000); // 1 ms
		avail_bytes = COM_port.BytesAvailable();
		repeat_count--;
	} while ((avail_bytes < 8) && (repeat_count));
	if (avail_bytes >= 8) {
		ret = COM_port.ReadBytes(buf, 8);
		if (ret < 8) return -10;
		COM_port.Flush_RX();
	}

	COM_port.CloseCommPort();

	if (buf[0] != START_BYTE) return -21;
	if (buf[7] != STOP_BYTE) return -21;
	if (buf[1] != cmd) return -22;
	if (buf[2] != (uint8_t)((reg_addr >> 8) & 0xFF)) return -23;
	if (buf[3] != (uint8_t)(reg_addr & 0xFF)) return -23;
	if (p_reg_data) *p_reg_data = (uint16_t)((uint16_t)buf[5] | ((uint16_t)(buf[4]) << 8));
	return 0;
}

int Write_Register(_TCHAR *COM_port_name, uint16_t reg_addr, uint8_t width, uint16_t reg_data)
{
	uint8_t		cmd;
	TCommPort	COM_port;
	int			ret;
	int			avail_bytes;
	int			repeat_count;
	BYTE		buf[8];

	if (!COM_port_name) return -1;

	if (width == 16) cmd = DEBUG_DEV_CMD_WRITE_16;
	else			cmd = DEBUG_DEV_CMD_WRITE_8;
	buf[0] = START_BYTE;
	buf[1] = cmd;
	buf[2] = (uint8_t)((reg_addr >> 8) & 0xFF);
	buf[3] = (uint8_t)(reg_addr & 0xFF);
	buf[4] = (uint8_t)((reg_data >> 8) & 0xFF);
	buf[5] = (uint8_t)(reg_data & 0xFF);
	buf[6] = 0;
	buf[7] = STOP_BYTE;

	ret = COM_port.SetCommPort(std::tstring(COM_port_name));
	if (ret < 0) return -3;
	ret = COM_port.SetBaudRate(CBR_115200);
	if (ret < 0) return -4;
	ret = COM_port.SetParity(NOPARITY);
	if (ret < 0) return -5;
	ret = COM_port.SetByteSize(8);
	if (ret < 0) return -6;
	ret = COM_port.SetStopBits(ONESTOPBIT);
	if (ret < 0) return -7;
	ret = COM_port.OpenCommPort();
	if (ret < 0) return -8;

	ret = COM_port.WriteBuffer(buf, 8);
	if (ret < 0) return -9;
	ZeroMemory(buf, 8);
	repeat_count = TIMEOUT_MS;
	do {
		usleep(1 * 1000); // 1 ms
		avail_bytes = COM_port.BytesAvailable();
		repeat_count--;
	} while ((avail_bytes < 8) && (repeat_count));
	if (avail_bytes >= 8) {
		ret = COM_port.ReadBytes(buf, 8);
		if (ret < 8) return -10;
		COM_port.Flush_RX();
	}

	COM_port.CloseCommPort();

	if (buf[0] != START_BYTE) return -21;
	if (buf[7] != STOP_BYTE) return -21;
	if (buf[1] != cmd) return -22;
	if (buf[2] != (uint8_t)((reg_addr >> 8) & 0xFF)) return -23;
	if (buf[3] != (uint8_t)(reg_addr & 0xFF)) return -23;
	if (buf[4] != (uint8_t)((reg_data >> 8) & 0xFF)) return -24;
	if (buf[5] != (uint8_t)(reg_data & 0xFF)) return -24;
	return 0;
}
/*
void print_usage(LPSTR * argv)
{
	printf("\nRead / write register.\n\n");
	printf("Usage: %s list/l/read/r/write/w COM_port_name width(8/16bit) register_addr [register_data]\n\n", argv[0]);
	printf("List available COM ports : %s list\n", argv[0]);
	printf("Read key settings : %s read  COM_port_name width(8/16bit) register_addr\n", argv[0]);
	printf("Write key settings: %s write COM_port_name width(8/16bit) register_addr register_data\n", argv[0]);
}

LONG __cdecl main(LONG argc, LPSTR * argv)
{
	int						ret = 0;
	int						argc_cnt = 1;
	unsigned long			command = 0;
	unsigned long			param1 = 0;
	unsigned long			param2 = 0;
	unsigned long			param3 = 0;
	_TCHAR					*COM_port_name = NULL;


	if (argc > argc_cnt) { // arg 1
		if ((strcmp(argv[argc_cnt], "read") == 0) || (strcmp(argv[argc_cnt], "r") == 0)) command = 1;
		else if ((strcmp(argv[argc_cnt], "write") == 0) || (strcmp(argv[argc_cnt], "w") == 0)) command = 2;
		else if ((strcmp(argv[argc_cnt], "list") == 0) || (strcmp(argv[argc_cnt], "l") == 0)) command = 3;
	}
	argc_cnt++;
	if (argc > argc_cnt) { // arg 2
#ifdef _UNICODE
		size_t len, lret;
		len = strlen(argv[argc_cnt]) + 1;
		COM_port_name = new _TCHAR[len];
		mbstowcs_s(&lret, COM_port_name, len, argv[argc_cnt], len);
#else
		COM_port_name = argv[argc_cnt];
#endif
	}
	argc_cnt++;
	if (argc > argc_cnt) { // arg 3
		if (argv[argc_cnt][1] == 'x') param1 = strtoul(argv[argc_cnt], NULL, 16);
		else param1 = strtoul(argv[argc_cnt], NULL, 10);
	}
	argc_cnt++;
	if (argc > argc_cnt) { // arg 4
		if (argv[argc_cnt][1] == 'x') param2 = strtoul(argv[argc_cnt], NULL, 16);
		else param2 = strtoul(argv[argc_cnt], NULL, 10);
	}
	argc_cnt++;
	if (argc > argc_cnt) { // arg 5
		if (argv[argc_cnt][1] == 'x') param3 = strtoul(argv[argc_cnt], NULL, 16);
		else param3 = strtoul(argv[argc_cnt], NULL, 10);
	}
	//argc_cnt++;


	if ((command != 1) && (command != 2) && (command != 3)) {
		print_usage(argv);
		exit(0);
	}
	if ((command == 1) && (argc < 5)) {
		print_usage(argv);
		exit(0);
	}
	if ((command == 2) && (argc < 6)) {
		print_usage(argv);
		exit(0);
	}
	if ((command == 3) && (argc < 2)) {
		print_usage(argv);
		exit(0);
	}

	if (command == 1) { // READ
		uint8_t width = (uint8_t)param1;
		uint16_t reg_addr = (uint16_t)param2;
		uint16_t reg_data = 0;
		if (width != 16) width = 8;
		_tprintf(_T("Reading register 0x%X (%d bit) using %s... "), reg_addr, width, COM_port_name);
		ret = Read_Register(COM_port_name, reg_addr, width, &reg_data);
		if (ret) {
			printf("Error %d\n", ret);
		} else {
			printf("OK!\n");
			printf("Register addr: 0x%X\n", reg_addr);
			printf("Width: %d bit\n", width);
			printf("Register data: 0x%X\n", reg_data);
		}
	} else
	if (command == 2) { // WRITE
		uint8_t width = (uint8_t)param1;
		uint16_t reg_addr = (uint16_t)param2;
		uint16_t reg_data = (uint16_t)param3;
		if (width != 16) width = 8;
		printf("Register addr: 0x%X\n", reg_addr);
		printf("Width: %d bit\n", width);
		printf("Register data: 0x%X\n", reg_data);
		_tprintf(_T("Writing register using %s... "), COM_port_name);
		ret = Write_Register(COM_port_name, reg_addr, width, reg_data);
		if (ret) printf("Error %d\n", ret);
		else printf("OK!\n");
	} else
	if (command == 3) { // LIST
		std::list<_TCHAR*> port_list;
		ret = Get_port_list(port_list);
		_tprintf(_T("%d COM port(s) available.\nList:\n"), port_list.size());
		for (std::list<_TCHAR*>::iterator it = port_list.begin(); it != port_list.end(); it++)
			_tprintf(_T("%s\n"), *it);
		Free_port_list(port_list);
	}
	
//exit:
	return ret;
}
*/

