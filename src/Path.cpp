#include "Path.h"

namespace aprs {

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
  for (auto const &pathElement : _path) {
    if (pathElement.getName() == name) {
      return true;
    }
  }
  return false;
}

void Path::setConsumed(const String &name) {
  for (auto &pathElement : _path) {
    if (pathElement.getName() == name) {
      pathElement.setConsumed();
      return;
    }
  }
  // element is not existing, lets add it
  _path.push_back(PathElement(name, true));
}

String Path::toString() const {
  String p = "";
  for (auto const &pathElement : _path) {
    { p += pathElement.getName() + "(" + pathElement.getConsumed() + "), "; }
  }
  p.remove(p.length() - 2, 2);
  return p;
}
} // namespace aprs
