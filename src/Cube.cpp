#include "Cube.h"

#include <cassert>

#include "Matrix.h"
#include "Quaternion.h"

Cube::Cube(Vector center, float width, float height, float depth) : transformMatrix(4, 4), center(center), width(width),
                                                                    height(height), depth(depth)
{
    transformMatrix = transformMatrix.identity();
    Vector frontCenter = Vector(center.x, center.y, center.z + depth / 2);
    Vector backCenter = Vector(center.x, center.y, center.z - depth / 2);
    Vector leftCenter = Vector(center.x - width / 2, center.y, center.z);
    Vector rightCenter = Vector(center.x + width / 2, center.y, center.z);
    Vector topCenter = Vector(center.x, center.y + height / 2, center.z);
    Vector bottomCenter = Vector(center.x, center.y - height / 2, center.z);

    // Plane front = Plane(frontCenter, Vector(0, 0, 1));
    // Plane back = Plane(backCenter, Vector(0, 0, -1));
    // Plane left = Plane(leftCenter, Vector(-1, 0, 0));
    // Plane right = Plane(rightCenter, Vector(1, 0, 0));
    // Plane top = Plane(topCenter, Vector(0, 1, 0));
    // Plane bottom = Plane(bottomCenter, Vector(0, -1, 0));

    const float halfWidth = width / 2.0f;
    const float halfHeight = height / 2.0f;
    const float halfDepth = depth / 2.0f;

    // Define the planes for each face of the cube
    faces =
    {
        Plane(center + Vector(halfWidth, 0.0f, 0.0f), Vector(1.0f, 0.0f, 0.0f)),  // Right face
        Plane(center - Vector(halfWidth, 0.0f, 0.0f), Vector(-1.0f, 0.0f, 0.0f)), // Left face
        Plane(center + Vector(0.0f, halfHeight, 0.0f), Vector(0.0f, 1.0f, 0.0f)), // Top face
        Plane(center - Vector(0.0f, halfHeight, 0.0f), Vector(0.0f, -1.0f, 0.0f)), // Bottom face
        Plane(center + Vector(0.0f, 0.0f, halfDepth), Vector(0.0f, 0.0f, 1.0f)), // Front face
        Plane(center - Vector(0.0f, 0.0f, halfDepth), Vector(0.0f, 0.0f, -1.0f)) // Back face
    };
}

//static int streak = 0;
bool Cube::intersects(Line line) const
{
    const float halfWidth = width / 2.0f;
    const float halfHeight = height / 2.0f;
    const float halfDepth = depth / 2.0f;

    // Transform the line into the cube's local coordinate system
    const Matrix inverseTransform = transformMatrix.inverse();
    line.p = inverseTransform * line.p;

    const Matrix inverseRotation = inverseTransform.getRotationPart();
    line.v = inverseRotation * line.v;

    line.v = line.v.normalized();

    constexpr float epsilon = 0.00005f;

    for (auto const& plane : faces)
    {
        const Vector normal = plane.normal;
        const Vector Q = plane.p;
        const Vector P = line.p;
        const Vector V = line.v;

        const float t = ((Q - P).dot(normal)) / (V.dot(normal));

        if (t >= 0.0f)
        {
            constexpr float epsilon = 0.0f; // Doesn't really fix the issue
            const Vector intersection = P + V * t;

            if (std::abs(intersection.x - center.x) <= halfWidth + epsilon &&
                std::abs(intersection.y - center.y) <= halfHeight + epsilon &&
                std::abs(intersection.z - center.z) <= halfDepth + epsilon)
            {
                return true;
            }
        }
    }

    //streak = 0;
    return false;
}

static float prevX = 1;

void Cube::rotate(float angle, Vector axis)
{
    // Rotate the center of each face
    for (auto& face : faces)
    {
        face.p = Quaternion::rotate(face.p - center, axis, angle) + center;
        Vector v = Quaternion::rotate(face.normal, axis, angle);

        if (prevX * v.x < 0)
            // face.p.x *= -1;

            prevX = v.x;

        face.normal = v;
    }
}