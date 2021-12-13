#include <algorithm>
#include <numeric>

#include "Path.h"

namespace aprs {

class findPathElement {
public:
  explicit findPathElement(const String &name) : _name(name) {
  }

  bool operator()(std::shared_ptr<IPathElement> other) const {
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

std::list<std::shared_ptr<IPathElement>> Path::get() const {
  return _path;
}

void Path::add(std::shared_ptr<IPathElement> path) {
  _path.push_back(path);
}

void Path::addNode(std::shared_ptr<IPathElement> node) {
  auto found = std::find_if(_path.begin(), _path.end(), [](const std::shared_ptr<IPathElement> elem) {
    return !elem->getConsumed();
  });
  _path.insert(found, node);
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
  auto accumulate_path = [](const String &a, std::shared_ptr<IPathElement> elem) {
    return a + elem->getPathName() + ", ";
  };

  String p = std::accumulate(_path.begin(), _path.end(), String(""), accumulate_path);
  p.remove(p.length() - 2);
  return p;
}

String Path::toAPRSString() const {
  if (_path.size() == 0) {
    return String();
  }

  auto accumulate_path = [](const String &a, std::shared_ptr<IPathElement> elem) {
    return a + elem->getPathName() + ",";
  };

  String p = std::accumulate(_path.begin(), _path.end(), String(","), accumulate_path);
  p.remove(p.length() - 1);
  return p;
}

Path PathFactory::generate(const String &pathText) {
  return Path();
}

} // namespace aprs
