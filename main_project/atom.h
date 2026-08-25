#pragma once
#include "main.h"
#include "timer.h"

vec3 f, nf;
float d;

float _time;
class atom {
public:
	object graph_obj;
	//vec3 vel;
	void create(vec3d pos = {}, vec3 vel = {}) {
		graph_obj = object{};
		graph_obj.pos = pos;
		//graph_obj.scl = { 0.5f, 0.5f , 0.5f };
		tetrahedrons ts = generateIcosahedron();
		setLinks(ts);
		graph_obj.addTetrahedron(ts, { 1, 1, 1, 1 }, dyn_triangles);
		UniversalRender::addObject(graph_obj);
		//this->vel = vel;
		createSphereBody(graph_obj);
		addBodyVel(graph_obj.id, (vel + cross(pos, { 0, 1, 0 }) / 1000) * 100);
	}
	void update1(atom& j) {
		f = j.graph_obj.pos - graph_obj.pos;
		nf = norm(f);
		d = f.length_squared();
		addBodyVel(graph_obj.id, nf / d * _time * 100);
		//vel += nf * (1 / d/* - 1 / (d * d * d)*/) * _time;
		/*if (d < 1) {
			vel -= f * dot(vel, f) / sqrt(d) * 0.05f;
			j.vel += f * dot(vel, f) / sqrt(d) * 0.05f;
		}*/
	}
	/*void update2() {
		if (vel.length_squared() > 100) vel = norm(vel) * 10;
		graph_obj.pos += vel * _time;
	}*/
};

atom* atoms;
int cursor;
int size;
void MallocAtoms(int n) {
	size = n;
	cursor = 0;
	free(atoms);
	atoms = (atom*)calloc(n, sizeof(atom));
}
void Update(float);
void StartAsyncUpdate(int t) {
	_time = t / 1000.0f;
	setTimer(Update, t);
}
void StartAsyncUpdate() {
	std::thread{ []() { while (1) Update(0); } }.detach();
}
long t_last;
void Update(float time) {
	long t_start = clock();
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i == j) continue;
			atoms[i].update1(atoms[j]);
		}
	}
	update(time);
	for (int i = 0; i < size; i++) {
		updateObjectData(atoms[i].graph_obj);
		//atoms[i].update2();
	}
	long t_end = clock();
	_time = (t_end - t_last) / 1000.0f;
	std::cout << time << ' ' << _time << ' ' << (t_end - t_start) / 1000.0f << " s\n";
	t_last = t_end;
}
void CreateAtom(vec3d pos = {}, vec3 vel = {}) {
	atoms[cursor].create(pos, vel);
	cursor++;
}
void CreateAtomsCloud(vec3d from, vec3 to, float vel_max, int n) {
	std::mt19937 gen(0);
	std::uniform_int_distribution<> rx(from.x * 256, to.x * 256);
	std::uniform_int_distribution<> ry(from.y * 256, to.y * 256);
	std::uniform_int_distribution<> rz(from.z * 256, to.z * 256);
	std::uniform_int_distribution<> rvx(-1000, 1000);
	std::uniform_int_distribution<> rvy(-1000, 1000);
	std::uniform_int_distribution<> rvz(-1000, 1000);
	std::uniform_int_distribution<> rv(0, vel_max * 256);

	MallocAtoms(n);
	for (int i = 0; i < n; i++) {
		atoms[i].create({ rx(gen) / 256.0f, ry(gen) / 256.0f, rz(gen) / 256.0f }, { norm(vec3{(float)rvx(gen), (float)rvy(gen), (float)rvz(gen)}) * rv(gen) / 256 });
	}
}