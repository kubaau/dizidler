#pragma once

#include <vector>

#include "Translation.hpp"
#include "Vertex.hpp"

using Vertices = std::vector<Vertex>;

struct Shape
{
    using Type = unsigned;

public:
    Shape(Type, const Vertices&, const Translation&);

    void render() const;

private:
    Translation translation;
    Type type;
    Vertices vertices;
};
