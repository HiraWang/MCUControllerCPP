#include <string>  
#include <iomanip>
#include <iostream> 
#include <sstream>   

#include "device.h"

extern std::string CR;

DeviceRegloIcc::DeviceRegloIcc(const wchar_t* port_name,
						       DWORD baud_rate,
						       BYTE byte_size,
						       BYTE stop_bits,
						       BYTE parity) :
	SerialPort(port_name, baud_rate, byte_size, stop_bits, parity)
{

}

DeviceRegloIcc::~DeviceRegloIcc()
{

}

SerialCode DeviceRegloIcc::Open()
{
	// open serial port
	serial_handle = CreateFile(port_name,
							   GENERIC_READ | GENERIC_WRITE,
							   0,
							   0,
							   OPEN_EXISTING,
							   FILE_ATTRIBUTE_NORMAL,
							   0);

	// check serial port
	if (serial_handle == INVALID_HANDLE_VALUE) {
		if (GetLastError() == ERROR_FILE_NOT_FOUND) {
			g_out << "serial port does not exist" << '\n';
			return SERIAL_NO_PORT;
		}
		g_out << "some other error occurred" << '\n';
		return SERIAL_FAIL;
	}

	// do basic settings
	DCB serial_params = { 0 };
	serial_params.DCBlength = sizeof(serial_params);

	if (!GetCommState(serial_handle, &serial_params)) {
		g_out << "error getting serial port state" << '\n';
		return SERIAL_FAIL_TO_GET_STATE;
	}

	serial_params.BaudRate = baud_rate;
	serial_params.ByteSize = byte_size;
	serial_params.StopBits = stop_bits;
	serial_params.Parity = parity;

	if (!SetCommState(serial_handle, &serial_params)) {
		g_out << "error setting serial port state" << '\n';
		return SERIAL_FAIL_TO_SET_STATE;
	}

	// set timeouts
	COMMTIMEOUTS timeout = { 0 };
	timeout.ReadIntervalTimeout = 50;
	timeout.ReadTotalTimeoutConstant = 50;
	timeout.ReadTotalTimeoutMultiplier = 50;
	timeout.WriteTotalTimeoutConstant = 50;
	timeout.WriteTotalTimeoutMultiplier = 10;

	SetCommTimeouts(serial_handle, &timeout);
	if (!SetCommTimeouts(serial_handle, &timeout)) {
		g_out << "error setting timeout" << '\n';
		return SERIAL_FAIL_TO_SET_TIMEOUT;
	}

	// set address
	SetAddress();
	
	// set rpm mode
	SetRpmMode(1);
	SetRpmMode(2);

	return SERIAL_OK;
}

SerialCode DeviceRegloIcc::Close()
{
	if (!CloseHandle(serial_handle)) {
		return SERIAL_FAIL;
	} else {
		return SERIAL_OK;
	}
}

SerialCode DeviceRegloIcc::Read()
{
	const int size = 5;
	char buf[size + 1] = { 0 };
	DWORD dw_bytes_read = 0;

	if (!ReadFile(serial_handle, buf, size, &dw_bytes_read, NULL)) {
		return SERIAL_FAIL_TO_READ;
	} else {
		g_out << buf << '\n';
		return SERIAL_OK;
	}
}

SerialCode DeviceRegloIcc::Write()
{
	char buf[] = "go\r";
	DWORD size = (DWORD)strlen(buf);
	DWORD dw_bytes_read = 0;

	if (!WriteFile(serial_handle, buf, size, &dw_bytes_read, NULL)) {
		return SERIAL_FAIL_TO_WRITE;
	} else {
		g_out << buf << '\n';
		return SERIAL_OK;
	}
}

SerialCode DeviceRegloIcc::Login()
{
	return SERIAL_OK;
}

SerialCode DeviceRegloIcc::SetRpm(BYTE channel, float rpm)
{
	int tmp = (int)roundf(rpm * 100.0f);
	int rpm_i = (int)(rpm);
	int rpm_f = (int)(tmp % 100);

	std::stringstream rpm_i_stream;
	rpm_i_stream << std::setw(4) << std::setfill('0') << std::to_string(rpm_i);
	//g_out << rpm_i_stream.str() << '\n';

	std::stringstream rpm_f_stream;
	rpm_f_stream << std::setw(2) << std::setfill('0') << std::to_string(rpm_f);
	//g_out << rpm_f_stream.str() << '\n';

	std::string buf = std::to_string(channel) + 'S' + rpm_i_stream.str() + rpm_f_stream.str();
	g_out << buf << '\n';
	buf += CR;

	char* cmd = CopyStringToNewedCharArray(buf);
	DWORD size = (DWORD)strlen(cmd);
	DWORD dw_bytes_read = 0;

	if (!WriteFile(serial_handle, cmd, size, &dw_bytes_read, NULL)) {
		delete[] cmd;
		return SERIAL_FAIL_TO_WRITE;
	} else {
		delete[] cmd;
		return SERIAL_OK;
	}
}

SerialCode DeviceRegloIcc::SetCw(BYTE channel)
{
	std::string buf = std::to_string(channel) + 'J';
	g_out << buf << '\n';
	buf += CR;

	char* cmd = CopyStringToNewedCharArray(buf);
	DWORD size = (DWORD)strlen(cmd);
	DWORD dw_bytes_read = 0;

	if (!WriteFile(serial_handle, cmd, size, &dw_bytes_read, NULL)) {
		delete[] cmd;
		return SERIAL_FAIL_TO_WRITE;
	} else {
		delete[] cmd;
		return SERIAL_OK;
	}
}

SerialCode DeviceRegloIcc::SetCcw(BYTE channel)
{
	std::string buf = std::to_string(channel) + 'K';
	g_out << buf << '\n';
	buf += CR;

	char* cmd = CopyStringToNewedCharArray(buf);
	DWORD size = (DWORD)strlen(cmd);
	DWORD dw_bytes_read = 0;

	if (!WriteFile(serial_handle, cmd, size, &dw_bytes_read, NULL)) {
		delete[] cmd;
		return SERIAL_FAIL_TO_WRITE;
	} else {
		delete[] cmd;
		return SERIAL_OK;
	}
}

SerialCode DeviceRegloIcc::On(BYTE channel)
{
	std::string buf = std::to_string(channel) + 'H';
	g_out << buf << '\n';
	buf += CR;

	char* cmd = CopyStringToNewedCharArray(buf);
	DWORD size = (DWORD)strlen(cmd);
	DWORD dw_bytes_read = 0;

	if (!WriteFile(serial_handle, cmd, size, &dw_bytes_read, NULL)) {
		delete[] cmd;
		return SERIAL_FAIL_TO_WRITE;
	} else {
		delete[] cmd;
		return SERIAL_OK;
	}
}

SerialCode DeviceRegloIcc::Off(BYTE channel)
{
	std::string buf = std::to_string(channel) + 'I';
	g_out << buf << '\n';
	buf += CR;

	char* cmd = CopyStringToNewedCharArray(buf);
	DWORD size = (DWORD)strlen(cmd);
	DWORD dw_bytes_read = 0;

	if (!WriteFile(serial_handle, cmd, size, &dw_bytes_read, NULL)) {
		delete[] cmd;
		return SERIAL_FAIL_TO_WRITE;
	} else {
		delete[] cmd;
		return SERIAL_OK;
	}
}

SerialCode DeviceRegloIcc::SetAddress()
{
	std::string buf_1 = "@2";
	std::string buf_2 = "2~1";
	g_out << buf_1 << '\n';
	g_out << buf_2 << '\n';
	buf_1 += CR;
	buf_2 += CR;

	char* cmd_1 = CopyStringToNewedCharArray(buf_1);
	char* cmd_2 = CopyStringToNewedCharArray(buf_2);
	DWORD size_1 = (DWORD)strlen(cmd_1);
	DWORD size_2 = (DWORD)strlen(cmd_2);
	DWORD dw_bytes_read = 0;

	if (!WriteFile(serial_handle, cmd_1, size_1, &dw_bytes_read, NULL)) {
		delete[] cmd_1;
		delete[] cmd_2;
		return SERIAL_FAIL_TO_WRITE;
	}

	if (!WriteFile(serial_handle, cmd_2, size_2, &dw_bytes_read, NULL)) {
		delete[] cmd_1;
		delete[] cmd_2;
		return SERIAL_FAIL_TO_WRITE;
	}

	delete[] cmd_1;
	delete[] cmd_2;
	return SERIAL_OK;
}

SerialCode DeviceRegloIcc::SetRpmMode(BYTE channel)
{
	std::string buf = std::to_string(channel) + 'L';
	g_out << buf << '\n';
	buf += CR;

	char* cmd = CopyStringToNewedCharArray(buf);
	DWORD size = (DWORD)strlen(cmd);
	DWORD dw_bytes_read = 0;

	if (!WriteFile(serial_handle, cmd, size, &dw_bytes_read, NULL)) {
		delete[] cmd;
		return SERIAL_FAIL_TO_WRITE;
	} else {
		delete[] cmd;
		return SERIAL_OK;
	}
}