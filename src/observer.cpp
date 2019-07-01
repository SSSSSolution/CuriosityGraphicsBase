#include "observer.h"

namespace curiosity {
    namespace graphics {

    void Subject::attach(Observer *observer) {
        observers.push_back(observer);
    }

    void Subject::detach(Observer *observer) {
        observers.remove(observer);
    }

    void Subject::notify() {
        for (auto observer : observers) {
            observer->update(this);
        }
    }

    }
}
