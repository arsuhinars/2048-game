#pragma once
#include <map>
#include <string>
#include <random>

namespace arsuhinars
{
	namespace utils
	{
		typedef std::map<std::string, std::string> IniFile;

		// ������� ���������� ������� ������
		unsigned int findPowerOfTwo(unsigned int power);

		// ���������� ��������� ����� � ��������� [0, 1)
		float random();

		// ���������� ��������� ������������ ����� � ��������� [min, max)
		float randomRange(float min, float max);

		// ���������� ��������� ����� ����� � ��������� [min, max)
		int randomRange(int min, int max);

		// ������ ini ���� � ���������� ������� �� ����� ����������
		IniFile readIni(const std::string& path);

		// ��������� ��� �������� �� ������� � ini ����
		void saveIni(const std::string& path, IniFile data);
	}
}
