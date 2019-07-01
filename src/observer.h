#ifndef GRAPHCIS_OBSERVER_H
#define GRAPHCIS_OBSERVER_H
#include <list>
#include <string>

namespace curiosity {
    namespace graphics {
    class Subject;

    class Observer {
        friend class Subject;
    public:
        virtual ~Observer() {}

    protected:
        virtual void update(Subject *) = 0;
    };

    class Subject {
    public:
        virtual ~Subject() {}
        void attach(Observer *observer);
        void detach(Observer *observer);
        virtual void notify();
        virtual std::string getSubjectState() = 0;

    private:
        std::list<Observer *> observers;
    };

    }
}

#endif
