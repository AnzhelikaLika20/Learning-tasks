#pragma once
#include "i_shape.h"
#include "point.h"
#include "vector.h"

namespace geometry {
class Segment : public IShape {
private:
    Point start_;
    Point end_;

public:
    Segment();

    Segment(Point, Point);

    Point GetStart() const;

    Point GetEnd() const;

    Segment& Move(const Vector& vector) override {
        start_.SetX(start_.GetX() + vector.GetX());
        start_.SetY(start_.GetY() + vector.GetY());
        end_.SetX(end_.GetX() + vector.GetX());
        end_.SetY(end_.GetY() + vector.GetY());
        return *this;
    };
    bool ContainsPoint(const Point& point) const override {
        if (GetStart() == GetEnd()) {
            return point == GetStart();
        }
        Vector vector1 = point - GetStart();
        Vector vector2 = GetEnd() - GetStart();
        return VectorMult(vector1, vector2) == 0 && point.GetX() >= std::min(GetStart().GetX(), GetEnd().GetX()) &&
               point.GetX() <= std::max(GetStart().GetX(), GetEnd().GetX()) &&
               point.GetY() >= std::min(GetStart().GetY(), GetEnd().GetY()) &&
               point.GetY() <= std::max(GetStart().GetY(), GetEnd().GetY());
    }

    bool CrossesSegment(const Segment& segment) const override {
        Point a = segment.GetStart();
        Point b = segment.GetEnd();
        Point c = GetStart();
        Point d = GetEnd();
        int64_t vector_mult1 = VectorMult(a - b, a - c);
        int64_t vector_mult2 = VectorMult(a - b, a - d);
        int64_t vector_mult3 = VectorMult(c - d, c - a);
        int64_t vector_mult4 = VectorMult(c - d, c - b);
        if (vector_mult1 * vector_mult2 < 0 && vector_mult3 * vector_mult4 < 0) {
            return true;
        }
        return false;
    };

    Segment* Clone() const override {
        Segment* new_line = new Segment(start_, end_);
        return new_line;
    };
};
}  // namespace geometry
