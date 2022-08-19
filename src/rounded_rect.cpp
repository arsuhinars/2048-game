#define _USE_MATH_DEFINES
#include <math.h>
#include "rounded_rect.h"

using namespace std;
using namespace sf;

sf::ConvexShape arsuhinars::createRoundedRect(sf::Vector2f size, float radius, size_t circlePointsCount)
{
    auto shape = ConvexShape(circlePointsCount * 4 + 8);

    shape.setPoint(0, Vector2f(0.0f, radius));
    shape.setPoint(circlePointsCount + 1, Vector2f(radius, 0.0f));
    shape.setPoint(circlePointsCount + 2, Vector2f(size.x - radius, 0.0f));
    shape.setPoint(circlePointsCount * 2 + 3, Vector2f(size.x, radius));
    shape.setPoint(circlePointsCount * 2 + 4, Vector2f(size.x, size.y - radius));
    shape.setPoint(circlePointsCount * 3 + 5, Vector2f(size.x - radius, size.y));
    shape.setPoint(circlePointsCount * 3 + 6, Vector2f(radius, size.y));
    shape.setPoint(circlePointsCount * 4 + 7, Vector2f(0.0f, size.y - radius));

    // Координаты центра всех четвертей
    auto c1 = Vector2f(radius, radius);
    auto c2 = Vector2f(size.x - radius, radius);
    auto c3 = Vector2f(size.x - radius, size.y - radius);
    auto c4 = Vector2f(radius, size.y - radius);

    float angle = 0.0f;
    float delta = static_cast<float>(M_PI) / 2.0f / (circlePointsCount + 1);

    // Создаем четверти окружностей
    for (size_t i = 0; i < circlePointsCount; i++) {
        angle += delta;

        // Смещение данной точки
        auto o1 = Vector2f(cos(angle), sin(angle));
        auto o2 = Vector2f(
            cos(static_cast<float>(M_PI) / 2.0f - angle),
            sin(static_cast<float>(M_PI) / 2.0f - angle)
        );

        shape.setPoint(i + 1, c1 + Vector2f(-o1.x, -o1.y) * radius);
        shape.setPoint(circlePointsCount + 3 + i, c2 + Vector2f(o2.x, -o2.y) * radius);
        shape.setPoint(circlePointsCount * 2 + 5 + i, c3 + Vector2f(o1.x, o1.y) * radius);
        shape.setPoint(circlePointsCount * 3 + 7 + i, c4 + Vector2f(-o2.x, o2.y) * radius);
    }

    return shape;
}
