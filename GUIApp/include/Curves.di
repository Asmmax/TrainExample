bind "ACurve.hpp";
bind "Circle2D.hpp";
bind "Spline.hpp";

abstract shared ACurve
{
} curves;

shared Circle2D : ACurve
{
	Circle2D(glm::vec3 center, float radius, float parameter_distorsion = 0.0);
};

shared Spline : ACurve
{
	Spline(vector<glm::vec3> points, bool loop, unsigned int accuracy = 5);
};
