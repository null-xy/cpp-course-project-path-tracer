
#ifndef RAY_CLASS
#define RAY_CLASS

#include <eigen3/Eigen/Dense>
//#include <eigen3/Eigen/Core>

template <typename T>
class Ray{
    public:
    Ray(){}
    Ray(const Eigen::Vector3d& origin_, const Eigen::Vector3d& direction_):
    origin_(origin),direction_(direction){}
    
    Eigen::Vector3d Origin() const {return origin_;}
    Eigen::Vector3d Direction() const {return direction_;}
    Eigen::Vector3d At(T& t) const {return origin_ + t * direction_;}

    private:
    Eigen::Vector3d origin_;
    Eigen::Vector3d direction_;
};

#endif