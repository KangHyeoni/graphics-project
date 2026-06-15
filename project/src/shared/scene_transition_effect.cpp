#include "shared/scene_transition_effect.h"

#include <algorithm>

#include <glad/glad.h>

#include "shared/shader.h"

namespace scene_transition_effect {

enum class Phase {
    None,
    FadeOut,
    FadeIn,
};

static const float FADE_OUT_SECONDS = 1.0f;
static const float FADE_IN_SECONDS = 1.0f;

static Shader fadeOverlayShader;
static unsigned int fadeOverlayVAO = 0;
static unsigned int fadeOverlayVBO = 0;
static Phase phase = Phase::None;
static float phaseStart = 0.0f;
static int pendingSceneIndex = -1;

void init()
{
    fadeOverlayShader = Shader("../shaders/shared/fade_overlay.vs", "../shaders/shared/fade_overlay.fs");

    const float quadVertices[] = {
        -1.0f,  1.0f,
        -1.0f, -1.0f,
         1.0f, -1.0f,
        -1.0f,  1.0f,
         1.0f, -1.0f,
         1.0f,  1.0f,
    };

    glGenVertexArrays(1, &fadeOverlayVAO);
    glGenBuffers(1, &fadeOverlayVBO);
    glBindVertexArray(fadeOverlayVAO);
    glBindBuffer(GL_ARRAY_BUFFER, fadeOverlayVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

bool isActive()
{
    return phase != Phase::None;
}

void request(int targetSceneIndex, float now)
{
    if (isActive()) {
        return;
    }

    pendingSceneIndex = targetSceneIndex;
    phase = Phase::FadeOut;
    phaseStart = now;
}

int update(float now)
{
    if (!isActive()) {
        return -1;
    }

    float elapsed = now - phaseStart;

    if (phase == Phase::FadeOut && elapsed >= FADE_OUT_SECONDS) {
        int targetSceneIndex = pendingSceneIndex;
        phase = Phase::FadeIn;
        phaseStart = now;
        return targetSceneIndex;
    }

    if (phase == Phase::FadeIn && elapsed >= FADE_IN_SECONDS) {
        phase = Phase::None;
        pendingSceneIndex = -1;
    }

    return -1;
}

float getFadeAlpha(float now)
{
    if (!isActive()) {
        return 0.0f;
    }

    float elapsed = now - phaseStart;

    if (phase == Phase::FadeOut) {
        return std::min(elapsed / FADE_OUT_SECONDS, 1.0f);
    }
    if (phase == Phase::FadeIn) {
        return 1.0f - std::min(elapsed / FADE_IN_SECONDS, 1.0f);
    }
    return 0.0f;
}

void drawFadeOverlay(float alpha)
{
    alpha = std::max(0.0f, std::min(alpha, 1.0f));
    if (alpha <= 0.0f || fadeOverlayVAO == 0) {
        return;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    fadeOverlayShader.use();
    fadeOverlayShader.setFloat("alpha", alpha);
    glBindVertexArray(fadeOverlayVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    glDisable(GL_BLEND);
    glDepthMask(GL_TRUE);
    glEnable(GL_DEPTH_TEST);
}

} // namespace scene_transition_effect
