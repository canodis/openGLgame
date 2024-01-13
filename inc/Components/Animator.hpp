#include "Component.hpp"
#include <vector>


class Animator : public Component 
{
public:
    Animator();
    ~Animator();
    void update(float deltaTime) override;
    void setGameObject(GameObject *gameObject) override;
private:
};