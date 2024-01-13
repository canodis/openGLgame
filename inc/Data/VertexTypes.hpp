#pragma once

# include "../glm/glm.hpp"
# include <vector>

class  Vertex2dObject
{
public:
	glm::vec2 pos;
	glm::vec2 texCoord;
};

typedef std::vector<unsigned int>   IndexList;
typedef std::vector<glm::vec3>      PositionList;
typedef std::vector<glm::vec2>      TextCoordList;