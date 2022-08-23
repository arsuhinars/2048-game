#include <string>
#include <iostream>
#include "glow_effect.h"

using namespace std;
using namespace sf;

static const string SHADER_PROGRAM = "\
uniform vec2 resolution;	\
uniform mat4 transform;		\
uniform vec2 size;			\
uniform float radius;		\
uniform vec4 color;			\
uniform float blur;			\
uniform float spread;		\
							\
							\
float ease(float t) {		\
	return t;			\
}							\
							\
float findDist(vec2 p) {	\
	vec2 halfSize = size / 2;	\
	vec2 boxCenter = halfSize + vec2(blur + spread);\
	vec2 radiusCenter = halfSize - vec2(radius);	\
													\
	vec2 delta = abs(p - boxCenter);				\
													\
	float radiusDist = length(delta - radiusCenter) - radius;\
				\
	float d = 0;\
	d += step(halfSize.x, delta.x) * (1 - step(radiusCenter.y, delta.y)) * (delta.x - halfSize.x);	\
	d += step(halfSize.y, delta.y) * (1 - step(radiusCenter.x, delta.x)) * (delta.y - halfSize.y);	\
	d += step(radiusCenter.x, delta.x) * step(radiusCenter.y, delta.y) * max(radiusDist, 0);		\
				\
	return d;	\
}				\
				\
void main() {	\
	vec2 sp = vec2(gl_FragCoord.x, resolution.y - gl_FragCoord.y);\
	vec2 p = (transform * vec4(sp, 0, 1)).xy;\
							\
	float k = 1 - max(findDist(p) - spread, 0) / blur;\
	k = max(k, 0);			\
	k = 1 - ease(1 - k);	\
							\
	gl_FragColor = vec4(color.xyz, color.w * k);\
}\
";

static const string RESOLUTION_UNIFORM = "resolution";
static const string TRANSFORM_UNIFORM = "transform";
static const string SIZE_UNIFORM = "size";
static const string RADIUS_UNIFORM = "radius";
static const string GLOW_COLOR_UNIFORM = "color";
static const string GLOW_BLUR_UNIFORM = "blur";
static const string GLOW_SPREAD_UNIFORM = "spread";

static unique_ptr<Shader> shader;

arsuhinars::GlowEffect::GlowEffect(
	const sf::Vector2f& size,
	float radius,
	const sf::Color& glowColor,
	float glowBlur,
	float glowSpread
) {
	if (!shader) {
		shader = make_unique<Shader>();
		shader->loadFromMemory(SHADER_PROGRAM, Shader::Type::Fragment);
	}

	GlowEffect::size = size;
	GlowEffect::radius = radius;
	GlowEffect::glowColor = glowColor;
	GlowEffect::glowBlur = glowBlur;
	GlowEffect::glowSpread = glowSpread;

	updateSize();
}

void arsuhinars::GlowEffect::setSize(const sf::Vector2f& size)
{
	GlowEffect::size = size;
	updateSize();
}

const sf::Vector2f& arsuhinars::GlowEffect::getSize()
{
	return size;
}

void arsuhinars::GlowEffect::setRadius(float radius)
{
	GlowEffect::radius = radius;
}

float arsuhinars::GlowEffect::getRadius()
{
	return radius;
}

void arsuhinars::GlowEffect::setGlowColor(const sf::Color& color)
{
	glowColor = color;
}

const sf::Color& arsuhinars::GlowEffect::getGlowColor()
{
	return glowColor;
}

void arsuhinars::GlowEffect::setGlowBlur(float blur)
{
	glowBlur = blur;
	updateSize();
}

float arsuhinars::GlowEffect::getGlowBlur()
{
	return glowBlur;
}

void arsuhinars::GlowEffect::setGlowSpread(float spread)
{
	glowSpread = spread;
	updateSize();
}

float arsuhinars::GlowEffect::getGlowSpread()
{
	return glowSpread;
}

void arsuhinars::GlowEffect::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (glowColor.a == 0) {
		return;
	}

	auto resolution = target.getSize();

	states.shader = shader.get();
	states.transform *= edgeTransform;
	states.transform *= getTransform();

	shader->setUniform(
		RESOLUTION_UNIFORM,
		Vector2f(static_cast<float>(resolution.x), static_cast<float>(resolution.y))
	);
	shader->setUniform(
		TRANSFORM_UNIFORM,
		Glsl::Mat4(states.transform.getInverse())
	);
	shader->setUniform(SIZE_UNIFORM, size);
	shader->setUniform(RADIUS_UNIFORM, radius);
	shader->setUniform(GLOW_COLOR_UNIFORM, Glsl::Vec4(glowColor));
	shader->setUniform(GLOW_BLUR_UNIFORM, glowBlur);
	shader->setUniform(GLOW_SPREAD_UNIFORM, glowSpread);

	target.draw(shape, states);
}

void arsuhinars::GlowEffect::updateSize()
{
	shape.setSize(size + (glowBlur + glowSpread) * 2.0f * Vector2f(1.0f, 1.0f));

	edgeTransform = Transform::Identity;
	edgeTransform.translate(Vector2f(-1.0f, -1.0f) * (glowBlur + glowSpread));
	// shape.setOrigin(Vector2f(1.0f, 1.0f) * (glowBlur + glowSpread));
}
