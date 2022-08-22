#include <regex>
#include <vector>
#include <random>
#include <fstream>
#include "utils.h"

using namespace std;
using namespace sf;

unsigned int arsuhinars::utils::findPowerOfTwo(unsigned int power)
{
    static vector<unsigned int> cache = { 1 };

    for (auto i = cache.size(); i <= power; i++) {
        cache.push_back(cache[i - 1] * 2);
    }
    
    return cache[power];
}

float arsuhinars::utils::lerp(float a, float b, float t)
{
    return a + (b - a) * t;
}

sf::Vector2f arsuhinars::utils::lerpVector(const sf::Vector2f& a, const sf::Vector2f& b, float t)
{
    return sf::Vector2f(
        lerp(a.x, b.x, t),
        lerp(a.y, b.y, t)
    );
}

sf::Color arsuhinars::utils::lerpColor(const sf::Color& a, const sf::Color& b, float t)
{
    return Color(
        static_cast<unsigned int>(lerp(a.r, b.r, t)),
        static_cast<unsigned int>(lerp(a.g, b.g, t)),
        static_cast<unsigned int>(lerp(a.b, b.b, t)),
        static_cast<unsigned int>(lerp(a.a, b.a, t))
    );
}

float arsuhinars::utils::random()
{
    static default_random_engine gen{ random_device{}() };
    static uniform_real_distribution<float> dist(0.0f, 1.0f);

    return dist(gen);
}

float arsuhinars::utils::randomRange(float min, float max)
{
    return random() * (max - min) + min;
}

int arsuhinars::utils::randomRange(int min, int max)
{
    return static_cast<int>(randomRange(
        static_cast<float>(min),
        static_cast<float>(max)
    ));
}

arsuhinars::utils::IniFile arsuhinars::utils::readIni(const std::string& path)
{
    static regex r(R"(\s*(\S+)\s*=\s*([^\s;]*[^;]*[^\s;]+).*)");

    IniFile output;

    ifstream f(path);
    if (!f.is_open()) {
        return output;
    }

    string line;
    while (getline(f, line)) {
        smatch results;

        if (regex_match(line, results, r)) {
            output[results[1].str()] = results[2].str();
        }
    }

    return output;
}

void arsuhinars::utils::saveIni(const std::string& path, IniFile data)
{
    ofstream f(path);

    for (auto& pair : data) {
        f << pair.first << "=" << pair.second << endl;
    }
    
    f.close();
}
