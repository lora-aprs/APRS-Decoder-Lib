#include <algorithm>
#include <numeric>

#include "Path.h"

namespace aprs {

class findPathElement {
public:
  explicit findPathElement(const String &name) : _name(name) {
  }

  bool operator()(const PathElement &other) const {
    return other.getName() == _name;
  }

private:
  const String _name;
};

PathElement::PathElement(const String &name, bool consumed) : _name(name), _consumed(consumed) {
}

void PathElement::setConsumed(bool consumed) {
  _consumed = consumed;
}

bool PathElement::getConsumed() const {
  return _consumed;
}

String PathElement::getName() const {
  return _name;
}

std::list<PathElement> Path::get() const {
  return _path;
}

void Path::add(const PathElement &path) {
  _path.push_back(path);
}

bool Path::isExisting(const String &name) {
  return std::any_of(_path.begin(), _path.end(), findPathElement(name));
}

void Path::setConsumed(const String &name) {
  auto found = std::find_if(_path.begin(), _path.end(), findPathElement(name));
  if (found != _path.end()) {
    found->setConsumed();
    return;
  }
  _path.push_back(PathElement(name, true));
}

String Path::toString() const {
  auto accumulate_path = [](const String &a, const aprs::PathElement &elem) {
    if (elem.getConsumed()) {
      return a + elem.getName() + "*, ";
    } else {
      return a + elem.getName() + ", ";
    }
  };

  String p = std::accumulate(_path.begin(), _path.end(), String(""), accumulate_path);
  p.remove(p.length() - 2);
  return p;
}
} // namespace aprs
