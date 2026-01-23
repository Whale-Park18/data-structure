#ifndef DSL_OBJECT_HPP
#define DSL_OBJECT_HPP

class object
{
public:
    object() = default;
    virtual ~object() = default;

    void do_something();
};

#endif // DSL_OBJECT_HPP