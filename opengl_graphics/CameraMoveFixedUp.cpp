#include "main.h"

#define TOVEC3 *(vec3*)&

std::set<void(*)(int, int)> CameraMoveFixedUp::mouseEvent;
std::set<void(*)(int, int, int, int)> CameraMoveFixedUp::keyEvent;

// ================================================================================================================= клавиши клавиатуры
std::set<int> _camera_keys{};
void _camera_key_callback(GLFWwindow* window, int key, int scan_code, int action, int mode) {
	if (action == GLFW_PRESS)
		_camera_keys.insert(key);
	else if (action == GLFW_RELEASE)
		_camera_keys.erase(key);
	for (void(*e)(int, int, int, int) : CameraMoveFixedUp::keyEvent) e(key, scan_code, action, mode);
}

// ================================================================================================================= курсор
float _camera_sensitivity;
int _camera_last_x;
int _camera_last_y;
float _camera_yaw = 90;
float _camera_pitch = 0;
glm::vec3* _camera_dir;
extern bool _camera_mouse_hide;
int _camera_center_x;
int _camera_center_y;
bool _camera_first = true;
void _camera_mouse_callback(GLFWwindow* window, double x_pos, double y_pos) {
	if (_camera_first) {
		_camera_last_x = x_pos;
		_camera_last_y = y_pos;
		_camera_first = false;
	}
	else if (_camera_mouse_hide) {

		float x_offset = x_pos - _camera_last_x;
		float y_offset = _camera_last_y - y_pos;
		_camera_last_x = x_pos;
		_camera_last_y = y_pos;

		x_offset *= _camera_sensitivity;
		y_offset *= _camera_sensitivity;

		_camera_yaw += x_offset;
		_camera_pitch += y_offset;

		if (_camera_pitch > 89.9f)
			_camera_pitch = 89.9f;
		if (_camera_pitch < -89.9f)
			_camera_pitch = -89.9f;

		glm::vec3 front;
		front.x = cos(glm::radians(_camera_pitch)) * cos(glm::radians(_camera_yaw));
		front.y = sin(glm::radians(_camera_pitch));
		front.z = cos(glm::radians(_camera_pitch)) * sin(glm::radians(_camera_yaw));
		*_camera_dir = glm::normalize(front);
	}
	//mousePosAction(x_pos, y_pos);
}

// ================================================================================================================= кнопки мыши
bool mouseLKMtoMove;
bool mouseRKMtoMove;
bool useQEtoUpAndDown;
void _camera_mouse_callback2(GLFWwindow* window, int button, int action, int mode) {
	if (mouseLKMtoMove) {
		if (button == 0) {
			if (action) {
				_camera_first = true;
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				_camera_mouse_hide = true;
			}
			else {
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				_camera_mouse_hide = false;
			}
		}
	}
	if (mouseRKMtoMove) {
		if (button == 1) {
			if (action) {
				_camera_first = true;
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				_camera_mouse_hide = true;
			}
			else {
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				_camera_mouse_hide = false;
			}
		}
	}
	for (void(*e)(int, int) : CameraMoveFixedUp::mouseEvent) e(button, action);
	//mouseButtonAction(button, action, mode);
}
void _camera_resize(float w, float h) {
	_camera_last_x = _camera_center_x = w / 2;
	_camera_last_y = _camera_center_y = h / 2;
}

Camera* CameraMoveFixedUp::camera;
glm::vec3 pos;
glm::vec3 dir;
glm::vec3 up;
float _camera_base_speed;
float _camera_boost = 5;
void CameraMoveFixedUp::create(Camera* camera, bool _mouseLKMtoMove, float speed, float sens, bool _mouseRKMtoMove, bool _useQEtoUpAndDown, float boost) {
	mouseLKMtoMove = _mouseLKMtoMove;
	mouseRKMtoMove = _mouseRKMtoMove;
	useQEtoUpAndDown = _useQEtoUpAndDown;
	_camera_base_speed = speed;
	_camera_sensitivity = sens;
	_camera_boost = boost;

	CameraMoveFixedUp::camera = camera;
	vec3 _pos = camera->getPos();
	vec3 _dir = camera->getForward();
	vec3 _up = camera->getUp();
	pos = *(glm::vec3*)& _pos;
	dir = *(glm::vec3*)&_dir;
	up = *(glm::vec3*)&_up;

	if (!mouseLKMtoMove && !mouseRKMtoMove) {
		glfwSetInputMode(Window::getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		_camera_mouse_hide = true;
	}
	_camera_dir = &dir;
	glfwSetKeyCallback(Window::getWindow(), _camera_key_callback);
	glfwSetCursorPosCallback(Window::getWindow(), _camera_mouse_callback);
	glfwSetMouseButtonCallback(Window::getWindow(), _camera_mouse_callback2);
	_camera_resize(Window::getWidth(), Window::getHeight());
	Window::addResizeEvent(_camera_resize);
	Window::addUpdateEvent(update);
	glfwSetCursorPos(Window::getWindow(), _camera_center_x, _camera_center_y);
}

// ================================================================================================================= движение
bool f1;
bool _f1;
float _camera_speed;
bool _camera_mouse_hide;
bool c_space_enter;
bool c_pause;
bool _camera_esc_press;
void CameraMoveFixedUp::update(float time) {
	camera->setPos(TOVEC3 pos);
	camera->setForward(TOVEC3 dir);
	camera->setUp(TOVEC3 up);

	float speed = _camera_speed * time;
	if (_camera_keys.contains(GLFW_KEY_W))
		pos += speed * glm::normalize(glm::vec3(dir.x, 0, dir.z));
	if (_camera_keys.contains(GLFW_KEY_S))
		pos -= speed * glm::normalize(glm::vec3(dir.x, 0, dir.z));
	if (_camera_keys.contains(GLFW_KEY_A))
		pos -= glm::normalize(glm::normalize(glm::cross(dir, up))) * speed;
	if (_camera_keys.contains(GLFW_KEY_D))
		pos += glm::normalize(glm::normalize(glm::cross(dir, up))) * speed;
	if (useQEtoUpAndDown) {
		if (_camera_keys.contains(GLFW_KEY_E))
			pos += glm::normalize(glm::normalize(up)) * speed;
		if (_camera_keys.contains(GLFW_KEY_Q))
			pos -= glm::normalize(glm::normalize(up)) * speed;
	}
	else {
		if (_camera_keys.contains(GLFW_KEY_SPACE))
			pos += glm::normalize(glm::normalize(up)) * speed;
		if (_camera_keys.contains(GLFW_KEY_LEFT_SHIFT))
			pos -= glm::normalize(glm::normalize(up)) * speed;
	}
	if (!mouseLKMtoMove && !mouseRKMtoMove) {
		if (_camera_keys.contains(GLFW_KEY_ESCAPE) && !_camera_esc_press) {
			if (_camera_mouse_hide) {
				glfwSetInputMode(Window::getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				_camera_mouse_hide = false;
			}
			else {
				glfwSetCursorPos(Window::getWindow(), _camera_center_x, _camera_center_y);
				_camera_first = true;
				glfwSetInputMode(Window::getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				_camera_mouse_hide = true;
			}
			_camera_esc_press = true;
		}
		else if (!_camera_keys.contains(GLFW_KEY_ESCAPE)) _camera_esc_press = false;
	}
	if (_camera_keys.contains(GLFW_KEY_LEFT_CONTROL))
		_camera_speed = _camera_base_speed * _camera_boost;
	else
		_camera_speed = _camera_base_speed;


}

void CameraMoveFixedUp::addMouseEvent(void(*e)(int, int))
{
	mouseEvent.insert(e);
}

void CameraMoveFixedUp::remMouseEvent(void(*e)(int, int))
{
	mouseEvent.erase(e);
}

void CameraMoveFixedUp::addKeyEvent(void(*e)(int, int, int, int))
{
	keyEvent.insert(e);
}

void CameraMoveFixedUp::remKeyEvent(void(*e)(int, int, int, int))
{
	keyEvent.erase(e);
}

void CameraMoveFixedUp::setYRotDeg(float r)
{
	_camera_yaw = r;
}

bool CameraMoveFixedUp::isKeyPressed(int key)
{
	return _camera_keys.contains(key);
}
