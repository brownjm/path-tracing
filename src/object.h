#ifndef OBJECT_H_
#define OBJECT_H_

class Object {
public:
  virtual Hit intersect(const Ray& ray) const = 0;
  
};

#endif // OBJECT_H_
