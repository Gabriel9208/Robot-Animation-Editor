#include "Camara.h"

Camara::Camara() : pos(0.0f, 0.0f, 10.0f), target(0.0f, 0.0f, 0.0f), up(0.0f, 1.0f, 0.0f), lookAtMat(1.0f)
{
    genLookAt();
}

Camara::Camara(glm::vec3 cameraPos, glm::vec3 cameraTarget, glm::vec3 upVector): 
    pos(cameraPos), 
    target(cameraTarget), 
    up(upVector), 
    lookAtMat(1.0f)
{
    genLookAt();

}

void Camara::setPos(glm::vec3 newPos)
{
    pos = newPos;
    genLookAt();
}

void Camara::setTarget(glm::vec3 newTarget)
{
    target = newTarget;
    genLookAt();
}

void Camara::setUpVector(glm::vec3 newUp)
{
    up = newUp;
    genLookAt();
}

void Camara::genLookAt()
{
    lookAtMat = glm::lookAt(pos, target, up);
}

