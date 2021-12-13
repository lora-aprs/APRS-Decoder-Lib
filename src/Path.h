#ifndef PATH_H_
#define PATH_H_

#include <Arduino.h>
#include <list>
#include <memory>

namespace aprs {

class IPathElement {
public:
  virtual void   Consume()           = 0;
  virtual bool   getConsumed() const = 0;
  virtual String getName() const     = 0;
  virtual String getPathName() const = 0;
};

class BasicPathElement : public IPathElement {
public:
  explicit BasicPathElement(const String &name, bool consumed = false);

  void Consume() override;
  bool getConsumed() const override;

  String getName() const override;
  String getPathName() const override;

private:
  const String _name;
  bool         _consumed;
};

class WidePathElement : public IPathElement {
public:
  explicit WidePathElement(const int startValue, const int currentValue);

  void Consume() override;
  bool getConsumed() const override;

  String getName() const override;
  String getPathName() const override;

private:
  int _startValue;
  int _currentValue;
};

class Path {
public:
  std::list<std::shared_ptr<IPathElement>> get() const;
  void                                     add(std::shared_ptr<IPathElement> path);
  void                                     addNode(std::shared_ptr<IPathElement> node);

  bool isExisting(const String &name);
  void setConsumed(const String &name);

  String toString() const;
  String toAPRSString() const;

private:
  std::list<std::shared_ptr<IPathElement>> _path;
};

class PathFactory {
public:
  static Path generate(const String &pathText);
};

} // namespace aprs

#endif
