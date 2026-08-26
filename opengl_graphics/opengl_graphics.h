#pragma once

#include "../math/math.h"

#include <string>
#include <vector>
#include <set>
#include <map>

#ifdef OPENGL_GRAPHICS_EXPORTS
#define OPENGL_GRAPHICS_API __declspec(dllexport)
#else
#pragma comment(lib, "../x64/Release/opengl_graphics.lib")
#define OPENGL_GRAPHICS_API __declspec(dllimport)
#endif

// ======================== Утилиты

class OPENGL_GRAPHICS_API Shader {
private:
	int program;
	void checkShaderError(int shader, int shaderType);
	void checkProgramError(int program);
	int createShader(const char* path, int shaderType);
	std::string checkIncludesAndInclude(std::string& line);
	std::ifstream checkFilePathAndOpen(const char* path);
public:
	Shader(const char* path_vert, const char* path_frag);
	Shader(const char* path_vert, const char* path_geom, const char* path_frag);
	~Shader();
	void use() const;
};

class OPENGL_GRAPHICS_API VertexArray {
private:
	unsigned VAO;
public:
	VertexArray(int* config, int size);
	~VertexArray();
	void use() const;
};

class OPENGL_GRAPHICS_API VertexBuffer {
private:
	unsigned VBO;
public:
	VertexBuffer();
	~VertexBuffer();
	void use() const;
};

class OPENGL_GRAPHICS_API UniformBuffer {
private:
	unsigned UBO;
public:
	UniformBuffer(int index);
	~UniformBuffer();
	void use() const;
};

class OPENGL_GRAPHICS_API ShaderBuffer {
private:
	unsigned SSB;
public:
	ShaderBuffer(int index);
	~ShaderBuffer();
	void use() const;
};

class OPENGL_GRAPHICS_API Texture {
private:
	unsigned texture;
	unsigned position;
	int width, height;
public:
	Texture(std::string path, unsigned position);
	~Texture();
	void SetPosition(unsigned position);
	unsigned GetTextureWidth() const;
	unsigned GetTextureHeight() const;
	void use() const;
};

// ======================== Ядро

class OPENGL_GRAPHICS_API Window {
private:
#ifdef OPENGL_GRAPHICS_EXPORTS
	static GLFWwindow* window;
	static void resize(GLFWwindow* window, int width, int height);
#endif
	static std::set<void(*)(float)> updateEvent;
	static std::set<void(*)(float, float)> resizeEvent;
	static int width;
	static int height;
public:
#ifdef OPENGL_GRAPHICS_EXPORTS
	static GLFWwindow* getWindow();
#endif
	static void create();
	static void run();
	static void create(int w, int h, const char* name);
	static void close();
	static void addUpdateEvent(void(*)(float));
	static void remUpdateEvent(void(*)(float));
	static void addResizeEvent(void(*)(float, float));
	static void remResizeEvent(void(*)(float, float));
	static int getWidth();
	static int getHeight();
	static void enableBlockFaceCulling();
	static void disableBlockFaceCulling();
	static void setSkyColor(vec4 color);
	// 1 - enable; 0 - disable; -1 - adaptive
	static void setVSync(int mode);
};

class OPENGL_GRAPHICS_API Camera {
private:
	vec3d pos;
	vec3 forward{0, 0, 1};
	vec3 up{0, 1, 0};
	float fov{ 1.57f };
	float farFront{ 1000.0f };
	float nearFront{ 0.1f };
public:
	mat4 getView();
	vec3d getPos();
	vec3 getForward();
	vec3 getUp();
	float getFov();
	float getFarFront();
	float getNearFront();
	void setPos(vec3d pos);
	void setForward(vec3 forward);
	void setUp(vec3 up);
	void setFov(float);
	void setFarFront(float);
	void setNearFront(float);

};

class OPENGL_GRAPHICS_API UniversalRender {
private:
	static std::vector<object*> objects;
	static Shader* shader;
	static VertexBuffer* vbo;
	static VertexArray* vao;
	static VertexBuffer* vbo_dyn;
	static VertexArray* vao_dyn;
	static UniformBuffer* ubo;
	static bool rewrite;
	static int count;
	static int point1;
	static int point2;
	static int point3;
	static Camera* camera;
	static std::vector<float> collectObjectsToData(drawMode mode, bool alpha);
public:
	static void create();
	static void free();
	static int addObject(object& object);
	static void removeObject(int index);
	static void update(float time);
	static void resize(float w, float h);
	static void setRewrite();
	static void setCameraPtr(Camera* camera);
};

class OPENGL_GRAPHICS_API UniversalRender2 {
private:
	static std::vector<object> objects;
	static Shader* shader;
	static VertexBuffer* vbo;
	static VertexArray* vao;
	static VertexBuffer* vbo_dyn;
	static VertexArray* vao_dyn;
	static UniformBuffer* ubo;
	static ShaderBuffer* sbo;
	static bool rewrite;
	static int count;
	static int point1;
	static int point2;
	static int point3;
	static unsigned selected_id;
	static unsigned highlight_id;
	static unsigned super_selected_id;
	static bool highlight_selected;
	static Camera* camera;
	static std::vector<float> collectObjectsToData(drawMode mode, bool alpha);
public:
	static void create();
	static void free();
	static object* addObject(object object);
	static bool removeObject(object* object);
	static void update(float time);
	static void resize(float w, float h);
	static void setRewrite();
	static void setCameraPtr(Camera* camera);
	static void reserveObjects(unsigned);
	static unsigned getSelectedID();
	static unsigned getHighlightID();
	static unsigned getSuperSelectedID();
	static void setHighlightID(unsigned);
	static void setSuperSelectedID(unsigned);
	static void highlightSelected(bool = true);
	static object* getSelectedObject();
	static object* getSuperSelectedObject();
};

class OPENGL_GRAPHICS_API CameraMoveFixedUp {
private:
	static Camera* camera;
public:
	static std::set<void(*)(int, int)> mouseEvent;
	static std::set<void(*)(int, int, int, int)> keyEvent;
	static void create(Camera* camera, bool mouseLKMtoMove = false, float speed = 0.005f, float sensitivity = 0.15f, bool mouseRKMtoMove = false, bool _useQEtoUpAndDown = false, float boost = 5);
	static void update(float time);
	static void addMouseEvent(void(*)(int, int));
	static void remMouseEvent(void(*)(int, int));
	static void addKeyEvent(void(*)(int, int, int, int));
	static void remKeyEvent(void(*)(int, int, int, int));
	static void setYRotDeg(float);
	static bool isKeyPressed(int key);
};

class OPENGL_GRAPHICS_API ConsoleFPS {
private:
	static float t;
public:
	static void create();
	static void update(float time);
};

// ======================== GUI

class OPENGL_GRAPHICS_API GUIElement {
protected:
	object* objPtr;
	Texture* texturePtr;
	vec2 posInTex{};
	vec2 sizeInTex{};
	bool dyn;
	virtual void genVerts();
public:
	GUIElement(vec2 pos, vec2 size, Texture* texturePtr, vec2 posInTex, vec2 sizeInTex, bool dyn = false, bool genVerts = true);
	void enableElement(bool enable = true);
	void setTexturePosAndSize(vec2 pos, vec2 size);
};

class OPENGL_GRAPHICS_API GUIText : public GUIElement {
protected:
	std::string text;
	void genVerts() override;
public:
	GUIText(vec2 pos, float size, Texture* texturePtr, std::string text, bool dyn = false);
	void setText(std::string text);
};

const std::map<char, vec2> charTable = {
	{'A', {0, 0}},
	{'B', {1, 0}},
	{'C', {2, 0}},
	{'D', {3, 0}},
	{'E', {4, 0}},
	{'F', {5, 0}},
	{'G', {6, 0}},
	{'H', {7, 0}},
	{'I', {8, 0}},
	{'J', {9, 0}},
	{'K', {10, 0}},
	{'L', {11, 0}},
	{'M', {12, 0}},
	{'N', {13, 0}},
	{'O', {14, 0}},
	{'P', {15, 0}},
	{'Q', {16, 0}},
	{'R', {17, 0}},
	{'S', {18, 0}},
	{'T', {19, 0}},
	{'U', {20, 0}},
	{'V', {21, 0}},
	{'W', {22, 0}},
	{'X', {23, 0}},
	{'Y', {24, 0}},
	{'Z', {25, 0}},

	{'a', {26, 0}},
	{'b', {27, 0}},
	{'c', {28, 0}},
	{'d', {29, 0}},
	{'e', {30, 0}},
	{'f', {31, 0}},
	{'g', {32, 0}},
	{'h', {33, 0}},
	{'i', {34, 0}},
	{'j', {35, 0}},
	{'k', {36, 0}},
	{'l', {37, 0}},
	{'m', {38, 0}},
	{'n', {39, 0}},
	{'o', {40, 0}},
	{'p', {41, 0}},
	{'q', {42, 0}},
	{'r', {43, 0}},
	{'s', {44, 0}},
	{'t', {45, 0}},
	{'u', {46, 0}},
	{'v', {47, 0}},
	{'w', {48, 0}},
	{'x', {49, 0}},
	{'y', {50, 0}},
	{'z', {51, 0}},

	{'0', {52, 0}},
	{'1', {53, 0}},
	{'2', {54, 0}},
	{'3', {55, 0}},
	{'4', {56, 0}},
	{'5', {57, 0}},
	{'6', {58, 0}},
	{'7', {59, 0}},
	{'8', {60, 0}},
	{'9', {61, 0}},

	{'.', {62, 0}},
	{',', {63, 0}},
	{'"', {2, 1}},
	{'\'', {3, 1}},
	{'?', {4, 1}},
	{'!', {5, 1}},
	{'@', {6, 1}},
	{'_', {7, 1}},
	{'*', {8, 1}},
	{'#', {9, 1}},
	{'$', {10, 1}},
	{'%', {11, 1}},
	{'&', {12, 1}},
	{'{', {13, 1}},
	{'}', {14, 1}},
	{'+', {15, 1}},
	{'-', {16, 1}},
	{'/', {17, 1}},
	{':', {18, 1}},
	{';', {19, 1}},
	{'<', {20, 1}},
	{'=', {21, 1}},
	{'>', {22, 1}},
	{'[', {23, 1}},
	{'\\', {24, 1}},
	{']', {25, 1}},
	{'^', {26, 1}},
	{'`', {27, 1}},
	{'{', {28, 1}},
	{'|', {29, 1}},
	{'}', {30, 1}},
	{'~', {31, 1}},
	{' ', {32, 1}},

	{'А', {9, 12}},
	{'Б', {10, 12}},
	{'В', {11, 12}},
	{'Г', {12, 12}},
	{'Д', {13, 12}},
	{'Е', {14, 12}},
	{'Ё', {60, 11}},
	{'Ж', {15, 12}},
	{'З', {16, 12}},
	{'И', {17, 12}},
	{'Й', {18, 12}},
	{'К', {19, 12}},
	{'Л', {20, 12}},
	{'М', {21, 12}},
	{'Н', {22, 12}},
	{'О', {23, 12}},
	{'П', {24, 12}},
	{'Р', {25, 12}},
	{'С', {26, 12}},
	{'Т', {27, 12}},
	{'У', {28, 12}},
	{'Ф', {29, 12}},
	{'Х', {30, 12}},
	{'Ц', {31, 12}},
	{'Ч', {32, 12}},
	{'Ш', {33, 12}},
	{'Щ', {34, 12}},
	{'Ъ', {35, 12}},
	{'Ы', {36, 12}},
	{'Ь', {37, 12}},
	{'Э', {38, 12}},
	{'Ю', {39, 12}},
	{'Я', {40, 12}},

	{'а', {41, 12}},
	{'б', {42, 12}},
	{'в', {43, 12}},
	{'г', {44, 12}},
	{'д', {45, 12}},
	{'е', {46, 12}},
	{'ё', {8, 13}},
	{'ж', {47, 12}},
	{'з', {48, 12}},
	{'и', {49, 12}},
	{'й', {50, 12}},
	{'к', {51, 12}},
	{'л', {52, 12}},
	{'м', {53, 12}},
	{'н', {54, 12}},
	{'о', {55, 12}},
	{'п', {56, 12}},
	{'р', {57, 12}},
	{'с', {58, 12}},
	{'т', {59, 12}},
	{'у', {60, 12}},
	{'ф', {61, 12}},
	{'х', {62, 12}},
	{'ц', {63, 12}},
	{'ч', {64, 12}},
	{'ш', {65, 12}},
	{'щ', {0, 13}},
	{'ъ', {1, 13}},
	{'ы', {2, 13}},
	{'ь', {3, 13}},
	{'э', {4, 13}},
	{'ю', {5, 13}},
	{'я', {6, 13}},
};

#define KEY_SPACE              32
#define KEY_APOSTROPHE         39  /* ' */
#define KEY_COMMA              44  /* , */
#define KEY_MINUS              45  /* - */
#define KEY_PERIOD             46  /* . */
#define KEY_SLASH              47  /* / */
#define KEY_0                  48
#define KEY_1                  49
#define KEY_2                  50
#define KEY_3                  51
#define KEY_4                  52
#define KEY_5                  53
#define KEY_6                  54
#define KEY_7                  55
#define KEY_8                  56
#define KEY_9                  57
#define KEY_SEMICOLON          59  /* ; */
#define KEY_EQUAL              61  /* = */
#define KEY_A                  65
#define KEY_B                  66
#define KEY_C                  67
#define KEY_D                  68
#define KEY_E                  69
#define KEY_F                  70
#define KEY_G                  71
#define KEY_H                  72
#define KEY_I                  73
#define KEY_J                  74
#define KEY_K                  75
#define KEY_L                  76
#define KEY_M                  77
#define KEY_N                  78
#define KEY_O                  79
#define KEY_P                  80
#define KEY_Q                  81
#define KEY_R                  82
#define KEY_S                  83
#define KEY_T                  84
#define KEY_U                  85
#define KEY_V                  86
#define KEY_W                  87
#define KEY_X                  88
#define KEY_Y                  89
#define KEY_Z                  90
#define KEY_LEFT_BRACKET       91  /* [ */
#define KEY_BACKSLASH          92  /* \ */
#define KEY_RIGHT_BRACKET      93  /* ] */
#define KEY_GRAVE_ACCENT       96  /* ` */
#define KEY_WORLD_1            161
#define KEY_WORLD_2            162

#define KEY_ESCAPE             256
#define KEY_ENTER              257
#define KEY_TAB                258
#define KEY_BACKSPACE          259
#define KEY_INSERT             260
#define KEY_DELETE             261
#define KEY_RIGHT              262
#define KEY_LEFT               263
#define KEY_DOWN               264
#define KEY_UP                 265
#define KEY_PAGE_UP            266
#define KEY_PAGE_DOWN          267
#define KEY_HOME               268
#define KEY_END                269
#define KEY_CAPS_LOCK          280
#define KEY_SCROLL_LOCK        281
#define KEY_NUM_LOCK           282
#define KEY_PRINT_SCREEN       283
#define KEY_PAUSE              284
#define KEY_F1                 290
#define KEY_F2                 291
#define KEY_F3                 292
#define KEY_F4                 293
#define KEY_F5                 294
#define KEY_F6                 295
#define KEY_F7                 296
#define KEY_F8                 297
#define KEY_F9                 298
#define KEY_F10                299
#define KEY_F11                300
#define KEY_F12                301
#define KEY_F13                302
#define KEY_F14                303
#define KEY_F15                304
#define KEY_F16                305
#define KEY_F17                306
#define KEY_F18                307
#define KEY_F19                308
#define KEY_F20                309
#define KEY_F21                310
#define KEY_F22                311
#define KEY_F23                312
#define KEY_F24                313
#define KEY_F25                314
#define KEY_KP_0               320
#define KEY_KP_1               321
#define KEY_KP_2               322
#define KEY_KP_3               323
#define KEY_KP_4               324
#define KEY_KP_5               325
#define KEY_KP_6               326
#define KEY_KP_7               327
#define KEY_KP_8               328
#define KEY_KP_9               329
#define KEY_KP_DECIMAL         330
#define KEY_KP_DIVIDE          331
#define KEY_KP_MULTIPLY        332
#define KEY_KP_SUBTRACT        333
#define KEY_KP_ADD             334
#define KEY_KP_ENTER           335
#define KEY_KP_EQUAL           336
#define KEY_LEFT_SHIFT         340
#define KEY_LEFT_CONTROL       341
#define KEY_LEFT_ALT           342
#define KEY_LEFT_SUPER         343
#define KEY_RIGHT_SHIFT        344
#define KEY_RIGHT_CONTROL      345
#define KEY_RIGHT_ALT          346
#define KEY_RIGHT_SUPER        347
#define KEY_MENU               348