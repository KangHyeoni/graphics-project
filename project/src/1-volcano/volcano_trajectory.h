#ifndef VOLCANO_TRAJECTORY_H
#define VOLCANO_TRAJECTORY_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace volcano {

extern const glm::vec3 fireSceneOffset;
extern const float flightSpeed;

struct DragonFlightPose {
    glm::vec3 position;
    glm::vec3 tangent;
    float angle;
};

// Set of trajectory functions for Toothless and the dragon flight sequence
glm::vec3 rotateAroundX(const glm::vec3& value, float angle);
glm::mat4 getToothlessFlightModelMatrix(float time);
DragonFlightPose getDragonFlightPose(float time);
glm::vec3 getDragonFlightVelocity(float time);
glm::mat4 getDragonFlightModelMatrix(float time);

} // namespace volcano

#endif
