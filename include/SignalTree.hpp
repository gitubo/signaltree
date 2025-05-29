#pragma once

#include "SignalTreeNode.hpp"
#include "Task.hpp"
#include <memory> 
#include <vector>
#include <functional>


namespace signaltree {

    enum class SignalTreeReturnCode {
        SUCCESS,
        OUT_OF_RANGE,
        NO_SIGNAL_FOUND,
        TASK_NOT_FOUND,
        UNDEFINED_ERROR
    };

    class SignalTree {
        private:
            std::unique_ptr<SignalTreeNode> root_;
            size_t number_of_signals_;
            std::vector<Task> tasks_;
            size_t tasks_current_index_;

        public:
            SignalTree(size_t number_of_signals) : 
                number_of_signals_(number_of_signals),
                tasks_current_index_(0),
                root_(nullptr) 
            {
                tasks_.reserve(number_of_signals_);
            }

            ~SignalTree() = default;

            inline size_t get_number_of_signals() const { return number_of_signals_; }

            TaskId append_task(std::function<void()>);
            SignalTreeReturnCode schedule_task(size_t);
            SignalTreeReturnCode execute_next_task();

            
    };

}