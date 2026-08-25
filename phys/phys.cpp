#include "main.h"

void initPhys() {
	physWorld = physCommon.createPhysicsWorld();
	physWorld->setNbIterationsVelocitySolver(1);
	physWorld->setNbIterationsPositionSolver(1);
}

struct ObjRb
{
	object& obj;
	rp::RigidBody* rb;
};
std::vector<ObjRb> objs{};
std::unordered_map<int, rp::RigidBody*> hash_objs{};
object* objects;
int size;
void CallocAtoms(int n) {
	size = n;
	free(objects);
	objects = (object*)calloc(n, sizeof(object));
}

void createBody(object& obj) {
	rp::Transform tr{ TORPVEC3D obj.pos, toRpQuat(obj.rot) };
	rp::RigidBody* rb = physWorld->createRigidBody(tr);
	rb->setType(rp::BodyType::STATIC);
	objs.push_back({obj, rb});

	std::vector<float> vert;
	std::vector<int> ind;
	int n{};
	for (vertex& v : obj.vert) {
		vert.push_back(v.pos.x);
		ind.push_back(n * 3);
		vert.push_back(v.pos.y);
		ind.push_back(n * 3 + 1);
		vert.push_back(v.pos.z);
		ind.push_back(n * 3 + 2);
		n++;
	}

	rp::PolygonVertexArray::PolygonFace* polygonFaces = new rp::PolygonVertexArray::PolygonFace[n];
	rp::PolygonVertexArray::PolygonFace* face = polygonFaces;
	for (int i = 0; i < n; i++) {
		face->indexBase = i * 3;
		face->nbVertices = 3;
		face++;
	}

	rp::PolygonVertexArray* polygonVertexArray = new rp::PolygonVertexArray(n, vert.data(), 3 * sizeof(float), ind.data(), sizeof(int), n / 3, polygonFaces,
		rp::PolygonVertexArray::VertexDataType::VERTEX_FLOAT_TYPE,
		rp::PolygonVertexArray::IndexDataType::INDEX_INTEGER_TYPE);

	std::vector<rp::Message> messages;
	rp::ConvexMesh* convexMesh = physCommon.createConvexMesh(*polygonVertexArray, messages);

	if (messages.size() > 0) {
		for (const rp3d::Message& message : messages) {
			std::string messageType;
			switch (message.type) {
			case rp3d::Message::Type::Information:
				messageType = "info";
				break;
			case rp3d::Message::Type::Warning:
				messageType = "warning";
				break;
			case rp3d::Message::Type::Error:
				messageType = "error";
				break;
			}
			std::cout << "Message (" << messageType << "): " << message.text << std::endl;
		}
	}
	std::cout << "convexMesh: " << convexMesh << '\n';

    rp::ConvexMeshShape* shape = physCommon.createConvexMeshShape(convexMesh);
    rp::Collider* collider = rb->addCollider(shape, rp::Transform::identity());
    collider->setIsSimulationCollider(0);
}

unsigned testRay(vec3d start, vec3d end) {
    rp::Ray ray{TORPVEC3D start, TORPVEC3D end};
    double length = (start - end).length_squared();
    unsigned id{};
    for (int i = 0; i < objs.size(); i++) {
        rp::RaycastInfo info{};
        if (objs[i].rb->raycast(ray, info)) {
            double l = (start - TOVEC3D info.worldPoint).length_squared();
            if (l < length) {
                length = l;
                id = objs[i].obj.id;
            }
            std::cout << objs[i].obj.id << ' ' << length << ' ' << l << '\n';
        }
    }
    return id;
}


void createSphereBody(object& obj) {
	rp::Transform tr{ TORPVEC3D obj.pos, toRpQuat(obj.rot) };
	rp::RigidBody* rb = physWorld->createRigidBody(tr);
	//rb->setType(rp::BodyType::DYNAMIC);
	//rb->setIsAllowedToSleep(0);
	rb->enableGravity(0);
	//rb->setLinearDamping(0);
	//rb->setAngularDamping(0);
	//rb->setMass(1);
	rp::SphereShape* shape = physCommon.createSphereShape(0.8f);
	rp::Collider* collider;
	collider = rb->addCollider(shape, rp::Transform::identity());
	collider->getMaterial().setBounciness(0.5f);
	collider->getMaterial().setFrictionCoefficient(0.05f);
	hash_objs[obj.id] = rb;
}
void createSphereBodyG(int i, vec3d pos, vec3 scl, vec3 vel) {
	object obj = object{};
	objects[i] = obj;
	objects[i].pos = pos;
	objects[i].scl = scl;
	tetrahedrons ts = generateIcosahedron();
	setLinks(ts);
	objects[i].addTetrahedron(ts, { 1, 1, 1, 1 }, triangles);
	UniversalRender::addObject(objects[i]);

	rp::Transform tr{ TORPVEC3D objects[i].pos, toRpQuat(objects[i].rot) };
	rp::RigidBody* rb = physWorld->createRigidBody(tr);
	//rb->setType(rp::BodyType::DYNAMIC);
	//rb->setIsAllowedToSleep(0);
	rb->enableGravity(0);
	//rb->setLinearDamping(0);
	//rb->setAngularDamping(0);
	//rb->setMass(1);
	rp::SphereShape* shape = physCommon.createSphereShape(0.8f);
	rp::Collider* collider;
	collider = rb->addCollider(shape, rp::Transform::identity());
	//collider->getMaterial().setBounciness(0.1f);
	//collider->getMaterial().setFrictionCoefficient(0.5f);
	rb->applyWorldForceAtCenterOfMass(toRpVec3(vel));
	hash_objs[objects[i].id] = rb;
	std::cout << objects[i].id << '\n';
}

void addBodyVel(int body_id, vec3 vel) {
	//hash_objs[body_id]->setLinearLockAxisFactor(toRpVec3(vel));
	hash_objs[body_id]->applyWorldForceAtCenterOfMass(toRpVec3(vel));
}

void update(float time) {
	physWorld->update(time);
}
vec3d f;
vec3d nf;
float d;
void updateG(float time) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i == j) continue;
			f = objects[i].pos - objects[j].pos;
			nf = norm(f);
			d = f.length_squared();// посмотреть f nf
			nf = nf / d * time * 100; // посмотреть 100
			hash_objs[objects[i].id]->applyWorldForceAtCenterOfMass(TORPVEC3D nf);
		}

		objects[i].pos = TOVEC3D hash_objs[objects[i].id]->getTransform().getPosition();// посмотреть hash_objs[objects[i].id]
		objects[i].rot = toQuat(hash_objs[objects[i].id]->getTransform().getOrientation());
	}
	physWorld->update(time);
}

void updateObjectData(object& obj) {
	rp::RigidBody* rb = hash_objs[obj.id];
	obj.pos = TOVEC3D rb->getTransform().getPosition();
	obj.rot = toQuat(rb->getTransform().getOrientation());
	//if (rb->isSleeping()) obj.color = {1, 0.5f, 0.5f, 1};
	//else obj.color = {};
}

void createObjectsG(vec3d from, vec3 to, float vel_max, float angular_vel_factor, int n) {
	std::mt19937 gen(0);
	std::uniform_int_distribution<> rx(from.x * 256, to.x * 256);
	std::uniform_int_distribution<> ry(from.y * 256, to.y * 256);
	std::uniform_int_distribution<> rz(from.z * 256, to.z * 256);
	std::uniform_int_distribution<> rvx(-1000, 1000);
	std::uniform_int_distribution<> rvy(-1000, 1000);
	std::uniform_int_distribution<> rvz(-1000, 1000);
	std::uniform_int_distribution<> rv(0, vel_max * 256);
	vec3 pos{ rx(gen) / 256.0f, ry(gen) / 256.0f, rz(gen) / 256.0f };
	vec3 vel{ norm(vec3{(float)rvx(gen), (float)rvy(gen), (float)rvz(gen)}) * rv(gen) / 256 };
	vel += cross(pos, { 0, 1, 0 }) / 1000;
	CallocAtoms(n);
	for (int i = 0; i < n; i++) {
		createSphereBodyG(i, pos, {1, 1, 1}, vel);
	}
}