#include "Particle.h"


bool Particle::almostEqual(double a, double b, double eps)
{
	return fabs(a - b) < eps;
}

void Particle::unitTests()
{
    int score = 0;

    cout << "Testing RotationMatrix constructor...";
    double theta = M_PI / 4.0;
    RotationMatrix r(M_PI / 4);
    if (r.getRows() == 2 && r.getCols() == 2 && almostEqual(r(0, 0), cos(theta))
        && almostEqual(r(0, 1), -sin(theta))
        && almostEqual(r(1, 0), sin(theta))
        && almostEqual(r(1, 1), cos(theta)))
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Testing ScalingMatrix constructor...";
    ScalingMatrix s(1.5);
    if (s.getRows() == 2 && s.getCols() == 2
        && almostEqual(s(0, 0), 1.5)
        && almostEqual(s(0, 1), 0)
        && almostEqual(s(1, 0), 0)
        && almostEqual(s(1, 1), 1.5))
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Testing TranslationMatrix constructor...";
    TranslationMatrix t(5, -5, 3);
    if (t.getRows() == 2 && t.getCols() == 3
        && almostEqual(t(0, 0), 5)
        && almostEqual(t(1, 0), -5)
        && almostEqual(t(0, 1), 5)
        && almostEqual(t(1, 1), -5)
        && almostEqual(t(0, 2), 5)
        && almostEqual(t(1, 2), -5))
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    
    cout << "Testing Particles..." << endl;
    cout << "Testing Particle mapping to Cartesian origin..." << endl;
    if (m_centerCoordinate.x != 0 || m_centerCoordinate.y != 0)
    {
        cout << "Failed.  Expected (0,0).  Received: (" << m_centerCoordinate.x << "," << m_centerCoordinate.y << ")" << endl;
    }
    else
    {
        cout << "Passed.  +1" << endl;
        score++;
    }

    cout << "Applying one rotation of 90 degrees about the origin..." << endl;
    Matrix initialCoords = m_A;
    rotate(M_PI / 2.0);
    bool rotationPassed = true;
    for (int j = 0; j < initialCoords.getCols(); j++)
    {
        if (!almostEqual(m_A(0, j), -initialCoords(1, j)) || !almostEqual(m_A(1, j), initialCoords(0, j)))
        {
            cout << "Failed mapping: ";
            cout << "(" << initialCoords(0, j) << ", " << initialCoords(1, j) << ") ==> (" << m_A(0, j) << ", " << m_A(1, j) << ")" << endl;
            rotationPassed = false;
        }
    }
    if (rotationPassed)
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Applying a scale of 0.5..." << endl;
    initialCoords = m_A;
    scale(0.5);
    bool scalePassed = true;
    for (int j = 0; j < initialCoords.getCols(); j++)
    {
        if (!almostEqual(m_A(0, j), 0.5 * initialCoords(0,j)) || !almostEqual(m_A(1, j), 0.5 * initialCoords(1, j)))
        {
            cout << "Failed mapping: ";
            cout << "(" << initialCoords(0, j) << ", " << initialCoords(1, j) << ") ==> (" << m_A(0, j) << ", " << m_A(1, j) << ")" << endl;
            scalePassed = false;
        }
    }
    if (scalePassed)
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Applying a translation of (10, 5)..." << endl;
    initialCoords = m_A;
    translate(10, 5);
    bool translatePassed = true;
    for (int j = 0; j < initialCoords.getCols(); j++)
    {
        if (!almostEqual(m_A(0, j), 10 + initialCoords(0, j)) || !almostEqual(m_A(1, j), 5 + initialCoords(1, j)))
        {
            cout << "Failed mapping: ";
            cout << "(" << initialCoords(0, j) << ", " << initialCoords(1, j) << ") ==> (" << m_A(0, j) << ", " << m_A(1, j) << ")" << endl;
            translatePassed = false;
        }
    }
    if (translatePassed)
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Score: " << score << " / 7" << endl;
}

Particle::Particle(RenderTarget &target, int numPoints, Vector2i mouseClickPosition): m_A(2, numPoints) 
{

}

void Particle::draw(RenderTarget &target, RenderStates states) const 
{

}

void Particle::update(float dt) 
{
    m_ttl -= dt;
    rotate(dt * m_radiansPerSec);
    scale(SCALE);

    float dx, dy;
    dx = m_vx * dt;

    m_vy -= G * dt;

    dy = m_vy * dt;

    translate(dx, dy);
}


void Particle::translate(double xShift, double yShift) 
{
    
    m_centerCoordinate.x += xShift;
    m_centerCoordinate.y += yShift;
}

void Particle::rotate(double theta) 
{
    Vector2f temp =  m_centerCoordinate;
    //shift particle back to the origin
    translate(-m_centerCoordinate.x, -m_centerCoordinate.y);
    
    ScalingMatrix S = c;

    //matrix multiplication
    for (float i = 0; i < -m_centerCoordinate.y; i++)
    {
        for (float j = 0; j < -m_centerCoordinate.x; j++)
        {
            m_A = S * m_A;
        }
    }

    translate(temp.x, temp.y);
}

void Particle::scale(double c) 
{

}

//vector.h
namespace Vector
{
    template<typename T> 
    class vector 
    {
    private:
        size_t sz; 
        T* elem;
        size_t space;
    public:
        vector() : sz(0), elem(nullptr), space(0), {}
        //keyword explicit: prevents code like vctor<int> v = 7
        explicit vector(size_t s) : sz{ s }, elem{new T[s] }, space{ s }, {}

        vector(const vector&)
        vector& operator=(const vector&);
        ~vector() {delete[] elem; cout << "Destructor called!" << endl; }
        //checked access
        T& at(size_t n);
        const T& at(size_t n) const;
        //unchecked access
        T& operator[](size_t n);
        const T& operator[](size_t n)  const;

        size_t size() const {return sz;}

        void resize(size_t newsize);
        void push_back(T d);
        void reserve(size_t newalloc);
        int capacity() const { return space; } 
    };

    template<typename T>
    T& vector<T>::operator[](size_t n)
    {
        return elem[n];
    }

    template<typename T>
    const T& vector<T>::operator[](size_t n) const
    {
        return elem[n];
    }

    //checked acces throws an exception for out of range index
    struct out_of_range {};
    template<typename T>
    const T& vector<T>::at(size_t n) const
    {
        if(n < 0 || n >= sz) throw out_of_range();
        return elem[n];
    }
    

    //vector<int> v1 = v2;
    template<typename T>
    vector<T>::vector(const vector<T>& a):
    sz(a.sz), elem(new T[a.sz]), space,{a.sz}
    {
        cout << "Copy constructor called" << endl;
        for (size_t i = 0; i < sz; i++)
        {
            elem[i] = a.elem[i];
        }
    }

    //vector<int> v1;
    //v1 = v2
    template<typename T>
    vector<T>& vector<T>::operator=(const vector<T>& a)
    {
        cout << "Copy assignment called" << endl;
        if(this == &a) return *this;    //guard against self assignment
        if(a.sz < space)
        {
            for(size_t i = 0; i < a.sz; i++) elem[i] = a.elem[i];
            sz = a.sz;
            return *this;
        }
        else
        {
            T* p = new T[a.sz];
            for(size_t i = 0; i < a.sz; i++) p[i] = a.elem[i];
            delete[] elem;
            sz = a.sz;
            space = a.sz;
            elem = p;
            return *this;
        }
    }

    template<typename T>
    void vector<T>::push_back(T d)
    {
        if(sz == 0) reserve(8);
        else if(sz == space) reserve(2 * space);
        elem[sz] = d;
        ++sz;
    }

    template<typename T>
    void vector<T>::reserve(size_t newalloc)
    {
        if (newalloc <= space) return
        T* p = new T[newalloc];
        for(size_t i = 0, i < sz; i++) p[i] = elem[i];
        delete[] elem;
        elem = p;
        space = newalloc;
    }

    template<typename T>
    void vector<T>::resize(size_t newsize)
    {
        reserve(newsize);
        for(size_t i = sz; i < newsize; i++) elem[i] = T();
        sz = newsize;
    }

    template<typename T>
    ostream& operator<<(ostream& os, const vector<T>& v)
    {
        for(size_t i = 0; i < v.size(); i++) os << v[i] << " ";
        return os;
    }
}
