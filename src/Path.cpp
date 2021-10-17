#include <algorithm>
#include <numeric>

#include "Path.h"

namespace aprs {

class findPathElement {
public:
  explicit findPathElement(const String &name) : _name(name) {
  }

  bool operator()(IPathElement *other) const {
    return other->getName() == _name;
  }

private:
  const String _name;
};

BasicPathElement::BasicPathElement(const String &name, bool consumed) : _name(name), _consumed(consumed) {
}

void BasicPathElement::Consume() {
  _consumed = true;
}

bool BasicPathElement::getConsumed() const {
  return _consumed;
}

String BasicPathElement::getName() const {
  return _name;
}

String BasicPathElement::getPathName() const {
  if (getConsumed()) {
    return getName() + "*";
  }
  return getName();
}

WidePathElement::WidePathElement(const int startValue, const int currentValue) : _startValue(startValue), _currentValue(currentValue) {
}

void WidePathElement::Consume() {
  if (_currentValue > 0) {
    _currentValue--;
  }
}

bool WidePathElement::getConsumed() const {
  return _currentValue == 0;
}

String WidePathElement::getName() const {
  return String("WIDE") + _startValue;
}

String WidePathElement::getPathName() const {
  if (getConsumed()) {
    return getName() + "*";
  }
  return getName() + "-" + _currentValue;
}

std::list<IPathElement *> Path::get() const {
  return _path;
}

void Path::add(IPathElement *path) {
  _path.push_back(path);
}

bool Path::isExisting(const String &name) {
  return std::any_of(_path.begin(), _path.end(), findPathElement(name));
}

void Path::setConsumed(const String &name) {
  auto found = std::find_if(_path.begin(), _path.end(), findPathElement(name));
  if (found != _path.end()) {
    (*found)->Consume();
  }
}

String Path::toString() const {
  auto accumulate_path = [](const String &a, aprs::IPathElement *elem) {
    return a + elem->getPathName() + ", ";
  };

  String p = std::accumulate(_path.begin(), _path.end(), String(""), accumulate_path);
  p.remove(p.length() - 2);
  return p;
}
} // namespace aprs
