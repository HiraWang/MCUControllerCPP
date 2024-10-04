#include "device.h"

#include <queue>

std::queue<SerialCode> q_login_ret;

DeviceG1B::DeviceG1B(const wchar_t* port_name,
					 DWORD baud_rate,
				     BYTE byte_size,
					 BYTE stop_bits,
					 BYTE parity) :
	SerialPort(port_name, baud_rate, byte_size, stop_bits, parity)
{

}

DeviceG1B::~DeviceG1B()
{

}

SerialCode DeviceG1B::Open()
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
			std::cout << "serial port does not exist" << '\n';
			return SERIAL_NO_PORT;
		}
		std::cout << "some other error occurred" << '\n';
		return SERIAL_FAIL;
	}

	// do basic settings
	DCB serial_params = { 0 };
	serial_params.DCBlength = sizeof(serial_params);

	if (!GetCommState(serial_handle, &serial_params)) {
		std::cout << "error getting serial port state" << '\n';
		return SERIAL_FAIL_TO_GET_STATE;
	}

	serial_params.BaudRate = baud_rate;
	serial_params.ByteSize = byte_size;
	serial_params.StopBits = stop_bits;
	serial_params.Parity = parity;

	if (!SetCommState(serial_handle, &serial_params)) {
		std::cout << "error setting serial port state" << '\n';
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
		std::cout << "error setting timeout" << '\n';
		return SERIAL_FAIL_TO_SET_TIMEOUT;
	}

	return SERIAL_OK;
}

SerialCode DeviceG1B::Close()
{
	if (!CloseHandle(serial_handle)) {
		return SERIAL_FAIL;
	} else {
		return SERIAL_OK;
	}
}

SerialCode DeviceG1B::Read()
{
	const int size = 5;
	char buf[size + 1] = { 0 };
	DWORD dw_bytes_read = 0;

	if (!ReadFile(serial_handle, buf, size, &dw_bytes_read, NULL)) {
		return SERIAL_FAIL_TO_READ;
	} else {
		std::cout << buf << '\n';
		return SERIAL_OK;
	}
}

SerialCode DeviceG1B::Write()
{
	char buf[] = "go\r";
	DWORD size = (DWORD)strlen(buf);
	DWORD dw_bytes_read = 0;

	if (!WriteFile(serial_handle, buf, size, &dw_bytes_read, NULL)) {
		return SERIAL_FAIL_TO_WRITE;
	} else {
		std::cout << buf << '\n';
		return SERIAL_OK;
	}
}

SerialCode DeviceG1B::Read(char* buf, const int size)
{
	DWORD dw_bytes_read = 0;

	if (!ReadFile(serial_handle, buf, size, &dw_bytes_read, NULL)) {
		return SERIAL_FAIL_TO_READ;
	} else {
		std::cout << "Read : " << buf;
		return SERIAL_OK;
	}
}

SerialCode DeviceG1B::Write(const char* buf)
{
	DWORD size = (DWORD)strlen(buf);
	DWORD dw_bytes_read = 0;

	if (!WriteFile(serial_handle, buf, size, &dw_bytes_read, NULL)) {
		return SERIAL_FAIL_TO_WRITE;
	} else {
		std::cout << "Write : " << buf;
		return SERIAL_OK;
	}
}

SerialCode DeviceG1B::Login()
{
	SerialCode ret = SERIAL_FAIL;
	ret = LoginStepFunction("login step 1", std::string("\r\n"),
		"avtech-f8369be5fff1", 5, 200);
	if (ret == SERIAL_OK) {
		ret = LoginStepFunction("login step 2", std::string("adminz\r\n"),
			"Password", 5, 200);
		if (ret == SERIAL_OK) {
			ret = LoginStepFunction("login step 3", std::string("defaultz\r\n"),
				"> ", 5, 200);
			if (ret == SERIAL_OK) {
				std::cout << "login successful" << '\n';
				q_login_ret.push(ret);
				emit SignalLoginFinished();
				return ret;
			} else {
				std::cout << "login step 3 failed" << '\n';
				q_login_ret.push(ret);
				return ret;
			}
		} else {
			std::cout << "login step 2 failed" << '\n';
			q_login_ret.push(ret);
			return ret;
		}
	} else {
		std::cout << "login step 1 failed" << '\n';
		q_login_ret.push(ret);
		return ret;
	}
}

SerialCode DeviceG1B::LoginStepFunction(std::string name,
										std::string input,
										const char* keyword,
										int max_cnt,
										DWORD time_delay)
{
	int cnt = 0;
	char buf[MAXBYTE] = "";
	char* cmd = CopyStringToNewedCharArray(input);

	while (strstr(buf, keyword) == NULL && cnt < max_cnt) {
		std::cout << name << " try no." << cnt << '\n';

		if (cnt == 0) {
			Write(cmd);
			Sleep(time_delay);
		}

		Read(buf, MAXBYTE);
		Sleep(time_delay);
		cnt += 1;

		if (cnt == max_cnt) {
			return SERIAL_FAIL;
		}
	}
	return SERIAL_OK;
}