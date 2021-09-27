#include <curve.hpp>
#include <iostream>

float curve::linearInterpolate(float x1, float x2, float t){
    return (1 - t) * x1 + t * x2;
}

vector2 curve::nthBezier(std::vector<controlPoint> points, float t){
    std::vector<controlPoint> nextLevelPoints;
    if (points.size() <= 2){
        return vector2{linearInterpolate(points[0].position.x, points[1].position.x, t), linearInterpolate(points[0].position.y, points[1].position.y, t)};
    } else {
        for (unsigned int i = 0; i < points.size() - 1; ++i){
            nextLevelPoints.push_back({{linearInterpolate(points[i].position.x, points[i + 1].position.x, t), linearInterpolate(points[i].position.y, points[i + 1].position.y, t)}});
        }
        return nthBezier(nextLevelPoints, t);
    }
}
