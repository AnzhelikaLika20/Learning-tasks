#include "segment.h"

geometry::Segment::Segment() {
    start_.SetX(0);
    start_.SetY(0);
    end_.SetX(0);
    end_.SetY(0);
}

geometry::Segment::Segment(geometry::Point start, geometry::Point end) {
    start_ = start;
    end_ = end;
}

geometry::Point geometry::Segment::GetStart() const {
    return start_;
}

geometry::Point geometry::Segment::GetEnd() const {
    return end_;
}
