#pragma once
#include "i_shape.h"
#include "point.h"

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
        start_.Move(vector);
        end_.Move(vector);
        return *this;
    };

    bool ContainsPoint(const Point& point) const override {
        Vector vector1 = Vector((point - start_).GetX(), (point - start_).GetY());
        Vector vector2 = Vector((end_ - start_).GetX(), (end_ - start_).GetY());
        if (point.GetX() >= std::min(start_.GetX(), end_.GetX()) &&
            point.GetX() <= std::max(start_.GetX(), end_.GetX()) && VectorMult(vector1, vector2) == 0) {
            return true;
        }
        return false;
    }

    bool CrossesSegment(const Segment& segment) const override {
        Vector p3_p4 = geometry::Vector((segment.end_ - segment.start_).GetX(), (segment.end_ - segment.start_).GetY());
        Vector p3_p1 = geometry::Vector((segment.end_ - end_).GetX(), (segment.end_ - end_).GetY());
        Vector p3_p2 = geometry::Vector((segment.end_ - start_).GetX(), (segment.end_ - start_).GetY());
        Vector p1_p2 = geometry::Vector((end_ - start_).GetX(), (end_ - start_).GetY());
        Vector p1_p4 = geometry::Vector((end_ - segment.start_).GetX(), (end_ - segment.start_).GetY());
        Vector p1_p3 = geometry::Vector((end_ - segment.end_).GetX(), (end_ - segment.end_).GetY());
        int64_t p3_p4_and_p3_p1 = VectorMult(p3_p4, p3_p1);
        int64_t p3_p4_and_p3_p2 = VectorMult(p3_p4, p3_p2);
        int64_t p1_p2_and_p1_p3 = VectorMult(p1_p2, p1_p3);
        int64_t p1_p2_and_p1_p4 = VectorMult(p1_p2, p1_p4);
        if (p3_p4_and_p3_p1 * p3_p4_and_p3_p2 < 0 && p1_p2_and_p1_p3 * p1_p2_and_p1_p4 < 0) {
            return true;
        }
        return false;
    };

    Segment* Clone() const override {
        Segment* segment_new = new Segment(start_, end_);
        return segment_new;
    };
};
}  // namespace geometry
