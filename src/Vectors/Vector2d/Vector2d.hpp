
#ifndef VECTOR2D_H
#define VECTOR2D_H

# include <cmath>

struct Vector2D
{
    float x,y;

    Vector2D() = default;

    Vector2D(float a, float b)
    {
        x = a;
        y = b;
    }

    // index operator for L-Value (i.e. assignment)
    float& operator [] (int i)
    {
        return ((&x)[i]);
    }

    // index operator for R-Value (i.e. "retrieval")
    const float& operator [] (int i) const 
    {
        return ((&x)[i]);
    }

    Vector2D& operator +=(const Vector2D& v)
    {
        x += v.x;
        y += v.y;
        return (*this);
    }

    Vector2D& operator =(const Vector2D& v)
    {
        x = v.x;
        y = v.y;
        return (*this);
    }

    Vector2D& operator *=(float s)
    {
        
        x *= s;
        y *= s;

        return(*this);
    }

    Vector2D& operator /=(float s)
    {
        s = 1.0f / s;
        x /= s;
        y /= s;

        return(*this);
    }

};

inline Vector2D operator *(const Vector2D& v, float s) // have to put in both, as it's not a member of the struct
{
    return( Vector2D(v.x * s, v.y * s) );
}

inline Vector2D operator /(const Vector2D& v, float s )
{
    s = 1.0f / s;
    return(Vector2D(v.x / s, v.y / s));
}

inline Vector2D operator -(const Vector2D& v) // prepend negative sign
{
    return(Vector2D(-v.x, -v.y));
}

inline Vector2D operator +(const Vector2D& v, const Vector2D& w)
{
    return(Vector2D(v.x + w.x, v.y + w.y));
}

inline Vector2D operator -(const Vector2D& v, const Vector2D& w)
{
    return(Vector2D(v.x - w.x, v.y - w.y));
}

inline float magnitude(const Vector2D& v)
{
    return (sqrt(v.x * v.x + v.y * v.y));
}

inline Vector2D normalize(const Vector2D& v)
{
    return (v / magnitude(v) );
}

inline float Dot(const Vector2D& v, const Vector2D& w)
{
    return (v.x * w.x + v.y + w.y);
}





#endif /* VECTOR2D_HPP */
