#include "math.h"
const float pi = 3.14159265 ; // For portability across platforms


class Transform  
{
public:
	Transform();
	virtual ~Transform();
    static matrix4 rotate(const float degrees, const vector3& axis) ;
    static matrix4 scale(const float &sx, const float &sy, const float &sz) ; 
    static matrix4 translate(const float &tx, const float &ty, const float &tz);
};

