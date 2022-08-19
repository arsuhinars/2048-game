#pragma once
#include <map>
#include <string>
#include <random>

namespace arsuhinars
{
	namespace utils
	{
		typedef std::map<std::string, std::string> IniFile;

		// Функция нахождения степени двойки
		unsigned int findPowerOfTwo(unsigned int power);

		// Возвращает случайное число в диапозоне [0, 1)
		float random();

		// Возвращает случайное вещественное число в диапозоне [min, max)
		float randomRange(float min, float max);

		// Возвращает случайное целое число в диапозоне [min, max)
		int randomRange(int min, int max);

		// Читает ini файл и возвращает словарь со всеми значениями
		IniFile readIni(const std::string& path);

		// Сохраняет все значения из словаря в ini файл
		void saveIni(const std::string& path, IniFile data);
	}
}
