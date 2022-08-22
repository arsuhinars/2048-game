#pragma once
#include <map>
#include <string>
#include <random>
#include <SFML/Graphics.hpp>

namespace arsuhinars
{
	namespace utils
	{
		typedef std::map<std::string, std::string> IniFile;

		// Функция нахождения степени двойки
		unsigned int findPowerOfTwo(unsigned int power);

		// Функция интерполяции двух чисел
		float lerp(float a, float b, float t);

		// Функция интерполяции векторов
		sf::Vector2f lerpVector(const sf::Vector2f& a, const sf::Vector2f& b, float t);

		// Функция интерполяции цвета
		sf::Color lerpColor(const sf::Color& a, const sf::Color& b, float t);

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
