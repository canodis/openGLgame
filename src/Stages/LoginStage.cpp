#include "LoginStage.hpp"
#include "MainStage.hpp"
#include "Navigator.hpp"
#include <string>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <glfw3.h>

LoginStage::LoginStage()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(Scene::getInstance().window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void LoginStage::initStage()
{
    windowWidth = WIDTH / 2.0f;
    windowHeight = HEIGHT / 2.0f;
}

bool isOpen = true;

void LoginStage::runStage()
{
    if (glfwGetKey(Scene::getInstance().window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(Scene::getInstance().window))
    {
        Navigator::getInstance().exitGame();
        return;
    }

    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::SetNextWindowSize(ImVec2(windowWidth, windowHeight), ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(windowWidth, windowHeight), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    ImGui::Begin("Login", &isOpen, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoNav);

    static char username[256] = "";
    static char password[256] = "";

    ImGui::InputText("Username", username, IM_ARRAYSIZE(username), ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll);
    ImGui::InputText("Password", password, IM_ARRAYSIZE(password), ImGuiInputTextFlags_Password | ImGuiInputTextFlags_EnterReturnsTrue);

    if (ImGui::Button("Login"))
    {
        Navigator::getInstance().setActiveStage(new MainStage());
    }

    ImGui::End(); // ImGui penceresi sonu

    // ImGui çizimlerini yap
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // GLFW tamponları değiştir ve olayları işle
    glfwSwapBuffers(Scene::getInstance().window);
    glfwPollEvents();
}

void LoginStage::endStage()
{
}

LoginStage::~LoginStage()
{
}