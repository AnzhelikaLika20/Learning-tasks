#include "circle.h"

#include "segment.h"
#include "vector.h"
geometry::Circle::Circle() {
    centre_ = Point(0, 0);
    radius_ = 0;
}

geometry::Circle::Circle(geometry::Point point, int64_t r) {
    centre_ = point;
    radius_ = r;
}

geometry::Circle& geometry::Circle::Move(const geometry::Vector& vector) {
    centre_.SetX(centre_.GetX() + vector.GetX());
    centre_.SetY(centre_.GetY() + vector.GetY());
    return *this;
}

bool geometry::Circle::ContainsPoint(const geometry::Point& point) const {
    geometry::Vector segment = point - centre_;
    return static_cast<double>(Length(segment)) <= static_cast<double>(radius_);
}

bool geometry::Circle::CrossesSegment(const geometry::Segment& segment) const {
    bool flag1 = pow(static_cast<double>(segment.GetStart().GetX() - centre_.GetX()), 2) +
                     pow(static_cast<double>(segment.GetStart().GetY() - centre_.GetY()), 2) -
                     static_cast<double>(radius_ * radius_) <
                 0;
    bool flag2 = pow(static_cast<double>(segment.GetEnd().GetX() - centre_.GetX()), 2) +
                     pow(static_cast<double>(segment.GetEnd().GetY() - centre_.GetY()), 2) -
                     static_cast<double>(radius_ * radius_) <
                 0;
    return segment.Distance(centre_) <= static_cast<double>(radius_) && !(flag1 && flag2);
}

geometry::Circle* geometry::Circle::Clone() const {
    return new Circle(centre_, radius_);
}

int64_t geometry::Circle::GetRadius() const {
    return radius_;
}

geometry::Point geometry::Circle::GetCenter() const {
    return centre_;
}
