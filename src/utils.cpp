#include <regex>
#include <vector>
#include <random>
#include <fstream>
#include "utils.h"

using namespace std;

unsigned int arsuhinars::utils::findPowerOfTwo(unsigned int power)
{
    static vector<unsigned int> cache = { 1 };

    for (auto i = cache.size(); i <= power; i++) {
        cache.push_back(cache[i - 1] * 2);
    }
    
    return cache[power];
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
