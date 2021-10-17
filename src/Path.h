#ifndef PATH_H_
#define PATH_H_

#include <Arduino.h>
#include <list>

namespace aprs {
class PathElement {
public:
  explicit PathElement(const String &name, bool consumed = false);

  void setConsumed(bool consumed = true);
  bool getConsumed() const;

  String getName() const;

private:
  const String _name;
  bool         _consumed;
};

class Path {
public:
  std::list<PathElement> get() const;
  void                   add(const PathElement &path);

  bool isExisting(const String &name);
  void setConsumed(const String &name);

  String toString() const;

private:
  std::list<PathElement> _path;
};

} // namespace aprs

#endif
