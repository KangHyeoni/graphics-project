#ifndef SCENE_TRANSITION_EFFECT_H
#define SCENE_TRANSITION_EFFECT_H

namespace scene_transition_effect {

void init();
bool isActive();
void request(int targetSceneIndex, float now);
int update(float now);
float getFadeAlpha(float now);
void drawFadeOverlay(float alpha);

} // namespace scene_transition_effect

#endif
