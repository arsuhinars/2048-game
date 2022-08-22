#define _USE_MATH_DEFINES
#include <math.h>
#include "rounded_rect.h"

using namespace std;
using namespace sf;

arsuhinars::RoundedRectShape::RoundedRectShape(const Vector2f& size, float radius, size_t radiusPointsCount) : sf::Shape()
{
    RoundedRectShape::size = size;
    RoundedRectShape::radius = radius;
    RoundedRectShape::radiusPointsCount = radiusPointsCount;

    updatePointsArray();
}

void arsuhinars::RoundedRectShape::setSize(const Vector2f& size)
{
    RoundedRectShape::size = size;

    updatePoints();
}

const Vector2f& arsuhinars::RoundedRectShape::getSize()
{
    return size;
}

void arsuhinars::RoundedRectShape::setRadius(float radius)
{
    RoundedRectShape::radius = radius;

    updatePoints();
}

float arsuhinars::RoundedRectShape::getRadius()
{
    return radius;
}

void arsuhinars::RoundedRectShape::setRadiusPointsCount(size_t count)
{
    radiusPointsCount = count;

    updatePointsArray();
}

size_t arsuhinars::RoundedRectShape::getRadiusPointsCount()
{
    return radiusPointsCount;
}

size_t arsuhinars::RoundedRectShape::getPointCount() const
{
    return points.size();
}

sf::Vector2f arsuhinars::RoundedRectShape::getPoint(size_t index) const
{
    return points[index];
}

void arsuhinars::RoundedRectShape::updatePointsArray()
{
    points = vector<Vector2f>();
    points.resize(radiusPointsCount * 4 + 8);

    updatePoints();
}

void arsuhinars::RoundedRectShape::updatePoints()
{
    points[0] = Vector2f(0.0f, radius);
    points[radiusPointsCount + 1] = Vector2f(radius, 0.0f);
    points[radiusPointsCount + 2] = Vector2f(size.x - radius, 0.0f);
    points[radiusPointsCount * 2 + 3] = Vector2f(size.x, radius);
    points[radiusPointsCount * 2 + 4] = Vector2f(size.x, size.y - radius);
    points[radiusPointsCount * 3 + 5] = Vector2f(size.x - radius, size.y);
    points[radiusPointsCount * 3 + 6] = Vector2f(radius, size.y);
    points[radiusPointsCount * 4 + 7] = Vector2f(0.0f, size.y - radius);

    // Координаты центра всех четвертей
    auto c1 = Vector2f(radius, radius);
    auto c2 = Vector2f(size.x - radius, radius);
    auto c3 = Vector2f(size.x - radius, size.y - radius);
    auto c4 = Vector2f(radius, size.y - radius);

    float angle = 0.0f;
    float delta = static_cast<float>(M_PI) / 2.0f / (radiusPointsCount + 1);

    // Создаем четверти окружностей
    for (size_t i = 0; i < radiusPointsCount; i++) {
        angle += delta;

        // Смещение данной точки
        auto o1 = Vector2f(cos(angle), sin(angle));
        auto o2 = Vector2f(
            cos(static_cast<float>(M_PI) / 2.0f - angle),
            sin(static_cast<float>(M_PI) / 2.0f - angle)
        );

        points[i + 1] = c1 + Vector2f(-o1.x, -o1.y) * radius;
        points[radiusPointsCount + 3 + i] = c2 + Vector2f(o2.x, -o2.y) * radius;
        points[radiusPointsCount * 2 + 5 + i] = c3 + Vector2f(o1.x, o1.y) * radius;
        points[radiusPointsCount * 3 + 7 + i] = c4 + Vector2f(-o2.x, o2.y) * radius;
    }

     Shape::update();
}
