#include "device.h"

#include <queue>

std::string g_g1b_account;
std::string g_g1b_password;
std::queue<SerialCode> q_login_ret;

DeviceG1B::DeviceG1B(const wchar_t* port_name,
					 DWORD baud_rate,
					 BYTE byte_size,
					 BYTE stop_bits,
					 BYTE parity) :
	SerialPort(port_name, baud_rate, byte_size, stop_bits, parity),
	frequency(0),
	pulse_width(0.0f),
	voltage(0),
	offset(0)
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

	serial_params.fRtsControl = RTS_CONTROL_HANDSHAKE;
	serial_params.fOutxCtsFlow = true;
	serial_params.fDtrControl = DTR_CONTROL_DISABLE;
	serial_params.fOutxDsrFlow = false;

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
		g_out << buf << '\n';
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
		g_out << buf << '\n';
		return SERIAL_OK;
	}
}

SerialCode DeviceG1B::Read(char* buf, const int size)
{
	DWORD dw_bytes_read = 0;

	if (!ReadFile(serial_handle, buf, size, &dw_bytes_read, NULL)) {
		return SERIAL_FAIL_TO_READ;
	} else {
		g_out << "Read " << dw_bytes_read << " bytes\n";
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
		//g_out << "Write : " << buf;
		return SERIAL_OK;
	}
}

SerialCode DeviceG1B::Login()
{
	q_login_ret = {};
	SerialCode ret = SERIAL_FAIL;
	g_out << g_g1b_account << '\n';
	g_out << g_g1b_password << '\n';

	ret = LoginStepFunction("login step 1", std::string(),
		"avtech-f8369be5fff1", 5, 1000);
	if (ret == SERIAL_OK) {
		ret = LoginStepFunction("login step 2", std::string(g_g1b_account),
			"Password", 10, 1000);
		if (ret == SERIAL_OK) {
			ret = LoginStepFunction("login step 3", std::string(g_g1b_password),
				"> ", 10, 1000);
			if (ret == SERIAL_OK) {
				g_out << "login successful" << '\n';
				q_login_ret.push(ret);
				emit SignalLoginFinished();
				return ret;
			} else {
				g_out << "login step 3 failed" << '\n';
				q_login_ret.push(ret);
				emit SignalLoginFailed();
				return ret;
			}
		} else {
			g_out << "login step 2 failed" << '\n';
			q_login_ret.push(ret);
			emit SignalLoginFailed();
			return ret;
		}
	} else {
		g_out << "login step 1 failed" << '\n';
		q_login_ret.push(ret);
		emit SignalLoginFailed();
		return ret;
	}
}

SerialCode DeviceG1B::LoginStepFunction(std::string name,
										std::string input,
										const char* keyword,
										int max_cnt,
										DWORD time_delay)
{
	input += std::string("\r\n");

	int cnt = 0;
	char buf[MAXBYTE] = "";
	char* cmd = CopyStringToNewedCharArray(input);

	while (strstr(buf, keyword) == NULL && cnt < max_cnt) {
		if (cnt == 0) {
			Write(cmd);
			Sleep(time_delay);
		}

		Read(buf, MAXBYTE);
		Sleep(time_delay);
		cnt += 1;

		g_out << name << " try no." << cnt << " buf " << buf << '\n';

		if (cnt == max_cnt) {
			return SERIAL_FAIL;
		}
	}
	return SERIAL_OK;
}

SerialCode DeviceG1B::SetFreq(int freq)
{
	this->frequency = freq;
	int period = (int)(1.0f / (float)freq * 1000000000.0f);
	//g_out << period << '\n';
	std::string node("source:");
	std::string period_cmd = "pulse:period " + std::to_string(period) + "ns;";
	std::string buf = node + period_cmd + "hold width;double off";
	buf += std::string("\r\n");
	g_out << buf << '\n';

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

SerialCode DeviceG1B::GetFreq(int* freq)
{
	*freq = this->frequency;
	return SERIAL_OK;
}

SerialCode DeviceG1B::SetPulseWidth(float pw)
{
	this->pulse_width = pw;
	int pw_ns = (int)((float)pw * 1000.0f);
	//g_out << pw_ns << '\n';
	std::string node("source:");
	std::string pw_cmd = "pulse:width " + std::to_string(pw_ns) + "ns;";
	std::string buf = node + pw_cmd + "hold width;double off";
	buf += std::string("\r\n");
	g_out << buf << '\n';

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

SerialCode DeviceG1B::GetPulseWidth(float* pw)
{
	*pw = this->pulse_width;
	return SERIAL_OK;
}

SerialCode DeviceG1B::SetVoltage(int v)
{
	this->voltage = v;
	std::string node("source:");
	std::string buf = node + "voltage " + std::to_string(v) + "V";
	buf += std::string("\r\n");
	g_out << buf << '\n';

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

SerialCode DeviceG1B::GetVoltage(int* v)
{
	*v = this->voltage;
	return SERIAL_OK;
}

SerialCode DeviceG1B::SetOffset(int offset)
{
	this->offset = offset;
	std::string node("source:");
	std::string buf = node + "voltage:low " + std::to_string(offset) + "V";
	buf += std::string("\r\n");
	g_out << buf << '\n';

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

SerialCode DeviceG1B::GetOffset(int* offset)
{
	*offset = this->offset;
	return SERIAL_OK;
}

SerialCode DeviceG1B::On()
{
	std::string buf = "output on";
	buf += std::string("\r\n");
	g_out << buf << '\n';

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

SerialCode DeviceG1B::Off()
{
	std::string buf = "output off";
	buf += std::string("\r\n");
	g_out << buf << '\n';

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