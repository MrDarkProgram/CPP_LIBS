#include "main.h"

struct Physcraft {
	Planets& planets;
	PlanetData& star;
	PlanetData& planet1;
	PlanetData& planet2;
	object* craft;
	object* trajectory;
	vec3 velocity{};
	vec3 lastPos{};
	Physcraft(Planets& planets, PlanetData& star, PlanetData& planet1, PlanetData& planet2) : planets(planets), star(star), planet1(planet1), planet2(planet2) {
		craft = UniversalRender2::addObject({});
		craft->addTriangles(generateSphere(0), { 1, 1, 1, 1 }, drawMode::dyn_triangles);
		craft->scl = { 1, 10, 1 };
		trajectory = UniversalRender2::addObject({});
		trajectory->color = { 1, 1, 1, 1 };
		trajectory->mode = dyn_lines;
	}
	void setPositionAndVelocity(vec3 pos, vec3 vel) {
		craft->pos = pos;
		lastPos = pos;
		velocity = vel;
	}
	void update(float dt) {
		vec3 resultAcceleration{};
		for (PlanetData& data : planets) {
			if (data.planet == planet1.planet) continue;
			resultAcceleration +=
				norm(data.planet->pos - craft->pos) * G * data.Mass / (data.planet->pos - craft->pos).length_squared() * planets.GlobalSemiMajorAxisModifier * planets.GlobalSemiMajorAxisModifier;
		}
		velocity += resultAcceleration * dt * 0.864;
		craft->pos += velocity * dt * 0.000864;

		if ((lastPos - craft->pos).length() > 1) {
			trajectory->vert.push_back({ lastPos });
			trajectory->vert.push_back({ craft->pos });
			lastPos = craft->pos;
		}
	}
};

struct Spacecraft {
	Planets& planets;
	PlanetData& star;
	PlanetData& planet1;
	PlanetData& planet2;
	PlanetData transOrbit{};
	PlanetData secondOrbit{};
	object phantom{};
	Physcraft physcraft;
	double maneuver1Time{};
	double maneuver2Time{};
	bool wasManeuver1{};
	bool wasManeuver2{};
	Spacecraft(Planets& planets, PlanetData& star, PlanetData& planet1, PlanetData& planet2, double global_t) :
		planets(planets), star(star), planet1(planet1), planet2(planet2), physcraft(planets, star, planet1, planet2) {

		transOrbit.planet = &phantom;
		transOrbit.ColorR = 0.5;
		transOrbit.ColorG = 0.5;
		transOrbit.ColorB = 0.5;
		calculateHomanOrbit(transOrbit, planets, star, planet1, planet2, global_t);
		transOrbit.orbit = UniversalRender2::addObject({});
		transOrbit.orbit->mode = lines;
		if (planet2.SemiMajorAxis > planet1.SemiMajorAxis) transOrbit.orbit->vert = drawOrbit05(transOrbit);
		else transOrbit.orbit->vert = drawOrbit50(transOrbit);
		maneuver1Time = tNow; // костыль
		maneuver2Time = maneuver1Time + calculateT(planets, star, transOrbit) * 500;

		secondOrbit.ColorR = 0.5;
		secondOrbit.ColorG = 0.5;
		secondOrbit.ColorB = 0.5;
		secondOrbit.SemiMajorAxis = planet2.SemiMajorAxis;
		secondOrbit.Eccentricity = planet2.Eccentricity;
		secondOrbit.LongitudeOfTheAscendingNode = transOrbit.LongitudeOfTheAscendingNode;
		secondOrbit.Inclination = transOrbit.Inclination;
		secondOrbit.ArgumentOfPeriapsis = planet2.ArgumentOfPeriapsis + planet2.LongitudeOfTheAscendingNode - planet1.LongitudeOfTheAscendingNode;
		secondOrbit.MeanAnomaly = planet2.MeanAnomaly;
		secondOrbit.calculateQM();
		secondOrbit.orbit = UniversalRender2::addObject({});
		secondOrbit.orbit->mode = lines;
		secondOrbit.orbit->vert = drawOrbit(secondOrbit);

		UniversalRender2::setRewrite();
	}
	~Spacecraft() {
		UniversalRender2::removeObject(transOrbit.orbit);
		UniversalRender2::removeObject(secondOrbit.orbit);
	}
	void update(double global_t, float t) {
		if (global_t >= maneuver2Time) {
			if (!wasManeuver2) {
				transOrbit.SemiMajorAxis = planet2.SemiMajorAxis;
				transOrbit.Eccentricity = planet2.Eccentricity;
				transOrbit.ArgumentOfPeriapsis = planet2.ArgumentOfPeriapsis + planet2.LongitudeOfTheAscendingNode - planet1.LongitudeOfTheAscendingNode;
				transOrbit.MeanAnomaly = planet2.MeanAnomaly;
				transOrbit.SiderealOrbitalPeriod = planet2.SiderealOrbitalPeriod;
				transOrbit.calculateQM();
				wasManeuver2 = false;
			}
			moveObject(transOrbit, global_t);
			physcraft.setPositionAndVelocity(phantom.pos, {});
		}
		if (global_t >= maneuver1Time) {
			moveObject(transOrbit, global_t - maneuver1Time);
			if (!wasManeuver1) {
				float trueAnomaly = 0;
				if (planet2.SemiMajorAxis < planet1.SemiMajorAxis) trueAnomaly = 3.1415;
				physcraft.setPositionAndVelocity(transOrbit.planet->pos, norm(transOrbit.planet->pos - transOrbit.lastPos) * calculateV(planets, star, transOrbit, trueAnomaly));
				wasManeuver1 = true;
			}
			physcraft.update(t)ж
		}
		else {
			moveObject(transOrbit, global_t - maneuver1Time);
			physcraft.setPositionAndVelocity(planet1.planet->pos, {});
		}
		
	}
};