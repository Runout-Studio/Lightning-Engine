#pragma once
#include "Vector2D.hpp"
#include <memory>
#include <vector>

namespace Motus2D {

// Body types
enum class BodyType { Static, Dynamic };

// Base class
class Body {
public:
    Vector2D position;
    Vector2D velocity;
    float mass{1.0f};
    BodyType type{BodyType::Dynamic};

    Body(Vector2D pos, BodyType t = BodyType::Dynamic, float m = 1.0f)
        : position(pos), type(t), mass(m) {}

    virtual void applyForce(const Vector2D& force) = 0;
    virtual void integrate(float dt) = 0;
    virtual ~Body() = default;
};

// Circle body
class Circle : public Body {
public:
    float radius{1.0f};

    Circle(Vector2D pos, float r, BodyType t = BodyType::Dynamic, float m = 1.0f)
        : Body(pos, t, m), radius(r) {}

    void applyForce(const Vector2D& force) override {
        if (type == BodyType::Dynamic)
            velocity += force * (1.0f / mass);
    }

    void integrate(float dt) override {
        if (type == BodyType::Dynamic)
            position += velocity * dt;
    }
};

// Rectangle body
class Rectangle : public Body {
public:
    float width{1.0f};
    float height{1.0f};

    Rectangle(Vector2D pos, float w, float h, BodyType t = BodyType::Dynamic, float m = 1.0f)
        : Body(pos, t, m), width(w), height(h) {}

    void applyForce(const Vector2D& force) override {
        if (type == BodyType::Dynamic)
            velocity += force * (1.0f / mass);
    }

    void integrate(float dt) override {
        if (type == BodyType::Dynamic)
            position += velocity * dt;
    }
};

// World to manage bodies
class World {
public:
    Vector2D gravity{0.0f, -9.81f};
    std::vector<std::shared_ptr<Body>> bodies;

    void addBody(std::shared_ptr<Body> body) { bodies.push_back(body); }

    void step(float dt) {
        for (auto& b : bodies) {
            if (b->type == BodyType::Dynamic)
                b->applyForce(gravity * b->mass); // gravity
            b->integrate(dt);
        }
    }
};

} // namespace Motus2D
