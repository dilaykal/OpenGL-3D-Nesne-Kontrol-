#ifndef SHAPECREATOR_HPP
#define SHAPECREATOR_HPP

#include <unordered_map>
#include <glm/glm.hpp>

namespace graf {

class VertexArrayObject;

enum class ShapeTypes {
    Circle,
    Square,
    Cube,
    Pyramid,
    TruncatedPyramid
};

// Özel std::hash tanımı
struct ShapeTypesHash {
    std::size_t operator()(const ShapeTypes& shapeType) const noexcept {
        return static_cast<std::size_t>(shapeType);
    }
};

class ShapeCreator {
public:
    VertexArrayObject* create(ShapeTypes shape);

private:
    VertexArrayObject* createSquare();
    VertexArrayObject* createCircle(int angleInDegrees);
    VertexArrayObject* createCube();
    VertexArrayObject* createPyramid();
    VertexArrayObject* createTruncatedPyramid();

    // ShapeTypesHash kullanımı
    std::unordered_map<ShapeTypes, VertexArrayObject*, ShapeTypesHash> m_vaoMap;
};

} // namespace graf

#endif