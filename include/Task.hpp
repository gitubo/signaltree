#pragma once

#include <memory> 
#include <functional>

namespace signaltree {

    struct Task {
        private:
            std::function<void()> callback_;
        public:
            Task(std::function<void()> callback) : callback_(callback) {}

            void invoke(){callback_();}
    };

}