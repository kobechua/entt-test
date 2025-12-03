#ifndef WINDOW_HPP
#define WINDOW_HPP

// STD. includes
#include <iostream>
// GLAD
#include <glad/glad.h>
// GLFW
#include <GLFW/glfw3.h>
// GLM
#include <glm/glm.hpp>

#define MAX_KEYS     1024
#define MAX_BUTTONS  32

static void glfw_initialisation_error(int error, const char* description);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void window_resize_callback(GLFWwindow* window, int width, int height);
static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
static void mouse_position_callback(GLFWwindow* window, double xpos, double ypos);

/// The class responsible for Window Creation.
class Window
{
public:
    /// The background color of the Window.
    glm::vec4 backgroundColor;
    float deltaMouseX, deltaMouseY;
    mutable float deltaTime;
public:
    Window(const char *title, int width, int height);
    ~Window();

    /// Clears the window screen blank.
    void clear() const;
    /// Updates the window.
    void update() const;
    /// Indicates the current state of the Window.
    bool closed() const;

    /// Gets the current width of the window.
    inline float getWidth() const { return m_Width; }
    /// Gets the current height of the window.
    inline float getHeight() const { return m_Height; }
    /// Gets the current window's pointer to it's native object.
    inline GLFWwindow* getGLFWwindow() const { return m_Window; }

    /// Tells if a particular key on the keyboard was pressed or not.
    bool isKeyPressed(unsigned int keycode);
    /// Tells if a particular key on the keyboard was released or not.
    bool isKeyReleased(unsigned int keycode);
    /// Tells if a particular key on the keyboard is being held or not.
    bool isKeyHeld(unsigned int keycode) const;
    /// Tells if a particular key on the Mouse button was pressed or not.
    bool isMouseButtonPressed(unsigned int button);
    // TODO: To be implemented
    bool isMouseButtonReleased(unsigned int button);
    /// Tells if a particular key on the Mouse button is being held or not.
    bool isMouseButtonHeld(unsigned int button) const;
    /// Gets the current position of the mouse in Screen Space Coordinates.
    void getMousePosition(double& x, double& y) const;
public:
    enum Key
    {
        /* Printable keys */
        GAME_KEY_SPACE              = 32,
        GAME_KEY_APOSTROPHE         = 39,  /* ' */
        GAME_KEY_COMMA              = 44,  /* , */
        GAME_KEY_MINUS              = 45,  /* - */
        GAME_KEY_PERIOD             = 46,  /* . */
        GAME_KEY_SLASH              = 47,  /* / */
        GAME_KEY_0                  = 48,
        GAME_KEY_1                  = 49,
        GAME_KEY_2                  = 50,
        GAME_KEY_3                  = 51,
        GAME_KEY_4                  = 52,
        GAME_KEY_5                  = 53,
        GAME_KEY_6                  = 54,
        GAME_KEY_7                  = 55,
        GAME_KEY_8                  = 56,
        GAME_KEY_9                  = 57,
        GAME_KEY_SEMICOLON          = 59,  /* ; */
        GAME_KEY_EQUAL              = 61,  /* = */
        GAME_KEY_A                  = 65,
        GAME_KEY_B                  = 66,
        GAME_KEY_C                  = 67,
        GAME_KEY_D                  = 68,
        GAME_KEY_E                  = 69,
        GAME_KEY_F                  = 70,
        GAME_KEY_G                  = 71,
        GAME_KEY_H                  = 72,
        GAME_KEY_I                  = 73,
        GAME_KEY_J                  = 74,
        GAME_KEY_K                  = 75,
        GAME_KEY_L                  = 76,
        GAME_KEY_M                  = 77,
        GAME_KEY_N                  = 78,
        GAME_KEY_O                  = 79,
        GAME_KEY_P                  = 80,
        GAME_KEY_Q                  = 81,
        GAME_KEY_R                  = 82,
        GAME_KEY_S                  = 83,
        GAME_KEY_T                  = 84,
        GAME_KEY_U                  = 85,
        GAME_KEY_V                  = 86,
        GAME_KEY_W                  = 87,
        GAME_KEY_X                  = 88,
        GAME_KEY_Y                  = 89,
        GAME_KEY_Z                  = 90,
        GAME_KEY_LEFT_BRACKET       = 91,  /* [ */
        GAME_KEY_BACKSLASH          = 92,  /* \ */
        GAME_KEY_RIGHT_BRACKET      = 93,  /* ] */
        GAME_KEY_GRAVE_ACCENT       = 96,  /* ` */
        GAME_KEY_WORLD_1            = 161, /* non-US #1 */
        GAME_KEY_WORLD_2            = 162, /* non-US #2 */

        /* Function keys */
        GAME_KEY_ESCAPE             = 256,
        GAME_KEY_ENTER              = 257,
        GAME_KEY_TAB                = 258,
        GAME_KEY_BACKSPACE          = 259,
        GAME_KEY_INSERT             = 260,
        GAME_KEY_DELETE             = 261,
        GAME_KEY_RIGHT              = 262,
        GAME_KEY_LEFT               = 263,
        GAME_KEY_DOWN               = 264,
        GAME_KEY_UP                 = 265,
        GAME_KEY_PAGE_UP            = 266,
        GAME_KEY_PAGE_DOWN          = 267,
        GAME_KEY_HOME               = 268,
        GAME_KEY_END                = 269,
        GAME_KEY_CAPS_LOCK          = 280,
        GAME_KEY_SCROLL_LOCK        = 281,
        GAME_KEY_NUM_LOCK           = 282,
        GAME_KEY_PRINT_SCREEN       = 283,
        GAME_KEY_PAUSE              = 284,
        GAME_KEY_F1                 = 290,
        GAME_KEY_F2                 = 291,
        GAME_KEY_F3                 = 292,
        GAME_KEY_F4                 = 293,
        GAME_KEY_F5                 = 294,
        GAME_KEY_F6                 = 295,
        GAME_KEY_F7                 = 296,
        GAME_KEY_F8                 = 297,
        GAME_KEY_F9                 = 298,
        GAME_KEY_F10                = 299,
        GAME_KEY_F11                = 300,
        GAME_KEY_F12                = 301,
        GAME_KEY_F13                = 302,
        GAME_KEY_F14                = 303,
        GAME_KEY_F15                = 304,
        GAME_KEY_F16                = 305,
        GAME_KEY_F17                = 306,
        GAME_KEY_F18                = 307,
        GAME_KEY_F19                = 308,
        GAME_KEY_F20                = 309,
        GAME_KEY_F21                = 310,
        GAME_KEY_F22                = 311,
        GAME_KEY_F23                = 312,
        GAME_KEY_F24                = 313,
        GAME_KEY_F25                = 314,
        GAME_KEY_KP_0               = 320,
        GAME_KEY_KP_1               = 321,
        GAME_KEY_KP_2               = 322,
        GAME_KEY_KP_3               = 323,
        GAME_KEY_KP_4               = 324,
        GAME_KEY_KP_5               = 325,
        GAME_KEY_KP_6               = 326,
        GAME_KEY_KP_7               = 327,
        GAME_KEY_KP_8               = 328,
        GAME_KEY_KP_9               = 329,
        GAME_KEY_KP_DECIMAL         = 330,
        GAME_KEY_KP_DIVIDE          = 331,
        GAME_KEY_KP_MULTIPLY        = 332,
        GAME_KEY_KP_SUBTRACT        = 333,
        GAME_KEY_KP_ADD             = 334,
        GAME_KEY_KP_ENTER           = 335,
        GAME_KEY_KP_EQUAL           = 336,
        GAME_KEY_LEFT_SHIFT         = 340,
        GAME_KEY_LEFT_CONTROL       = 341,
        GAME_KEY_LEFT_ALT           = 342,
        GAME_KEY_LEFT_SUPER         = 343,
        GAME_KEY_RIGHT_SHIFT        = 344,
        GAME_KEY_RIGHT_CONTROL      = 345,
        GAME_KEY_RIGHT_ALT          = 346,
        GAME_KEY_RIGHT_SUPER        = 347,
        GAME_KEY_MENU               = 348
    };

private:
    const char*		m_Title;
    float m_Width,	m_Height;
    GLFWwindow*		m_Window;
    bool			m_Closed;

    bool            m_HeldKeys[MAX_KEYS];
    bool            m_PressedKeys[MAX_KEYS];
    bool            m_ReleasedKeys[MAX_KEYS];
    bool            m_HeldMouseButtons[MAX_BUTTONS];
    bool            m_PressedMouseButtons[MAX_BUTTONS];
    bool            m_ReleasedMouseButtons[MAX_BUTTONS];
    double          m_MouseX;
    double          m_MouseY;
    bool            firstMouse;
    float           lastMouseX, lastMouseY;
    mutable float           m_LastTime;
private :
    bool init();
    friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    friend void window_resize_callback(GLFWwindow* window, int width, int height);
    friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    friend void mouse_position_callback(GLFWwindow* window, double xpos, double ypos);
};

#endif